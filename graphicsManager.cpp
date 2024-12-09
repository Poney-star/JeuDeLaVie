#include "graphicsManager.hpp"

//Constructeur / Destructeurs

GraphicsManager::GraphicsManager()
{
    cursor = Cursor();
    window.create(sf::VideoMode(800,600), "Pig Dance", sf::Style::Default);
    originalSize = sf::Vector2f(800,600);
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
    if (!textures["constAliveCell"].loadFromFile("assets/textures/constAliveCellTexture.png")) return false;
    if (!textures["constDeadCell"].loadFromFile("assets/textures/constDeadCellTexture.png")) return false;

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
    texts["path"].setPosition(400.f, 100.f);
    texts["genNumber"] = sf::Text("",fonts["userEntry"], 16);
    texts["genNumber"].setPosition(400.f, 200.f);
    texts["consoleButton"] = sf::Text("Console",fonts["menuButton"], 20);
    texts["graphicButton"] = sf::Text("Graphique",fonts["menuButton"], 20);
    texts["checkFile"] = sf::Text("Verifier",fonts["menuButton"], 20);

    //TextBoxes
    textBoxes["path"] = TextBox(&sprites["pathBox"], &texts["path"], sf::Vector2f(400.f, 100.f));
    textBoxes["genNumber"] = TextBox(&sprites["genNumberBox"], &texts["genNumber"], sf::Vector2f(400.f, 200.f));

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
    while(window.isOpen() && ){
        gM.display();
    }
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

}

bool GraphicsManager::buttonActivatedSFAMMenu(sf::Vector2i mousePos)
{
    std::ifstream file(textBoxes["path"].getString());
    if (!file) {
        std::cout<<"fail"<<std::endl;
        return 0;
    }
    if(buttons["consoleButton"].isHovered(mousePos))
    {
        Game game = Game();
        if (stoi(textBoxes["genNumber"].getString())) game.setGenMax(stoi(textBoxes["genNumber"].getString()));
        if (game.loadFile(textBoxes["path"].getString())) game.console();
        window.close();
        return 1;
    } else if (buttons["graphicButton"].isHovered(mousePos))
    {
        Game game = Game();
        if (game.loadFile(textBoxes["path"].getString())) renderGame(&game);
        return 1;
    } else if (buttons["checkFile"].isHovered(mousePos))
    {
        Game game = Game();
        if (game.loadFile(textBoxes["path"].getString())) return 1;
        return 0;
    }
    return 0;
}

void GraphicsManager::renderGame(Game* game)
{
    toCheck = {}
    game->graphic(&window);
}

