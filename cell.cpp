#include "cell.hpp"

//Constructeur

Cell::Cell() : x(0), y(0), value(0)
{}

Cell::~Cell()
{}

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

void Cell::invertValue(GraphicsManager* renderer)
{
    value = !value;
    renderer->addToCheck(this);
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
{}

//Méthodes

void mutableCell::setNeighbours(int aliveNeighbours)
{
    this->aliveNeighbours = aliveNeighbours;
}

void mutableCell::update(GraphicsManager* renderer) {
    if(this->aliveNeighbours != 2 && this->aliveNeighbours != 3 && this->value == 1)
    {
        invertValue(renderer);
    }
    else if (this->aliveNeighbours == 3 && this->value == 0)
    {
        invertValue(renderer);
    }
}

void mutableCell::update() {
    if(this->aliveNeighbours != 2 && this->aliveNeighbours != 3 && this->value == 1)
    {
        invertValue();
    }
    else if (this->aliveNeighbours == 3 && this->value == 0)
    {
        invertValue();
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
{}

//Méthode

void constCell::update(GraphicsManager* renderer)
{
    invertValue(renderer);
}

void constCell::update()
{
    invertValue();
}