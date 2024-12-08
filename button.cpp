#include "button.hpp"


// Implémentation de la classe Button

Button::Button(float x, float y, float width, float height, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor):
position(sf::Vector2f(x, y)),
shape(sf::Vector2f(width, height)),
idleColor(idleColor),
hoverColor(hoverColor),
activeColor(activeColor)
{
    shape.setPosition(position);
    shape.setFillColor(idleColor); 
}

void Button::setText(const std::string& text, sf::Font& font, unsigned int fontSize)
{
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(fontSize);
    buttonText.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        position.x + (shape.getSize().x - textBounds.width) / 2 - textBounds.left,
        position.y + (shape.getSize().y - textBounds.height) / 2 - textBounds.top
    );
}

void Button::windowResized(int width, int height, sf::Vector2f scaleFactor)
{
    shape.setScale(scaleFactor);
    position.x = position.x * scaleFactor.x;
    position.y = position.y * scaleFactor.y;
    shape.setPosition(position.x, position.y);
    buttonText.setPosition(
        position.x + (shape.getSize().x - buttonText.getLocalBounds().width) / 2 - buttonText.getLocalBounds().left,
        position.y + (shape.getSize().y - buttonText.getLocalBounds().height) / 2 - buttonText.getLocalBounds().top
    );
}

void Button::update(sf::Vector2i mousePos, sf::RenderWindow* ctx) {
    sf::FloatRect bounds = shape.getGlobalBounds();

    if (bounds.contains(mousePos.x, mousePos.y)) {
        shape.setFillColor(hoverColor);           
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            shape.setFillColor(activeColor);
        }
    } else {
        shape.setFillColor(idleColor);            
    }

    ctx->draw(shape); 
    ctx->draw(buttonText); 
}

void Button::setPosition(float x, float y) {
    shape.setPosition(sf::Vector2f(x, y));
}

void Button::setSize(float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
}

bool Button::isHovered(sf::Vector2i mousePos) {
    sf::FloatRect bounds = shape.getGlobalBounds();
    return bounds.contains(mousePos.x, mousePos.y);
}