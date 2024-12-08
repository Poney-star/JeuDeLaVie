#include "graphicsManager.hpp"

//Constructeur / Destructeurs

GraphicsManager::GraphicsManager()
{
    cursor = Cursor();
    window.create(sf::VideoMode(800,600), "Pig Dance", sf::Style::Default);
    if(loadAssets())
    {}
}


// Accesseurs


sf::RenderWindow* GraphicsManager::getWindow() 
{
    return &window;
}

Cursor* GraphicsManager::getCursor()
{
    return &cursor;
}

sf::Texture* GraphicsManager::getTexture(std::string str)
{
    return (textures.find(str) == textures.end())? &textures.at(str) : nullptr;
}


sf::Sprite* GraphicsManager::getSprite(std::string str)
{
    return (sprites.find(str) == sprites.end())? &sprites.at(str) : nullptr;
}

sf::Font* GraphicsManager::getFont(std::string str)
{
    return(fonts.find(str) == fonts.end())? &fonts.at(str) : nullptr;
}

sf::Text* GraphicsManager::getText(std::string str)
{
    return(texts.find(str) == texts.end())? &texts.at(str) : nullptr;
}

Button* GraphicsManager::getButton(std::string str)
{
    return(buttons.find(str) == buttons.end())? &buttons.at(str) : nullptr;
}

TextBox* GraphicsManager::getTextBox(std::string str)
{
    return(textBoxes.find(str) == textBoxes.end())? &textBoxes.at(str) : nullptr;
}

//Méthodes

bool GraphicsManager::loadAssets()
{
    //Textures
    if (!textures["menuBackground"].loadFromFile("assets/textures/deadCellTexture.png")) return false;
    if (!textures["aliveCell"].loadFromFile("assets/textures/aliveCellTexture.png")) return false;
    if (!textures["deadCell"].loadFromFile("assets/textures/deadCellTexture.png")) return false;
    if (!textures["constAliveCell"].loadFromFile("assets/textures/aliveCellTexture.png")) return false;
    if (!textures["constDeadCell"].loadFromFile("assets/textures/deadCellTexture.png")) return false;

    //Sprites
    sprites["menuBackground"].setTexture(textures["menuBackground"]);
    sprites["menuBackground"].setScale(1,1);
    sprites["aliveCell"].setTexture(textures["aliveCell"]);
    sprites["deadCell"].setTexture(textures["deadCell"]);
    sprites["constAliveCell"].setTexture(textures["constAliveCell"]);
    sprites["constDeadCell"].setTexture(textures["constDeadCell"]);
    sprites["pathBox"] = sf::Sprite(textures["menuBackground"],sf::IntRect(400.f, 100.f, 200, 50));
    sprites["pathBox"].setPosition(400.F, 100.F);
    sprites["pathBox"].setColor(sf::Color(0, 0, 0, 172));

    //Polices
    if (!fonts["title"].loadFromFile("assets/fonts/title-font.ttf")) return false;
    if (!fonts["menuButton"].loadFromFile("assets/fonts/title-font.ttf")) return false;
    if (!fonts["userEntry"].loadFromFile("assets/fonts/title-font.ttf")) return false;

    //Textes
    texts["menuTitle"] = sf::Text("Pig Farm", fonts["title"]);
    texts["menuTitle"].setFillColor(sf::Color::White);
    texts["menuTitle"].setPosition(window.getSize().x / 2 -  texts["menuTitle"].getGlobalBounds().width / 2, 19);
    texts["startButton"] = sf::Text("Jouer", fonts["menuButton"], 20);
    texts["settingsButton"] = sf::Text("Parametres", fonts["menu_button"], 20);
    texts["quitButton"] = sf::Text("Quitter", fonts["menuButton"], 20);
    texts["path"] = sf::Text("",fonts["userEntry"], 16);
    texts["consoleButton"] = sf::Text("Console",fonts["menuButton"], 20);
    texts["graphicButton"] = sf::Text("Graphique",fonts["menuButton"], 20);
    texts["checkFile"] = sf::Text("Verifier",fonts["menuButton"], 20);

    //TextBoxes
    textBoxes["path"] = TextBox(&sprites["pathBox"], &texts["path"], sf::Vector2f(400.f, 100.f));

    //Boutons
    buttons["startButton"]= Button(200.f, 100.f, 200.f, 50.f, sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(100, 100, 100));
    buttons["startButton"].setText(&texts["startButton"]);
    buttons["settingsButton"] = Button(200.f, 175.f, 200.f, 50.f, sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(100, 100, 100));
    buttons["settingsButton"].setText(&texts["settingsButton"]);
    buttons["quitButton"] = Button(200.f, 250.f, 200.f, 50.f, sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(100, 100, 100));
    buttons["quitButton"].setText(&texts["quitButton"]);
    buttons["consoleButton"]= Button(75.f, 250.f, 200.f, 50.f, sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(100, 100, 100));
    buttons["consoleButton"].setText(&texts["consoleButton"]);
    buttons["graphicButton"]= Button(325.f, 250.f, 200.f, 50.f, sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(100, 100, 100));
    buttons["graphicButton"].setText(&texts["graphicButton"]);
    buttons["checkFile"]= Button(200.f, 100.f, 200.f, 50.f, sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(100, 100, 100));
    buttons["checkFile"].setText(&texts["checkFile"]);
    return true;
}

//Méthodes d'affichage

void GraphicsManager::renderStartMenu()
{
    toCheck = {
        &sprites["menuBackground"],
        &texts["menuTitle"],
        &buttons["startButton"],
        &buttons["settingsButton"],
        &buttons["quitButton"]
    };

    window.draw(sprites["menuBackground"]);
    window.draw(texts["menuTitle"]);
    buttons["startButton"].update(cursor.getPosition(), &window);
    buttons["settingsButton"].update(cursor.getPosition(), &window);
    buttons["quitButton"].update(cursor.getPosition(), &window);
    window.display();
}

void GraphicsManager::renderSFAMMenu()
{
    toCheck = {
        &sprites["menuBackground"],
        &textBoxes["path"],
        &buttons["consoleButton"],
        &buttons["graphicButton"],
        &buttons["checkFile"]
    };

    buttons["consoleButton"].update(cursor.getPosition(), &window);
    buttons["graphicButton"].update(cursor.getPosition(), &window);
    buttons["checkFile"].update(cursor.getPosition(), &window);
    window.display();
}

void GraphicsManager::renderGame()
{
    
}

void GraphicsManager::display()
{
    for (const auto& item : toCheck) {
        std::visit([this](const auto& value) {
            if constexpr (std::is_same_v<std::decay_t<decltype(value)>, sf::Sprite*>)
            {
                window.draw(*value);
            } else if constexpr (std::is_same_v<std::decay_t<decltype(value)>, sf::Text*>)
            {
                window.draw(*value);
            } else if  constexpr (std::is_same_v<std::decay_t<decltype(value)>, TextBox*>)
            {
                value->draw(&window);
            } else if constexpr (std::is_same_v<std::decay_t<decltype(value)>, Button*>)
            {
                value->update(cursor.getPosition(), &window);
            } else if constexpr (std::is_same_v<std::decay_t<decltype(value)>, Cell*>)
            {
                value->getX(), value->getY();
            } 
        }, item);
    }
}

void GraphicsManager::addToCheck(std::variant<sf::Sprite*, sf::Text*, TextBox*, Button*, Cell*> obj)
{
    toCheck.push_back(obj);
}