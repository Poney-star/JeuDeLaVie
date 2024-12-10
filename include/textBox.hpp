#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP
#include <string>
#include <SFML/Graphics.hpp>

class TextBox{
private:
    sf::Vector2f position;
    unsigned int charLimit;
    sf::Sprite* sprite;
    sf::Text* text;
    int cursorPos;
    bool focus;
public:
    TextBox();
    TextBox(sf::Sprite* sprite, sf::Text* text, sf::Vector2f position);
    void draw(sf::RenderWindow* window) const;
    void changeFocusState();
    void moveCursor(int mov);
    void addChar(std::string str);
    void deleteChar();
    void setScale(sf::Vector2f scaleFactor);
    bool getFocusState() const;
    std::string getString() const;
};

#endif