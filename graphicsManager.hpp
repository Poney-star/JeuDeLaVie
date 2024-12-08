#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP
#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "game.hpp"
#include <map>

class GraphicsManager
{
private:
sf::RenderWindow window;
Menu menu;
std::map<std::string, sf::Texture> textures;
std::map<std::string, sf::Font> fonts;

public:
    //Constructeur / Destructeur
    GraphicsManager();
    //Accesseurs
    sf::RenderWindow* getWindow();
    sf::Texture* getTexture(std::string str);
    sf::Font* getFont(std::string str);
    //Méthodes
    void renderMenu();
    bool loadAssets();
};

#endif