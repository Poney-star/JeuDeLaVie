#include "game.hpp"
#include <iostream>
#include <cmath>
Game::Game()
{
    window = new sf::RenderWindow();
    grid = new Grid();
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
            this.graphic();
            break;
        } 
        else if (std::find(c.begin(), c.end(), choice) != c.end())
        {
            this.console();
            break;
        }
    }
}

void Game::console()
{

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
                    this.resizeWindow(window->getSize().x,window->getSize().y);
                    break;
                case sf::Event::MouseButtonPressed:
                    cursor->clic(event);
                    break;
                case sf::Event::MouseMoved:
                    cursor->updatePosition(event.mouseMove.x, event.mouseMove.y);
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.scancode)  
                    {
                        case sf::Keyboard::Scan::Escape:
                            this.pause();
                            this.blurBackground();
                            this.pausemenu();
                            break;
                        case sf::Keyboard::Scan::Space:
                            this.pause();
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
    grid->display();
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
    this.loadFile(path);
    this.setMode();
}

void Game::loadFile(std::string path)
{  
   
}

void Game::invertCell(sf::Vector2i coordinates) const
{
    sf::Vector2i shapeBounds = grid->getSpriteBounds();
    grid->invertCell(floor(coordinates.x / shapeBounds.x),floor(coordinates.y / shapeBounds.y));
}