#include "menu.hpp"

Menu::Menu()
{
    if(!loadAssets())
    {
        std::cerr<<"Impossible de charger les textures ou les polices."<<std::endl;
    }
    //Boutons
    startButton = new Button(200.f, 100.f, 200.f, 50.f, sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(100, 100, 100));
    startButton->setText("Start", font, 20);
    
    settingsButton = new Button(200.f, 175.f, 200.f, 50.f, sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(100, 100, 100));
    settingsButton->setText("Settings", font, 20);

    quitButton = new Button(200.f, 250.f, 200.f, 50.f, sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(100, 100, 100));
    quitButton->setText("Quit", font, 20);
    //Titre
    sf::Text title("Le Jeu de la Vie", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(65, 19);

    game = new Game();
}

bool Menu::loadAssets()
{
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/textures/DeadCellTexture.png"))
    {
        std::cerr << "Erreur : Impossible de charger l'image de fond." << std::endl;
        return 0;
    }
    background.setTexture(backgroundTexture);
    background.setScale(1,1);
    if (!font.loadFromFile("assets/fonts/title-police.ttf"))
    {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
        return 0;
    }
    return 1;
}

void Menu::quit()
{
    game->getWindow()->close();
}

void Menu::settings()
{
    Settings settings;
    settings.open();
    delete &settings;
}

void Menu::start()
{
    game->init();
}
//A MODIFIER EN INTEGRANT LE MENU DANS GRAPHICSMANAGER
void Menu::update(sf::RenderWindow &window)
{
    while(window.isOpen())
    {
        window.draw(background);
        window.draw(title);
        startButton->update(game->getCursor()->getPosition(), &window);
        settingsButton->update(game->getCursor()->getPosition(), &window);
        quitButton->update(game->getCursor()->getPosition(), &window);
        window.display();
        sf::Event event;
        if(event.type == sf::Event::Closed){
            window.close();
        }
    }
}