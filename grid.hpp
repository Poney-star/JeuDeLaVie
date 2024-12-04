#ifndef GRID_H
#define GRID_H

#include <list>
#include <SFML/Graphics.hpp>
#include "cell.hpp"

class Grid {
private:
    std::list<Cell*> elements;       // Liste contenant toutes les cellules
    int width;                       // Largeur de la grille
    int height;                      // Hauteur de la grille
    sf::Sprite deadCellSprite;       // Sprite pour les cellules mortes
    sf::Sprite aliveCellSprite;      // Sprite pour les cellules vivantes
    sf::Sprite constDeadCellSprite;  // Sprite pour les cellules mortes constantes
    sf::Sprite constAliveCellSprite; // Sprite pour les cellules vivantes constantes
    static int genNumber;            // Numéro de la itération actuelle

public:
    // Constructeur et destructeur
    Grid(int width, int height);
    ~Grid();

    // Méthodes principales
    std::list<Cell*> getNeighbours(Cell* element); // Obtenir les voisins
    void nextGen();                                // Calculer la prochaine itération
    void display(sf::RenderWindow* window);        // Afficher la grille (mode graphique)
    void invertCell(int x, int y);                 // Inverser l'état d'une cellule
    void setConstant(int x, int y);                // Définir une cellule comme constante
    void resizeSprites(int cellWidth, int cellHeight); // Redimensionner les sprites

    // Accesseur pour la itération actuelle
    static int getGenNumber();
};

#endif // GRID_H