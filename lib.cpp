#include "lib.hpp"

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
void Grid::display(sf::RenderWindow& window) {
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
        window.draw(sprite);  // Dessiner le sprite sur la fenêtre
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

Game::Game()
{
    window = new sf::RenderWindow();
    grid = new Grid();
    cursor = new Cursor();
}

void Game::resizeWindow(int width, int height) const
{
    grid->resizeSprites(width, height);
    window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
}

void Game::setMode()
{
    std::string choice;
    /*int gridWidth;
    int gridHeight;*/
    const std::vector<std::string> g = {"g","G","GRAPHIQUE","graphique"};
    const std::vector<std::string> c = {"c","C","CONSOLE","console"};
    // Dans le cas d'une taille non fixée par le fichier :
    /* 
    std::cout << "Indiquer la hauteur de la grille:" << std::endl;
    std::cin >> gridHeight;
    std::cout << "Indiquer la largeur de la grille:" << std::endl;
    std::cin >> gridWidth;
    grid -> setSize(gridWidth, gridHeight);
    */
    while(1)
    {
        std::cout << "Indiquer le mode (graphique/console): "<< std::endl;
        std::cin >> choice;
        if (std::find(g.begin(), g.end(), choice) != g.end())
        {
            this.graphic();
            break;
        } 
        else if (std::find(c.begin(), c.end(), choice) != c.end())
        {
            this.console();
            break;
        }
    }
}

void Game::console()
{

}

void Game::graphic()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::Resized:
                    this.resizeWindow(window->getSize().x,window->getSize().y);
                    break;
                case sf::Event::MouseButtonPressed:
                    cursor->clic(event);
                    break;
                case sf::Event::MouseMoved:
                    cursor->updatePosition(event.mouseMove.x, event.mouseMove.y);
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.scancode)  
                    {
                        case sf::Keyboard::Scan::Escape:
                            this.pause();
                            this.blurBackground();
                            this.pausemenu();
                            break;
                        case sf::Keyboard::Scan::Space:
                            this.pause();
                            break;
                    }
                    break;
            }
            if (running)
            {
                grid->nextGen();
            }
        }
    }
}

void Game::display() const
{
    grid->display();
}

void Game::pause()
{
    running = !running;
}

void Game::init()
{
    std::string path;
    std::cout << "Indiquer le chemin d'accès du fichier: ";
    std::cin >> path;
    this.loadFile(path);
    this.setMode();
}

void Game::loadFile(std::string path)
{  
   
}

void Game::invertCell(sf::Vector2i coordinates) const
{
    sf::Vector2i shapeBounds = grid->getSpriteBounds();
    grid->invertCell(floor(coordinates.x / shapeBounds.x),floor(coordinates.y / shapeBounds.y));
}

Cursor::Cursor() : x(0), y(0) {}

Cursor::Cursor(int x, int y) : x(x), y(y) {}


sf::Vector2i Cursor::getPosition() const {
    return sf::Vector2i(x, y);
}


void Cursor::clic(const sf::Event& event, Game& game) {

        if (event.mouseButton.button == sf::Mouse::Left) { // Si clic gauche
            game.invertCell(getPosition()); // Appelle invertCell avec la position actuelle du curseur
        } else if (event.mouseButton.button == sf::Mouse::Right) { // Si clic droit
            game.setConstant(getPosition()); // Appelle setConstant avec la position actuelle du curseur
        }
}

void Cursor::updatePosition(int x, int y) : x(x), y(y)

void Cell::setConst(){
    isConstant = !isConstant;
}

bool Cell:: isConst() const{
    return isConstant;
}

void Alive_Cell:: update(Grid &grid) const{
    if(!(neighbours.x != 2 && neighbours.x != 3))
    {
        grid->invertCell(x, y);
    }
}

void Dead_Cell::update(Grid &grid) const{   
    if (neighbours.x == 3) 
    {
        grid->invertCell(x, y);
    }
}
