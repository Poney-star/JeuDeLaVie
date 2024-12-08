#include "textBox.hpp"

TextBox::TextBox()
{
    position = sf::Vector2f(0, 0);
    charLimit = 0;
    sprite = nullptr;
    text = nullptr;
    cursorPos = 0;
    focus = false;
}

TextBox::TextBox(sf::Sprite* sprite, sf::Text* text, sf::Vector2f position) :
position(position),
charLimit(80),
sprite(sprite),
text(text),
cursorPos(0),
focus(false)
{}

void TextBox::draw(sf::RenderWindow* window) const
{
    window->draw(*sprite);
    window->draw(*text);
}

void TextBox::moveCursor(int mov)
{
    if (cursorPos + mov < text->getString().getSize() + 1 && cursorPos + mov > 0) cursorPos += mov; 
}

std::string TextBox::getString() const
{
    return text->getString();
}

void TextBox::addChar(std::string str)
{
    if (charLimit > text->getString().getSize()) text->setString(text->getString() + str);
    cursorPos += 1;
}

void TextBox::deleteChar()
{
    if (cursorPos != 0) 
    {
        std::string str = text->getString();
        str.erase(cursorPos - 1, 1);
        cursorPos-=1;
        text->setString(str);
    }
}

bool TextBox::getFocusState() const
{
    return focus;
}
/*
void TextBox::focusOn(sf::RenderWindow* window)
{
    while (focus)
    {
        sf::Event event;
        window->pollEvent(event);
        switch (event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::Resized:
                break;
            case sf::Event::KeyPressed:
                    switch(event.key.code)  
                    {
                        case sf::Keyboard::Escape:
                            changeFocusState();
                            break;
                        case sf::Keyboard::Backspace:
                            deleteChar();
                            break;
                        default:
                            addChar(sf::Keyboard::getDescription(event.key.scancode));
                            window->draw(*sprite);
                            window->draw(*text);
                            break;
                    }
                    break;
        }
        window->display();    
    }
}
*/

void TextBox::setScale(sf::Vector2f scaleFactor)
{
    sprite->setScale(scaleFactor);
    text->setScale(scaleFactor);
}

void TextBox::changeFocusState()
{
    focus = !focus;
}