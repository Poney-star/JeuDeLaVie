#include "game.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
Game::Game()
{
    window = new sf::RenderWindow();
    grid = new Grid(0,0);
    cursor = new Cursor();
}

void Game::resizeWindow(int width, int height) const
{
    grid->resizeSprites(width, height);
    window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
}

void Game::setMode()
{
    std::string choice;
    /*int gridWidth;
    int gridHeight;*/
    const std::vector<std::string> g = {"g","G","GRAPHIQUE","graphique"};
    const std::vector<std::string> c = {"c","C","CONSOLE","console"};
    // Dans le cas d'une taille non fixée par le fichier :
    /* 
    std::cout << "Indiquer la hauteur de la grille:" << std::endl;
    std::cin >> gridHeight;
    std::cout << "Indiquer la largeur de la grille:" << std::endl;
    std::cin >> gridWidth;
    grid -> setSize(gridWidth, gridHeight);
    */
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
    while(grid->getGenNumber() < genMax)
    {
        std::ofstream outputFile("Grille_Generation_Numero_"+std::to_string(grid->getGenNumber())+"_out.txt");
        std::string intConcatenated;
        if (outputFile.is_open())
        {
            for(int line; line < grid->getHeight(); line++)
            {
            intConcatenated = "";
            for (int nb : grid->getLine(grid->getGenNumber()))
            {
                intConcatenated += std::to_string(nb);
            }
            outputFile <<  + "\n";
            }
        }
    }
}

void Game::graphic()
{
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
            if (running)
            {
                grid->nextGen();
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

    grid->clear(); // Vide la grille 
    int x , y;
    for (std::string line; std::getline(file, line); ){
        std::vector<Cell*> row;
        for (char c : line)
           if (c == '0')
            {
                row.push_back(new Alive_Cell(x, y));
                x++;
            }
            else if (c == '1')
            {
                row.push_back(new Dead_Cell(x, y));
                x++;
            }
        y++;
        if (!row.empty()) grid->addLine(row);    //si ligne valide(contient data) alors ajout ligne a la grille 
    }
}