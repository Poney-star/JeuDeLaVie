#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "grid.hpp"
#include "cursor.hpp"

class Game {
private:
    Cursor *cursor;
    Grid *grid;
    sf::RenderWindow *window;
    bool running;
    int interval;
    int genMax;
public:
    Game();
    void resizeWindow(int width, int height) const;
    void setMode();
    void console();
    void graphic();
    void display() const;
    void pause();
    void init();
    void loadFile(const std::string path);
    std::vector<Cell*> resizeLine(int width, std::vector<Cell*> row,int x ,int y) const;
    void invertCell(sf::Vector2i coordinates) const;
    void setConstantCell(sf::Vector2i coordinates) const;
};

#endif