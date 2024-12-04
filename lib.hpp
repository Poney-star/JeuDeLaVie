#include <list>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

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
    void display(sf::RenderWindow& window);        // Afficher la grille (mode graphique)
    void invertCell(int x, int y);                 // Inverser l'état d'une cellule
    void setConstant(int x, int y);                // Définir une cellule comme constante
    void resizeSprites(int cellWidth, int cellHeight); // Redimensionner les sprites

    // Accesseur pour la itération actuelle
    static int getGenNumber();
};

class Game {
private:
    Cursor *cursor;
    Grid *grid;
    sf::RenderWindow *window;
    bool running;
    int interval;
public:
    Game();
    void resizeWindow(int width, int height) const;
    void setMode();
    void console();
    void graphic();
    void display() const;
    void pause();
    void init();
    void loadFile(std::string path);
    void invertCell(sf::Vector2i coordinates) const;
    void setConstantCell(sf::Vector2i coordinates) const;
};

class Cursor {
    private:
    int x, y;

    public:
    Cursor(); // Constructeur par défaut

    Cursor(int x, int y); 

    sf::Vector2i getPosition() const; // Retourne la position actuelle

    void clic(const sf::Event& event, Game &game);

    void updatePosition(int x , int y);
};

class Cell
{
public:
    virtual void update(Grid &grid) = 0;
    void setConst();
    bool isConst() const;
    Cell(int x, int y, sf::Vector2i neighbours, bool isConstant);
    void setneighbours(sf::Vector2i neighbours);
protected:
    int x, y;
    sf::Vector2i neighbours;
    bool isConstant;
};

class Alive_Cell : public Cell 
{
public:
    virtual void update(Grid &grid) const;
};

class Dead_Cell : public Cell 
{
public:
    virtual void update(Grid &grid) const;
};