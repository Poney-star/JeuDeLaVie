#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "settings.hpp"

class Menu {
private :
    sf::Text title;
    sf::RenderWindow window;
    Button* startButton;
    Button* settingsButton;
    Button* quitButton;
    Game* game;
    sf::Font font;
    sf::Sprite background;
public:
    Menu();
    bool loadAssets();
    void start();
    void settings();
    void quit();
    void update(sf::RenderWindow &window);
};

#endif