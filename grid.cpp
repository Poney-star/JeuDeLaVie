#include "grid.hpp"

// Constructeur / Destructeur

Grid::Grid(int width, int height) : 
width(width), 
height(height), 
genNumber(0), 
elements({})
{}

Grid::~Grid()
{
    for (Cell* cell : elements) {
        delete cell;
    }
}

// Méthodes

void Grid::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

int Grid::getNeighbours(int x, int y) {
    int neighbours = 0;
    if (elements[(y - 1 < 0 ? height - 1 : y - 1 ) * width + (x - 1 < 0 ? width - 1 : x -  1)]->getValue() == true) neighbours += 1;
    if (elements[y * width + (x - 1 < 0 ? width - 1 : x -  1)]->getValue() == true) neighbours += 1;
    if (elements[((y+1)%height) * width + (x - 1 < 0 ? width - 1 : x -  1)]->getValue() == true) neighbours += 1;
    if (elements[(y - 1 < 0 ? height - 1 : y - 1) * width + x]->getValue() == true) neighbours += 1;
    if (elements[((y+1)%height) * width + x]->getValue() == true) neighbours += 1;
    if (elements[(y - 1 < 0 ? height - 1: y - 1) * width + ((x+1)%width)]->getValue() == true) neighbours += 1;
    if (elements[y * width + ((x+1)%width)]->getValue() == true) neighbours += 1;
    if (elements[((y+1)%height) * width + ((x+1)%width)]->getValue() == true) neighbours += 1;
    return neighbours;
}

void Grid::nextGen()
{
    for (Cell* cell : elements) {
        mutableCell* mCell = dynamic_cast<mutableCell*>(cell);
        if (mCell) {
            cell->update();
        }
    }
    updateNeighbours();
    ++genNumber;
}

void Grid::nextGen(GraphicsManager* renderer)
{
    for (Cell* cell : elements) {
        mutableCell* mCell = dynamic_cast<mutableCell*>(cell);
        if (mCell) {
            cell->update(renderer);
        }
    }
    updateNeighbours();
    ++genNumber;
}

void Grid::invertValue(int x, int y, GraphicsManager* renderer)
{
    elements[y * width + x]->invertValue(renderer);
    if (mutableCell* mCell = dynamic_cast<mutableCell*>(elements[(y - 1 < 0 ? height - 1 : y - 1 ) * width + (x - 1 < 0 ? width - 1 : x -  1)])) mCell->setNeighbours(getNeighbours((x - 1 < 0 ? width - 1 : x -  1), (y - 1 < 0 ? height - 1 : y - 1 )));
    if (mutableCell* mCell = dynamic_cast<mutableCell*>(elements[y * width + (x - 1 < 0 ? width - 1 : x -  1)])) mCell->setNeighbours(getNeighbours((x - 1 < 0 ? width - 1 : x -  1), y));
    if (mutableCell* mCell = dynamic_cast<mutableCell*>(elements[((y+1)%height) * width + (x - 1 < 0 ? width - 1 : x -  1)])) mCell->setNeighbours(getNeighbours((x - 1 < 0 ? width - 1 : x -  1), (y+1)%height));
    if (mutableCell* mCell = dynamic_cast<mutableCell*>(elements[(y - 1 < 0 ? height - 1 : y - 1) * width + x])) mCell->setNeighbours(getNeighbours(x, (y - 1 < 0 ? height - 1 : y - 1)));
    if (mutableCell* mCell = dynamic_cast<mutableCell*>(elements[((y+1)%height) * width + x])) mCell->setNeighbours(getNeighbours(x, (y+1)%height));
    if (mutableCell* mCell = dynamic_cast<mutableCell*>(elements[(y - 1 < 0 ? height - 1: y - 1) * width + ((x+1)%width)])) mCell->setNeighbours(getNeighbours((x+1)%width, (y - 1 < 0 ? height - 1: y - 1)));
    if (mutableCell* mCell = dynamic_cast<mutableCell*>(elements[y * width + ((x+1)%width)])) mCell->setNeighbours(getNeighbours((x+1)%width, y));
    if (mutableCell* mCell = dynamic_cast<mutableCell*>(elements[((y+1)%height) * width + ((x+1)%width)])) mCell->setNeighbours(getNeighbours((x+1)%width, (y+1)%height));
}

// Méthode pour inverser l'état d'une cellule (vivant/mort)
void Grid::invertConst(int x, int y, GraphicsManager* renderer)
{
    Cell* toDelete = elements[y * width + x];
    if (typeid(*elements[y * width + x]) == typeid(constCell)){
        elements[y * width + x] = new mutableCell(x, y, toDelete->getValue());
    } else {
        elements[y * width + x] = new constCell(x, y, toDelete->getValue());
    }
    delete toDelete;
    renderer->addToCheck(elements[y * width + x]);
}

// Accesseurs pour l'itération actuelle
int Grid::getGenNumber() const
{
    return genNumber;
}

int Grid::getHeight() const
{
    return height;
}

int Grid::getWidth() const
{
    return width;
}

std::vector<Cell*> Grid::getElements()
{
    return elements;
}

void Grid::updateNeighbours()
{
    for (Cell* cell : elements){
        mutableCell* mCell = dynamic_cast<mutableCell*>(cell);
        if (mCell)
        {
            mCell->setNeighbours(getNeighbours(mCell->getX(), mCell->getY()));
        }
    }
}

std::vector<int> Grid::getLine(int lineNumber) 
{
    std::vector<int> line;
    for (std::vector<Cell*>::iterator cell = (elements.begin() + (width * lineNumber));cell != elements.begin() + (width * (lineNumber + 1)); ++cell)
    {
        line.push_back(((*cell)->getValue())? 1 : 0);
    }
    return line;
}

void Grid::addLine(std::vector<Cell*> line, GraphicsManager* renderer)
{
    for(Cell* cell : line)
    {
        elements.push_back(cell);
    }
}

void Grid::renderAllCells(GraphicsManager* renderer)
{
    for(Cell* cell : elements)
    {
        renderer->addToCheck(cell);
    }
}