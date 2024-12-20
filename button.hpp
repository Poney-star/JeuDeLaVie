#ifndef BOUTONS_HPP
#define BOUTONS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class Button {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    sf::Text buttonText;

public:

    Button(float x, float y, float width, float height, 
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    void windowResized(int width, int height, sf::Vector2f scaleFactor);
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setText(const std::string& text, sf::Font& font, unsigned int fontSize);

    void update(sf::Vector2i mousePos, sf::RenderWindow* ctx);
    bool isHovered(sf::Vector2i mousePos);
};

#endif