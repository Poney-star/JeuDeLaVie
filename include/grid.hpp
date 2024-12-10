#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.hpp>
#include "cell.hpp"
#include <iostream>
#include "graphicsManager.hpp"

class GraphicsManager;

class Cell;

class Grid {
private:
    std::vector<Cell*> elements;
    int width;
    int height;
    int genNumber;

public:
    // Constructeur / destructeur
    Grid(int width, int height);
    ~Grid();

    // Méthodes
    void setSize(int width, int height);
    void updateNeighbours();
    void addLine(std::vector<Cell*>, GraphicsManager* renderer);
    int getNeighbours(int x, int y);
    void nextGen();
    void nextGen(GraphicsManager* renderer);
    void invertConst(int x, int y, GraphicsManager* renderer);
    void invertValue(int x, int y, GraphicsManager* renderer);
    std::vector<int> getLine(int lineNumber);
    void renderAllCells(GraphicsManager* renderer);

    // Accesseur pour la itération actuelle
    int getGenNumber() const;
    int getHeight() const;
    int getWidth() const;
    std::vector<Cell*> getElements();
};

#endif // GRID_H