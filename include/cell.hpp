#ifndef CELL_HPP
#define CELL_HPP
#include "grid.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class GraphicsManager;

class Grid;

class Cell
{
public:
    Cell();
    virtual ~Cell();
    virtual void update(GraphicsManager* renderer) = 0;
    virtual void update() = 0;
    int getX() const, getY() const;
    bool getValue() const;
    void invertValue(GraphicsManager* renderer);
    void invertValue();
protected:
    bool value;
    int x, y;
};

class mutableCell : public Cell 
{
private:
    int aliveNeighbours;
public:
    mutableCell(int x, int y, bool value);
    ~mutableCell();
    void setNeighbours(int aliveNeighbours);
    void update(GraphicsManager* renderer) override;
    void update() override;
};

class constCell : public Cell 
{
public:
    constCell(int x, int y, bool value);
    ~constCell();
    void update(GraphicsManager* renderer) override;
    void update() override;
};

#endif