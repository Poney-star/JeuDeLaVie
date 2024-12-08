#include "graphicsManager.hpp"

//Constructeur / Destructeurs

GraphicsManager::GraphicsManager()
{
    if(loadAssets())
    {
        window.create(sf::VideoMode(800,600), "Pig Dance");
    }
}


// Accesseurs


sf::RenderWindow* GraphicsManager::getWindow() 
{
    return &window;
}

sf::Texture* GraphicsManager::getTexture(std::string str)
{
    return (textures.find(str) == textures.end())? &textures.at(str) : nullptr;
}

sf::Font* GraphicsManager::getFont(std::string str)
{
    return(fonts.find(str) == fonts.end())? &fonts.at(str) : nullptr;
}

//Méthodes

bool GraphicsManager::loadAssets()
{
    textures["background"].loadFromFile("assets/textures/deadCellTexture.png");
    textures["aliveCell"].loadFromFile("assets/textures/aliveCellTexture.png");
    textures["deadCell"].loadFromFile("assets/textures/deadCellTexture.png");
    fonts["title"].loadFromFile("assets/fonts/title-font.ttf");
    fonts["menu_button"].loadFromFile("assets/fonts/title-font.ttf");
}

void GraphicsManager::renderMenu()
{
    
}