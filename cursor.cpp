#include <string>
#include <iostream>
#include "cursor.hpp"
#include "game.hpp"

Cursor::Cursor() : x(0), y(0) {}

Cursor::Cursor(int x, int y) : x(x), y(y) {}


sf::Vector2i Cursor::getPosition() const {
    return sf::Vector2i(x, y);
}


void Cursor::clicOnCell(const sf::Event* event, Game* game) {

    if (event->mouseButton.button == sf::Mouse::Left) { // Si clic gauche
        game->invertCell(this->getPosition()); // Appelle invertCell avec la position actuelle du curseur
    } else if (event->mouseButton.button == sf::Mouse::Right) { // Si clic droit
        game->setConstantCell(this->getPosition()); // Appelle setConstant avec la position actuelle du curseur
    }
}

void Cursor::updatePosition(int x, int y) {
    this->x = x;
    this->y = y;
}