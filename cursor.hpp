#ifndef CURSOR_HPP
#define CURSOR_HPP
#include <iostream>
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <string>

class Game;

class Cursor {
private:
    int x; 
    int y; 
public:
    Cursor();

    Cursor(int x, int y); 

    sf::Vector2i getPosition() const; 

    void clicOnCell(const sf::Event* event, Game* game);

    void updatePosition(int x , int y);
};

#endif