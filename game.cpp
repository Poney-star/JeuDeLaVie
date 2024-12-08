#include "game.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <cmath>
#include <thread>
#include <chrono>

Game::Game()
{
    grid = new Grid(0,0);
    cursor = new Cursor();
    interval = 200;
}

Cursor* Game::getCursor() const
{
    return cursor;
}

sf::RenderWindow* Game::getWindow() const
{
    return window;
}

void Game::resizeWindow(int width, int height) const
{
    grid->resizeSprites(width, height);
    window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
}

void Game::setMode()
{
    std::string choice;
    const std::vector<std::string> g = {"g","G","GRAPHIQUE","graphique"};
    const std::vector<std::string> c = {"c","C","CONSOLE","console"};
    while(1)
    {
        std::cout << "Indiquer le mode (graphique/console): "<< std::endl;
        std::cin >> choice;
        if (std::find(g.begin(), g.end(), choice) != g.end())
        {
            this->graphic();
            break;
        } 
        else if (std::find(c.begin(), c.end(), choice) != c.end())
        {
            this->console();
            break;
        }
    }
}

void Game::setConstantCell(sf::Vector2i coordinates) const
{
    sf::Vector2i shapeBounds = grid->getSpriteBounds();
    grid->setConstant(floor(coordinates.x / shapeBounds.x),floor(coordinates.y / shapeBounds.y));
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

void Game::graphic()
{
    if(!grid->loadTextures())
    {
        std::cerr << "Problème de chargement des textures" << std::endl;
    }
    int timer;
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
                    this->resizeWindow(window->getSize().x,window->getSize().y);
                    break;
                case sf::Event::MouseButtonPressed:
                    cursor->clic(&event, this);
                    break;
                case sf::Event::MouseMoved:
                    cursor->updatePosition(event.mouseMove.x, event.mouseMove.y);
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
                    }
                    break;
            }
            if (running && timer == interval)
            {
                window->display();
                grid->nextGen();
            } else {
                grid->display(window);
                timer = interval;
            }
        }
    }
}

void Game::display() const
{
    grid->display(window);
}

void Game::pause()
{
    running = !running;
}

void Game::init()
{
    std::string path;
    std::cout << "Indiquer le chemin d'accès du fichier: ";
    std::cin >> path;
    std::cout << "Indiquer le nombre de générations à effectuer: ";
    std::cin >> genMax;
    this->loadFile(path);
    this->setMode();
}

void Game::invertCell(sf::Vector2i coordinates) const
{
    sf::Vector2i shapeBounds = grid->getSpriteBounds();
    grid->invertCell(floor(coordinates.x / shapeBounds.x),floor(coordinates.y / shapeBounds.y));
}

void Game::loadFile(const std::string filename){
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir " << filename << std::endl;
    }

    grid->clear();
    int x = 0, y = 0;
    int width, height;
    file >> height; 
    file >> width;
    file.ignore();
    if (!((width > 1 && height > 1) && file.get() == (char)10)) {
        width = 0;
        height = 0;
        file.clear();
        file.seekg(0,std::ios::beg);
        for (std::string line; std::getline(file, line); height++)
        {
            if(std::count(line.begin(), line.end(), ' ') + 1 > width) width = std::count(line.begin(), line.end(), ' ') + 1;
        }
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
                    row.push_back(new Dead_Cell(x, y));
                    x++;
                    break;
                case '1':
                    row.push_back(new Alive_Cell(x, y));
                    x++;
                    break;
                case '\n':
                    x = 0;
                    (row.size() + 1 == width) ? grid->addLine(row) : grid->addLine(this->resizeLine(width, row, x, y));
                    y++;
                    row = {};
                    break;
            }
        }
    }
    (row.size() + 1 == width) ? grid->addLine(row) : grid->addLine(this->resizeLine(width, row, x, y));
    file.close();
    while (height - 1 > y)
    {
        x = 0;
        row = {};
        while (width - 1 > x)
        {
            row.push_back(new Dead_Cell(x, y));
            x++;
        }
        grid->addLine(row);
    }
    grid->endInit();
}

std::vector<Cell*> Game::resizeLine(int width, std::vector<Cell*> row,int x ,int y) const
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
            row.push_back(new Dead_Cell(x, y));
            x++;
        }
    }
    return row;
}