void GraphicsManager::handleEvents()
{
    sf::Event event;
    sf::Vector2f scaleFactor;
    window.pollEvent(event);
    switch (event.type)
    {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::Resized:
            scaleFactor = sf::Vector2f(event.size.width / originalSize.x, event.size.height / originalSize.y);
            window.setView(sf::View(sf::FloatRect(0,0,event.size.width,event.size.height)));
            break;
        case sf::Event::MouseMoved: 
            cursor.updatePosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
            break;
        case sf::Event::KeyPressed:
            if (textBoxes["path"].getFocusState())
            {
                switch(event.key.code)  
                {
                    case sf::Keyboard::Escape:
                        textBoxes["path"].changeFocusState();
                        break;
                    case sf::Keyboard::Enter:
                        textBoxes["path"].changeFocusState();
                        break;
                    case sf::Keyboard::Backspace:
                        textBoxes["path"].deleteChar();
                        break;
                    case sf::Keyboard::Left:
                        textBoxes["path"].moveCursor(-1);
                        break;
                    case sf::Keyboard::Right:
                        textBoxes["path"].moveCursor(1);
                        break;
                    case sf::Keyboard::RAlt:
                        break;
                    case sf::Keyboard::LShift:
                        break;
                    case sf::Keyboard::SemiColon:
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? textBoxes["path"].addChar(".") : textBoxes["path"].addChar(";");
                        break;
                    case sf::Keyboard::Num8:
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) textBoxes["path"].addChar("\\") ;
                        break;
                    default:
                        textBoxes["path"].addChar(sf::Keyboard::getDescription(event.key.scancode));
                        break;
                }
            } else if (textBoxes["genNumber"].getFocusState()){
                switch(event.key.code)  
                {
                    case sf::Keyboard::Escape:
                        textBoxes["genNumber"].changeFocusState();
                        break;
                    case sf::Keyboard::Enter:
                        textBoxes["genNumber"].changeFocusState();
                        break;
                    case sf::Keyboard::Backspace:
                        textBoxes["genNumber"].deleteChar();
                        break;
                    case sf::Keyboard::Left:
                        textBoxes["genNumber"].moveCursor(-1);
                        break;
                    case sf::Keyboard::Right:
                        textBoxes["genNumber"].moveCursor(1);
                        break;
                    case sf::Keyboard::Num0:
                        textBoxes["genNumber"].addChar("0");
                        break;
                    case sf::Keyboard::Numpad0:
                        textBoxes["genNumber"].addChar("0");
                        break;
                    case sf::Keyboard::Num1:
                        textBoxes["genNumber"].addChar("1");
                        break;
                    case sf::Keyboard::Numpad1:
                        textBoxes["genNumber"].addChar("1");
                        break;
                    case sf::Keyboard::Num2:
                        textBoxes["genNumber"].addChar("2");
                        break;
                    case sf::Keyboard::Numpad2:
                        textBoxes["genNumber"].addChar("2");
                        break;
                    case sf::Keyboard::Num3:
                        textBoxes["genNumber"].addChar("3");
                        break;
                    case sf::Keyboard::Numpad3:
                        textBoxes["genNumber"].addChar("3");
                        break;
                    case sf::Keyboard::Num4:
                        textBoxes["genNumber"].addChar("4");
                        break;
                    case sf::Keyboard::Numpad4:
                        textBoxes["genNumber"].addChar("4");
                        break;
                    case sf::Keyboard::Num5:
                        textBoxes["genNumber"].addChar("5");
                        break;
                    case sf::Keyboard::Numpad5:
                        textBoxes["genNumber"].addChar("5");
                        break;
                    case sf::Keyboard::Num6:
                        textBoxes["genNumber"].addChar("6");
                        break;
                    case sf::Keyboard::Numpad6:
                        textBoxes["genNumber"].addChar("6");
                        break;
                    case sf::Keyboard::Num7:
                        textBoxes["genNumber"].addChar("7");
                        break;
                    case sf::Keyboard::Numpad7:
                        textBoxes["genNumber"].addChar("7");
                        break;
                    case sf::Keyboard::Num8:
                        textBoxes["genNumber"].addChar("8");
                        break;
                    case sf::Keyboard::Numpad8:
                        textBoxes["genNumber"].addChar("8");
                        break;
                    case sf::Keyboard::Num9:
                        textBoxes["genNumber"].addChar("9");
                        break;
                    case sf::Keyboard::Numpad9:
                        textBoxes["genNumber"].addChar("9");
                        break;
                    default:
                        break;
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            if(sprites["pathBox"].getGlobalBounds().contains(cursor.getPosition().x, cursor.getPosition().y) && !textBoxes["path"].getFocusState())
            {
                textBoxes["path"].changeFocusState();
                toCheck.push_back(&textBoxes["path"]);
            } else if (textBoxes["path"].getFocusState())
            {
                textBoxes["path"].changeFocusState();
                toCheck.pop_back();
                buttonActivatedSFAMMenu(cursor.getPosition());
            } else if (sprites["genNumber"].getGlobalBounds().contains(cursor.getPosition().x, cursor.getPosition().y) && !textBoxes["genNumber"].getFocusState())
            {
                textBoxes["genNumber"].changeFocusState();
                toCheck.push_back(&textBoxes["genNumber"]);
            } else if (textBoxes["genNumber"].getFocusState())
            {
                textBoxes["path"].changeFocusState();
                toCheck.pop_back();
                buttonActivatedSFAMMenu(cursor.getPosition());
            }
        default:
            break;
    }
}

void GraphicsManager::display()
{
    for (const auto& item : toCheck) {
        std::visit([this, scaleFactor](const auto& value) {
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
            }
        }, item);
    }
    window.display();
}

void GraphicsManager::addToCheck(std::variant<sf::Sprite*, sf::Text*, TextBox*, Button*, Cell*> obj)
{
    toCheck.push_back(obj);
}

void GraphicsManager::displayGameCells()
{
    for (const auto& item : toCheck) {
        std::visit([this](const auto& value) {
            if constexpr (std::is_same_v<std::decay_t<decltype(value)>, mutableCell*>)
            {
                if (value->getValue())
                {
                    sprites["aliveCell"].setPosition(
                        sf::Vector2f(
                            value->getX()*sprites["aliveCell"].getGlobalBounds().width,
                            value->getY()*sprites["aliveCell"].getGlobalBounds().height
                        )
                    );
                    window.draw(sprites["aliveCell"]);
                } else {
                    sprites["deadCell"].setPosition(
                        sf::Vector2f(
                            value->getX()*sprites["deadCell"].getGlobalBounds().width,
                            value->getY()*sprites["deadCell"].getGlobalBounds().height
                        )
                    );
                    window.draw(sprites["deadCell"]);
                }
            } else {
                if (value->getValue())
                {
                    sprites["constAliveCell"].setPosition(
                        sf::Vector2f(
                            value->getX()*sprites["constAliveCell"].getGlobalBounds().width,
                            value->getY()*sprites["constAliveCell"].getGlobalBounds().height
                        )
                    );
                    window.draw(sprites["constAliveCell"]);
                } else {
                    sprites["constDeadCell"].setPosition(
                        sf::Vector2f(
                            value->getX()*sprites["constDeadCell"].getGlobalBounds().width,
                            value->getY()*sprites["constDeadCell"].getGlobalBounds().height
                        )
                    );
                    window.draw(sprites["constDeadCell"]);
                }
            }
        }, item);
    }
}