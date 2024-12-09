#include "game.hpp"

Game::Game()
{
    grid = new Grid(0,0);
    interval = std::chrono::seconds(1);
}
void Game::setGenMax(int nb)
{
    genMax = nb;
}
void Game::setConstantCell(sf::Vector2i coordinates) const
{
    sf::FloatRect shapeBounds = renderer->getSprite("aliveCell")->getGlobalBounds();
    grid->invertConst(floor(coordinates.x / shapeBounds.width),floor(coordinates.y / shapeBounds.height), renderer);
}

void Game::console()
{
    std::string intConcatenated;
    while(grid->getGenNumber() < genMax + 1)
    {
        std::ofstream outputFile("Grille_Generation_Numero_"+std::to_string(grid->getGenNumber())+"_out.txt");
        if (outputFile.is_open())
        {
            for(int line = 0; line < grid->getHeight(); line++)
            {
                intConcatenated = "";
                for (int nb : grid->getLine(line))
                {
                    intConcatenated += std::to_string(nb) + " ";
                }
                outputFile << intConcatenated + "\n";
            }
        }
        outputFile.close();
        grid->nextGen();
    }
}

void Game::graphic(sf::RenderWindow* window)
{
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::Resized:
                    break;
                case sf::Event::MouseButtonPressed:
                    renderer->getCursor()->clicOnCell(&event, this);
                    break;
                case sf::Event::MouseMoved:
                    renderer->getCursor()->updatePosition(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y);
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)  
                    {
                        case sf::Keyboard::Escape:
                            this->pause();
                            break;
                        case sf::Keyboard::Space:
                            this->pause();
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            std::chrono::system_clock::time_point timer = std::chrono::system_clock::now();
            if (running && timer - start >= interval)
            {
                grid->nextGen();
                renderer->displayGameCells(grid);
                start = timer;
            } else {
                window->display();
            }
        }
    }
}

void Game::pause()
{
    running = !running;
}

void Game::invertCell(sf::Vector2i coordinates) const
{
    sf::FloatRect shapeBounds = renderer->getSprite("aliveCell")->getGlobalBounds();
    grid->invertValue(floor(coordinates.x / shapeBounds.width),floor(coordinates.y / shapeBounds.height), renderer);
}

bool Game::loadFile(const std::string filename){
    std::ifstream file(filename);
    if (!file) {
        return 0;
    }
    unsigned int x = 0, y = 0;
    unsigned int width, height;
    file >> height; 
    file >> width;
    if (!((width > 1 && height > 1) && file.get() == (char)10)) {
        width = 0;
        height = 0;
        file.clear();
        file.seekg(0,std::ios::beg);
        for (std::string line; std::getline(file, line); height++)
        {
            if(std::count(line.begin(), line.end(), ' ') + 1 > width) width = std::count(line.begin(), line.end(), ' ') + 1;
        }
        y = 0;
        file.ignore();
        file.clear();
        file.seekg(0,std::ios::beg);
    }
    grid->setSize(width, height);
    std::vector<Cell*> row;
    for (char c; file.get(c);)
    {
        if (y < height)
        {
            switch (c)
            {
                case ' ':
                    break;
                case '0':
                    row.push_back(new mutableCell(x, y, 0));
                    x++;
                    break;
                case '1':
                    row.push_back(new mutableCell(x, y, 1));
                    x++;
                    break;
                case '2':
                    row.push_back(new constCell(x, y, 0));
                    x++;
                    break;
                case '3':
                    row.push_back(new constCell(x, y, 1));
                    x++;
                    break;
                case '\n':
                    x = 0;
                    (row.size() + 1 == width) ? grid->addLine(row, renderer) : grid->addLine(resizeLine(width, row, x, y), renderer);
                    y++;
                    row = {};
                    break;
            }
        }
    }      
    (row.size() + 1 == width) ? grid->addLine(row, renderer) : grid->addLine(this->resizeLine(width, row, x, y), renderer);
    file.close();
    while (height - 1 > y)
    {
        x = 0;
        row = {};
        while (width - 1 > x)
        {
            row.push_back(new mutableCell(x, y, 0));
            x++;
        }
        grid->addLine(row, renderer);
    }
    grid->updateNeighbours();
    return 1;
}

std::vector<Cell*> Game::resizeLine(unsigned int width, std::vector<Cell*> row,unsigned int x ,unsigned int y) const
{
    if (row.size() > width)
    {
        while (row.size() > width)
        {
            row.pop_back();
        }
    } else {
        while (row.size() < width)
        {
            row.push_back(new mutableCell(x, y, 0));
            x++;
        }
    }
    return row;
}