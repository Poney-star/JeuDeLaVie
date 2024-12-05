#include "cell.hpp"

void Cell::setConst(){
    constant = !constant;
}

bool Cell:: isConst() const{
    return constant;
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
    constant = false;
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
    this->constant = false;
}

Dead_Cell::Dead_Cell(int x, int y){
    this->x = x;
    this->y = y;
    this->constant = false;
}

void Dead_Cell::update(Grid *grid) {   
    if (neighbours.x == 3) 
    {
        grid->invertCell(x, y);
    }
}
