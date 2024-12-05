#ifndef CELL_HPP
#define CELL_HPP
#include "grid.hpp"
#include <SFML/Graphics.hpp>

class Grid;

class Cell
{
public:
    Cell();
    virtual void update(Grid *grid) = 0;
    void setConst();
    bool isConst() const;
    Cell(int x, int y, sf::Vector2i neighbours, bool isConstant);
    void setneighbours(sf::Vector2i neighbours);
    int getX() const, getY() const;
protected:
    int x, y;
    sf::Vector2i neighbours;
    bool constant;
};

class Alive_Cell : public Cell 
{
public:
    Alive_Cell(int x, int y);
    void update(Grid *grid) override;
};

class Dead_Cell : public Cell 
{
public:
    Dead_Cell(int x, int y);
    void update(Grid *grid) override;
};

#endif