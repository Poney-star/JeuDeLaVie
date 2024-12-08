#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef CURSOR_HPP
#define CURSOR_HPP

class Game;

class Cursor {
    private:
    int x; // Position X du curseur
    int y; // Position Y du curseur

    public:
    Cursor(); // Constructeur par défaut

    Cursor(int x, int y); 

    sf::Vector2i getPosition() const; // Retourne la position actuelle

    void clicOnCell(const sf::Event* event, Game* game);

    void updatePosition(int x , int y);
};

#endif