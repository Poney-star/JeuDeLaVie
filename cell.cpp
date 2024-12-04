#include "cell.hpp"

void Cell::setConst(){
    isConstant = !isConstant;
}

bool Cell:: isConst() const{
    return isConstant;
}

void Alive_Cell:: update(Grid *grid) const{
    if(!(neighbours.x != 2 && neighbours.x != 3))
    {
        grid->invertCell(x, y);
    }
}

void Dead_Cell::update(Grid *grid) const{   
    if (neighbours.x == 3) 
    {
        grid->invertCell(x, y);
    }
}
