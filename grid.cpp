#include "grid.hpp"

// Initialisation du membre statique
int Grid::genNumber = 0;

// Destructeur
Grid::~Grid() {
    for (Cell* cell : elements) {
        delete cell; // Libération de la mémoire de chaque cellule
    }
}

// Méthode pour récupérer les voisins d'une cellule
std::list<Cell*> Grid::getNeighbours(Cell* element) {
    std::list<Cell*> neighbours;
    int x = element->getX();
    int y = element->getY();

    // Parcourir les 8 voisins
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue; // Ignorer la cellule elle-même

            int nx = x + dx;
            int ny = y + dy;

            // Vérifier si les coordonnées sont dans la grille
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                for (Cell* cell : elements) {
                    if (cell->getX() == nx && cell->getY() == ny) {
                        neighbours.push_back(cell);  // Ajouter le voisin à la liste
                    }
                }
            }
        }
    }
    return neighbours;
}

// Méthode pour calculer l'itération suivante
void Grid::nextGen() {
    for (Cell* cell : elements) {
        if (!cell->isConst()) { // Ne pas mettre à jour les cellules constantes
            cell->update();
        }
    }
    ++genNumber;
}

// Méthode pour afficher la grille (mode graphique) ?????????
void Grid::display(sf::RenderWindow* window) {
    for (Cell* cell : elements) {
        sf::Sprite sprite;
        if (cell->isAlive()) {  // Si la cellule est vivante
            // Choisir le sprite en fonction de l'état de la cellule (vivante ou constante)
            sprite = cell->isConst() ? constAliveCellSprite : aliveCellSprite;
        } else {  // Si la cellule est morte
            // Choisir le sprite pour la cellule morte
            sprite = cell->isConst() ? constDeadCellSprite : deadCellSprite;
        }
        // Placer le sprite à la position appropriée de la cellule
        sprite.setPosition(cell->getX() * sprite.getLocalBounds().width,
                           cell->getY() * sprite.getLocalBounds().height);
        window->draw(sprite);  // Dessiner le sprite sur la fenêtre
    }
}

// Méthode pour inverser l'état d'une cellule (vivant/mort)
void Grid::invertCell(int x, int y) {
    for (Cell* cell : elements) {
        if (cell->getX() == x && cell->getY() == y) {
            if (cell->isAlive()) {
                delete cell;
                cell = new Dead_Cell(x, y);
            } else {
                delete cell;
                cell = new Alive_Cell(x, y);
            }
            break;
        }
    }
}

// Méthode pour définir une cellule comme constante
void Grid::setConstant(int x, int y) {
    for (Cell* cell : elements) {
        if (cell->getX() == x && cell->getY() == y) {
            cell->setConst();  // Marquer la cellule comme constante
            break;
        }
    }
}

// Méthode pour redimensionner les sprites !!!!!!!!!!!
void Grid::resizeSprites(float cellWidth, float cellHeight) {
    deadCellSprite.setScale(cellWidth / deadCellSprite.getLocalBounds().width,
                            cellHeight / deadCellSprite.getLocalBounds().height);
    aliveCellSprite.setScale(cellWidth / aliveCellSprite.getLocalBounds().width,
                             cellHeight / aliveCellSprite.getLocalBounds().height);
    constDeadCellSprite.setScale(cellWidth / constDeadCellSprite.getLocalBounds().width,
                                 cellHeight / constDeadCellSprite.getLocalBounds().height);
    constAliveCellSprite.setScale(cellWidth / constAliveCellSprite.getLocalBounds().width,
                                  cellHeight / constAliveCellSprite.getLocalBounds().height);
}

// Accesseur pour l'itération actuelle
int Grid::getGenNumber() {
    return genNumber;
}