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
    void setNeighbours(sf::Vector2i neighbours);
    void resizeSprite(int width, int height, int windowWidth, int windowHeight);
    int getX() const, getY() const;
    sf::Sprite* getSprite() const;
protected:
    sf::Sprite* sprite;
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