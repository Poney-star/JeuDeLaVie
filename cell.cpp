#include "cell.hpp"

void Cell::setConst(){
    isConstant = !isConstant;
}

bool Cell:: isConst() const{
    return isConstant;
}

int Cell::getX() const{
    return x;
}

int Cell::getY() const{
    return y;
}

Cell::Cell(){
    x = 0;
    y= 0;
    isConstant = false;
    neighbours = sf::Vector2i(0, 0);
}
void Alive_Cell:: update(Grid *grid) {
    if(!(neighbours.x != 2 && neighbours.x != 3))
    {
        grid->invertCell(x, y);
    }
}

Alive_Cell::Alive_Cell(int x, int y){
    this->x = x;
    this->y = y;
}

void Dead_Cell::update(Grid *grid) {   
    if (neighbours.x == 3) 
    {
        grid->invertCell(x, y);
    }
}
