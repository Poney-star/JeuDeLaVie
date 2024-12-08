#include "cell.hpp"
#include <iostream>

//Constructeur

Cell::Cell(){
    x = 0;
    y= 0;
    value = 0;
}

Cell::~Cell()
{
    delete this;
}

//Accesseurs

int Cell::getX() const
{
    return x;
}

int Cell::getY() const
{
    return y;
}

bool Cell::getValue() const
{
    return value;
}

void Cell::invertValue()
{
    value = !value;
}

//Constructeur / Destructeur

mutableCell::mutableCell(int x, int y, bool value) :aliveNeighbours(0)
{ 
    this->x = x; 
    this->y = y; 
    this->value = value;
}

mutableCell::~mutableCell()
{
    delete this;
}

//Méthodes

void mutableCell::setNeighbours(int aliveNeighbours)
{
    this->aliveNeighbours = aliveNeighbours;
}

void mutableCell::update(Grid *grid) {
    if(this->aliveNeighbours != 2 && this->aliveNeighbours != 3 && this->value == 1)
    {
        value = 0;
    } else if (this->aliveNeighbours == 3 && this->value == 0)
    {
        value = 1;
    }
}

//Constructeur / Destructeur

constCell::constCell(int x, int y, bool value)
{
    this->x = x;
    this->y = y;
    this->value = value;
}

constCell::~constCell()
{
    delete this;
}

//Méthode

void constCell::update(Grid *grid)
{}