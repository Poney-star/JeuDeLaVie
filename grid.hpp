#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include "cell.hpp"

class Cell;

class Grid {
private:
    std::vector<std::vector<Cell*>> elements;       // Liste contenant toutes les cellules
    int width;                                      // Largeur de la grille
    int height;                                     // Hauteur de la grille
    static sf::Texture deadCellTexture, aliveCellTexture, constDeadCellTexture, constAliveCellTexture;
    static int genNumber;                           // Numéro de la itération actuelle

public:
    // Constructeur et destructeur
    Grid(int width, int height);
    ~Grid();

    // Méthodes principales
    bool loadTextures();
    void setSize(int width, int height);
    void clear();                                       // Nettoyer la grille
    void endInit();
    void addLine(std::vector<Cell*>);                   // Ajoute une ligne à la grille
    sf::Vector2i getNeighbours(Cell* element);    // Obtenir les voisins
    void nextGen();                                     // Calculer la prochaine itération
    void display(sf::RenderWindow* window);             // Afficher la grille (mode graphique)
    void invertCell(int x, int y);                      // Inverser l'état d'une cellule
    void setConstant(int x, int y);                     // Définir une cellule comme constante
    void resizeSprites(int cellWidth, int cellHeight);  // Redimensionner les sprites
    sf::Vector2i getSpriteBounds();
    std::vector<int> getLine(int lineNumber);

    // Accesseur pour la itération actuelle
    static int getGenNumber();
    int getHeight() const;
};

#endif // GRID_H