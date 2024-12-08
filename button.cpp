#include "button.hpp"

Button::Button() :
position(sf::Vector2f(0, 0)),
buttonText(nullptr)
{}

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
    buttonText->setFont(font);
    buttonText->setString(text);
    buttonText->setCharacterSize(fontSize);
    buttonText->setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = buttonText->getLocalBounds();
    buttonText->setPosition(
        position.x + (shape.getSize().x - textBounds.width) / 2 - textBounds.left,
        position.y + (shape.getSize().y - textBounds.height) / 2 - textBounds.top
    );
}

void Button::setText(sf::Text* text)
{
    buttonText = text;
    buttonText->setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = buttonText->getLocalBounds();
    buttonText->setPosition(
        position.x + (shape.getSize().x - textBounds.width) / 2 - textBounds.left,
        position.y + (shape.getSize().y - textBounds.height) / 2 - textBounds.top
    );
}

void Button::setScale(sf::Vector2f scaleFactor)
{
    shape.setOrigin(scaleFactor.x * position.x, scaleFactor.y * position.x);
    buttonText->setScale(scaleFactor);
}

void Button::update(sf::Vector2i mousePos, sf::RenderWindow* ctx) {
    if (isHovered(mousePos)) {
        shape.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            shape.setFillColor(activeColor);
        }
    } else {
        shape.setFillColor(idleColor);            
    }
    ctx->draw(shape); 
    ctx->draw(*buttonText); 
}

void Button::setPosition(float x, float y) {
    shape.setPosition(sf::Vector2f(x, y));
}

void Button::setSize(float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
}

bool Button::isHovered(sf::Vector2i mousePos) {
    sf::FloatRect bounds = shape.getGlobalBounds();
    if (bounds.contains(mousePos.x, mousePos.y))
    {
        return true;
    }
    return false;
}