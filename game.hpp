#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "grid.hpp"
#include "graphicsManager.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <cmath>
#include <thread>
#include <chrono>

class GraphicsManager;
class Grid;
class Cell;

class Game {
private:
    GraphicsManager* renderer;
    Grid* grid; 
    bool running;
    std::chrono::seconds interval;
    int genMax;
public:
    Game(GraphicsManager* gM);
    void setGenMax(int nb);
    void console();
    void graphic();
    void display() const;
    void pause();
    bool loadFile(const std::string path);
    std::vector<Cell*> resizeLine(unsigned int width, std::vector<Cell*> row,unsigned int x ,unsigned int y) const;
    void invertCell(sf::Vector2i coordinates) const;
    void setConstantCell(sf::Vector2i coordinates) const;
};

#endif