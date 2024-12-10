#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP
#include <SFML/Graphics.hpp>
#include "textBox.hpp"
#include "cursor.hpp"
#include "button.hpp"
#include "game.hpp"
#include "cell.hpp"
#include <map>
#include <chrono>
#include <thread>
#include <variant>
#include <fstream>

class Cursor;
class Cell;
class mutableCell;
class constCell;
class Game;

class GraphicsManager
{
private:
    Cursor cursor;
    sf::RenderWindow window;
    sf::Vector2f originalSize;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Sprite> sprites;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::Text> texts;
    std::map<std::string, TextBox> textBoxes;
    std::map<std::string, Button> buttons;
    std::vector<std::variant<sf::Sprite*, sf::Text*, TextBox*, Button*, mutableCell*, constCell*, Cell*>> toCheck;

public:
    // Constructeur / Destructeur
    GraphicsManager();
    // Accesseurs
    sf::RenderWindow* getWindow();
    Cursor* getCursor();
    sf::Texture* getTexture(std::string str);
    sf::Sprite* getSprite(std::string str);
    sf::Font* getFont(std::string str);
    sf::Text* getText(std::string str);
    Button* getButton(std::string str);
    TextBox* getTextBox(std::string str);
    // Méthodes d'affichage
    void renderStartMenu();
    void renderSFAMMenu(); //render SFAM (Select File And Mode) Menu
    void renderGame(Game* game);
    void display();
    void displayGameCells(int width, int height);
    // Autres
    void handleEvents();
    void buttonActivatedMenu(sf::Vector2i);
    void buttonActivatedSFAMMenu(sf::Vector2i mousePos);
    bool loadAssets();
    void addToCheck(std::variant<sf::Sprite*, sf::Text*, TextBox*, Button*, mutableCell*, constCell*, Cell*> obj);
};
#endif