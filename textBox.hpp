#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP
#include "game.hpp"
#include <string>
#include <SFML/Graphics.hpp>

class TextBox{
private:
    Game *game;
    sf::Vector2f position;
    int charLimit;
    sf::Sprite *sprite;
    sf::Text text;
    int cursorPos;
    sf::RenderWindow *window;
    bool focus;
public:
    TextBox(Game *game, sf::RenderWindow *window, sf::Sprite *sprite, sf::Font font);
    void display() const;
    void changeFocusState();
    void addChar(std::string str);
    void deleteChar();
    void focusOn();
    std::string getString() const;
};

#endif