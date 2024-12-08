#include "textBox.hpp"

TextBox::TextBox(Game *game, sf::RenderWindow *window, sf::Sprite *sprite, sf::Font font) :
game(game), 
position(
    sf::Vector2f(
        sprite->getGlobalBounds().left,
        sprite->getGlobalBounds().top
    )
),
charLimit(80),
sprite(sprite),
text(sf::Text("", font)),
cursorPos(0),
window(window)
{
    text.setFillColor(sf::Color::White);
    text.setPosition(position.x + 5, position.y + sprite->getGlobalBounds().height - text.getGlobalBounds().height);
}

void TextBox::display() const
{
    window->draw(*sprite);
    window->draw(text);
}

void TextBox::addChar(std::string str)
{
    text.setString(text.getString() + str);
}

void TextBox::deleteChar()
{
    std::string str = text.getString();
    str.erase(cursorPos, 1);
    text.setString(str);
}

void TextBox::focusOn()
{
    while (focus)
    {
        sf::Event event;
        switch (event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::Resized:
                game->resizeWindow(window->getSize().x,window->getSize().y);
                break;
            case sf::Event::KeyPressed:
                    switch(event.key.code)  
                    {
                        case sf::Keyboard::Escape:
                            changeFocusState();
                            break;
                        case sf::Keyboard::Space:
                            addChar(sf::Keyboard::getDescription(event.key.scancode));
                            break;
                    }
                    break;
        }    
    }
}

void TextBox::changeFocusState()
{
    focus != focus;
}

std::string TextBox::getString() const
{
    return text.getString();
}