#ifndef CELL_HPP
#define CELL_HPP
#include "grid.hpp"
#include <SFML/Graphics.hpp>

class Grid;

class Cell
{
public:
    Cell();
    ~Cell();
    virtual void update(Grid *grid) = 0;
    int getX() const, getY() const;
    bool getValue() const;
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
    void setNeighbours(int aliveNeighbours);
    void update(Grid *grid) override;
};

class constCell : public Cell 
{
public:
    constCell(int x, int y, bool value);
    void update(Grid *grid) override;
};

#endif