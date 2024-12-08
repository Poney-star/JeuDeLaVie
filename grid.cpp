#include "grid.hpp"
#include <iostream>

// Initialisation du membre statique
int Grid::genNumber = 0;

sf::Texture Grid::deadCellTexture, Grid::aliveCellTexture, Grid::constDeadCellTexture, Grid::constAliveCellTexture;

bool Grid::loadTextures()
{
    if(!deadCellTexture.loadFromFile("assets/textures/DeadCellTexture.png") && !aliveCellTexture.loadFromFile("assets/textures/AliveCellTexture.png") && !constDeadCellTexture.loadFromFile("assets/textures/DeadCellTexture.png") && !constAliveCellTexture.loadFromFile("assets/textures/AliveCellTexture.png"));
    {
        return false;
    }
    return true;
}
//Constructeur
Grid::Grid(int width, int height) : width(width), height(height){
    elements = {{}};
}

// Destructeur
Grid::~Grid()
{
    for (std::vector<Cell*> row : elements)
    {
        for (Cell* cell : row) {
            delete cell; // Libération de la mémoire de chaque cellule
        }
    }
}

// Méthode pour récupérer les voisins d'une cellule
sf::Vector2i Grid::getNeighbours(Cell* element) {
    sf::Vector2i neighbours(0, 0);
    int x = element->getX();
    int y = element->getY();
    (typeid(*elements[y - 1 < 0 ? height - 1 : y - 1][x - 1 < 0 ? width - 1 : x -  1]) == typeid(Alive_Cell)) ? neighbours.x += 1 : neighbours.y += 1;
    (typeid(*elements[y][x - 1 < 0 ? width - 1 : x -  1]) == typeid(Alive_Cell)) ? neighbours.x += 1 : neighbours.y += 1;
    (typeid(*elements[(y+1)%height][x - 1 < 0 ? width - 1 : x -  1]) == typeid(Alive_Cell)) ? neighbours.x += 1 : neighbours.y += 1;
    (typeid(*elements[y - 1 < 0 ? height - 1 : y - 1][x]) == typeid(Alive_Cell)) ? neighbours.x += 1 : neighbours.y += 1;
    (typeid(*elements[(y+1)%height][x]) == typeid(Alive_Cell)) ? neighbours.x += 1 : neighbours.y += 1;
    (typeid(*elements[y - 1 < 0 ? height - 1: y - 1][(x+1)%width]) == typeid(Alive_Cell)) ? neighbours.x += 1 : neighbours.y += 1;
    (typeid(*elements[y][(x+1)%width]) == typeid(Alive_Cell)) ? neighbours.x += 1 : neighbours.y += 1;
    (typeid(*elements[(y+1)%height][(x+1)%width]) == typeid(Alive_Cell)) ? neighbours.x += 1 : neighbours.y += 1;
    return neighbours;
}

// Méthode pour calculer l'itération suivante
void Grid::nextGen()
{
    for (std::vector<Cell*> row : elements)
    {
        for (Cell* cell : row) {
            if (!cell->isConst()) {
                cell->update(this);
            }
        }
    }
    for (std::vector<Cell*> row : elements)
    {
        for (Cell* cell : row) {
            cell->setNeighbours(this->getNeighbours(cell));
        }
    }
    ++genNumber;
}
void Grid::clear()
{
    elements = {};
}

// Méthode pour afficher la grille (mode graphique) ?????????
void Grid::display(sf::RenderWindow* window)
{
    sf::Texture texture;
    for (std::vector<Cell*> row : elements)
    {
        for (Cell* cell : row) {
            if (typeid(*cell) == typeid(Alive_Cell)) {  // Si la cellule est vivante
                // Choisir le sprite en fonction de l'état de la cellule (vivante ou constante)
                texture = cell->isConst() ? constAliveCellTexture : aliveCellTexture;
            } else {  // Si la cellule est morte
                // Choisir le sprite pour la cellule morte
                texture = cell->isConst() ? constDeadCellTexture : deadCellTexture;
            }
            cell->getSprite()->setTexture(texture);
            window->draw(*cell->getSprite());  // Dessiner le sprite sur la fenêtre
        }
    }
}

// Méthode pour inverser l'état d'une cellule (vivant/mort)
void Grid::invertCell(int x, int y)
{
    Cell* toDelete = elements[y][x];
    if (typeid(*elements[y][x]) == typeid(Alive_Cell)){
        elements[y][x] = new Dead_Cell(x, y);
    } else {
        elements[y][x] = new Alive_Cell(x, y);
    }
    delete toDelete;
}

// Méthode pour définir une cellule comme constante
void Grid::setConstant(int x, int y)
{
    elements[y][x]->setConst(); 
}

void Grid::resizeSprites(int width, int height)
{
    for (std::vector<Cell*> row : elements)
    {
        for (Cell* cell : row) {
            cell->resizeSprite(width,height,this->width,this->height);
        }
    }
}

// Accesseur pour l'itération actuelle
int Grid::getGenNumber()
{
    return genNumber;
}

int Grid::getHeight() const
{
    return height;
}

void Grid::endInit()
{
    for (std::vector<Cell*> row : elements)
    {
        for (Cell* cell : row) {
            cell->setNeighbours(this->getNeighbours(cell));
        }
    }
}
std::vector<int> Grid::getLine(int lineNumber) 
{
    std::vector<int> line;
    for (Cell* cell : elements[lineNumber])
    {
        line.push_back((typeid(*cell) == typeid(Alive_Cell))? 1 : 0);
    }
    return line;
}

sf::Vector2i Grid::getSpriteBounds()
{
    return sf::Vector2i(elements[0][0]->getSprite()->getGlobalBounds().width,elements[0][0]->getSprite()->getGlobalBounds().height);
}

void Grid::addLine(std::vector<Cell*> line)
{
    elements.push_back(line);
}

void Grid::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}