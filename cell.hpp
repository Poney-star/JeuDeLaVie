#ifndef CELL_HPP
#define CELL_HPP
#include "grid.hpp"
#include <SFML/Graphics.hpp>

class Cell
{
public:
    virtual void update(Grid *grid) = 0;
    void setConst();
    bool isConst() const;
    Cell(int x, int y, sf::Vector2i neighbours, bool isConstant);
    void setneighbours(sf::Vector2i neighbours);
protected:
    int x, y;
    sf::Vector2i neighbours;
    bool isConstant;
};

class Alive_Cell : public Cell 
{
public:
    virtual void update(Grid *grid) const;
};

class Dead_Cell : public Cell 
{
public:
    virtual void update(Grid *grid) const;
};

#endif