#ifndef SETTINGS_HPP
#define SETTINGS_HPP
#include <SFML/Graphics.hpp>
#include "game.hpp"

class Settings
{
private:
    sf::Sprite background;
    Game* game;
public:
    void open();
    void close();
};

#endif