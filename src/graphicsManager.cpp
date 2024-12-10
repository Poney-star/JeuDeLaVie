#include "../include/graphicsManager.hpp"
#include "../include/textures.hpp"
#include "../include/fonts.hpp"

//Constructeur / Destructeurs

GraphicsManager::GraphicsManager()
{
    cursor = Cursor();
    window.create(sf::VideoMode(800,480), "Pig Dance", sf::Style::Default);
    originalSize = sf::Vector2f(800,480);
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
    return (textures.find(str) != textures.end())? &textures.at(str) : nullptr;
}


sf::Sprite* GraphicsManager::getSprite(std::string str)
{
    return (sprites.find(str) != sprites.end())? &sprites.at(str) : nullptr;
}

sf::Font* GraphicsManager::getFont(std::string str)
{
    return(fonts.find(str) != fonts.end())? &fonts.at(str) : nullptr;
}

sf::Text* GraphicsManager::getText(std::string str)
{
    return(texts.find(str) != texts.end())? &texts.at(str) : nullptr;
}

Button* GraphicsManager::getButton(std::string str)
{
    return(buttons.find(str) != buttons.end())? &buttons.at(str) : nullptr;
}

TextBox* GraphicsManager::getTextBox(std::string str)
{
    return(textBoxes.find(str) != textBoxes.end())? &textBoxes.at(str) : nullptr;
}

//Méthodes

bool GraphicsManager::loadAssets()
{
    //Textures
    if (!textures["menuBackground"].loadFromMemory(assets_images_background_jpg, assets_images_background_jpg_len)) return false;
    if (!textures["aliveCell"].loadFromMemory(assets_textures_aliveCellTexture_png, assets_textures_aliveCellTexture_png_len)) return false;
    if (!textures["deadCell"].loadFromMemory(assets_textures_deadCellTexture_png, assets_textures_deadCellTexture_png_len)) return false;
    if (!textures["constAliveCell"].loadFromMemory(assets_textures_constAliveCellTexture_png, assets_textures_constAliveCellTexture_png_len)) return false;
    if (!textures["constDeadCell"].loadFromMemory(assets_textures_constDeadCellTexture_png, assets_textures_constDeadCellTexture_png_len)) return false;

    //Sprites
    sprites["menuBackground"].setTexture(textures["menuBackground"]);
    sprites["aliveCell"].setTexture(textures["aliveCell"]);
    sprites["deadCell"].setTexture(textures["deadCell"]);
    sprites["constAliveCell"].setTexture(textures["constAliveCell"]);
    sprites["constDeadCell"].setTexture(textures["constDeadCell"]);
    sprites["pathBox"] = sf::Sprite(textures["menuBackground"],sf::IntRect(400.f, 100.f, 200, 50));
    sprites["pathBox"].setPosition(400.F, 100.F);
    sprites["pathBox"].setColor(sf::Color(0, 0, 0, 172));
    sprites["genNumberBox"] = sf::Sprite(textures["menuBackground"],sf::IntRect(400.f, 150.f, 200, 50));
    sprites["genNumberBox"].setPosition(400.F, 175.F);
    sprites["genNumberBox"].setColor(sf::Color(0, 0, 0, 172));

    //Polices
    if (!fonts["title"].loadFromMemory(assets_fonts_title_font_ttf,assets_fonts_title_font_ttf_len)) return false;
    if (!fonts["menuButton"].loadFromMemory(assets_fonts_title_font_ttf,assets_fonts_title_font_ttf_len)) return false;
    if (!fonts["userEntry"].loadFromMemory(assets_fonts_title_font_ttf,assets_fonts_title_font_ttf_len)) return false;

    //Textes
    texts["menuTitle"] = sf::Text("Pig Farm", fonts["title"]);
    texts["menuTitle"].setFillColor(sf::Color::White);
    texts["menuTitle"].setPosition(window.getSize().x / 2 -  texts["menuTitle"].getGlobalBounds().width / 2, 19);
    texts["startButton"] = sf::Text("Jouer", fonts["menuButton"], 20);
    texts["settingsButton"] = sf::Text("Param", fonts["menuButton"], 20);
    texts["quitButton"] = sf::Text("Quitter", fonts["menuButton"], 20);
    texts["pathTemplate"] = sf::Text("Entrer le chemin d'accès",fonts["userEntry"], 12);
    texts["pathTemplate"].setPosition(405.f, 103.f);
    texts["path"] = sf::Text("",fonts["userEntry"], 12);
    texts["path"].setPosition(405.f, 103.f);
    texts["genNumber"] = sf::Text("",fonts["userEntry"], 12);
    texts["genNumber"].setPosition(405.f, 178.f);
    texts["genNumberTemplate"] = sf::Text("Entrer le nombre de générations",fonts["userEntry"], 12);
    texts["genNumber"].setPosition(405.f, 178.f);
    texts["consoleButton"] = sf::Text("Console",fonts["menuButton"], 20);
    texts["graphicButton"] = sf::Text("Graphique",fonts["menuButton"], 20);
    texts["checkFile"] = sf::Text("Verifier",fonts["menuButton"], 20);

    //TextBoxes
    textBoxes["path"] = TextBox(&sprites["pathBox"], &texts["path"], sf::Vector2f(400.f, 100.f));
    textBoxes["genNumber"] = TextBox(&sprites["genNumberBox"], &texts["genNumber"], sf::Vector2f(400.f, 175.f));

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
    while(window.isOpen()){
        sf::Event event;
        window.pollEvent(event);
        switch (event.type)
        {
            case sf::Event::Closed:
            window.close();
            break;
            case sf::Event::Resized:
                window.setView(sf::View(sf::FloatRect(0,0,event.size.width,event.size.height)));
                sprites["menuBackground"].setScale(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height);
                buttons["startButton"].setScale(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height);
                buttons["settingsButton"].setScale(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height);
                buttons["quitButton"].setScale(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height);
                break;
            case sf::Event::MouseMoved: 
                cursor.updatePosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
                break;
            case sf::Event::MouseButtonPressed:
                buttonActivatedMenu(cursor.getPosition());
                break;
        }
        display();
    }
}

void GraphicsManager::renderSFAMMenu()
{
    toCheck = {
        &sprites["menuBackground"],
        &textBoxes["path"],
        &textBoxes["genNumber"],
        &buttons["consoleButton"],
        &buttons["graphicButton"],
        &buttons["checkFile"]
    };
    while(window.isOpen())
    {
        handleEvents();
        display();
    }
}

void GraphicsManager::buttonActivatedMenu(sf::Vector2i mousePos)
{
    if(buttons["startButton"].isHovered(mousePos))
    {
        renderSFAMMenu();
    } else if (buttons["settingsButton"].isHovered(mousePos)){

    } else if ((buttons["quitButton"].isHovered(mousePos))){
        window.close();
    }
}

void GraphicsManager::buttonActivatedSFAMMenu(sf::Vector2i mousePos)
{
    std::ifstream file(textBoxes["path"].getString());
    if (!file) {
    }
    if(buttons["consoleButton"].isHovered(mousePos))
    {
        Game* game = new Game(this);
        (stoi(textBoxes["genNumber"].getString())) ? game->setGenMax(stoi(textBoxes["genNumber"].getString())) : game->setGenMax(5) ;
        if (game->loadFile(textBoxes["path"].getString())) game->console();
        window.close();
    } else if (buttons["graphicButton"].isHovered(mousePos))
    {
        Game* game = new Game(this);
        if (game->loadFile(textBoxes["path"].getString())) renderGame(game);
    } else if (buttons["checkFile"].isHovered(mousePos))
    {
        
    }
}

void GraphicsManager::renderGame(Game* game)
{
    toCheck = {};
    window.clear();
    game->graphic();
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
            window.setView(sf::View(sf::FloatRect(0,0,event.size.width,event.size.height)));
            sprites["menuBackground"].setScale(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height);
            textBoxes["path"].setScale(sf::Vector2f(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height));
            textBoxes["genNumber"].setScale(sf::Vector2f(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height));
            buttons["consoleButton"].setScale(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height);
            buttons["graphicButton"].setScale(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height);
            buttons["checkFile"].setScale(event.size.width/sprites["menuBackground"].getLocalBounds().width,event.size.height/sprites["menuBackground"].getLocalBounds().height);
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
            if (sprites["genNumberBox"].getGlobalBounds().contains(cursor.getPosition().x, cursor.getPosition().y) && !textBoxes["genNumber"].getFocusState())
            {
                textBoxes["genNumber"].changeFocusState();
                toCheck.push_back(&textBoxes["genNumber"]);
            } else if (textBoxes["genNumber"].getFocusState())
            {
                textBoxes["genNumber"].changeFocusState();
                toCheck.pop_back();
                buttonActivatedSFAMMenu(cursor.getPosition());
            }
            if(sprites["pathBox"].getGlobalBounds().contains(cursor.getPosition().x, cursor.getPosition().y) && !textBoxes["path"].getFocusState())
            {
                textBoxes["path"].changeFocusState();
                toCheck.push_back(&textBoxes["path"]);
            } else if (textBoxes["path"].getFocusState())
            {
                textBoxes["path"].changeFocusState();
                toCheck.pop_back();
                buttonActivatedSFAMMenu(cursor.getPosition());
            }
            buttonActivatedSFAMMenu(cursor.getPosition());
            break;
        default:
            break;
    }
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
            }
        }, item);
    }
    window.display();
}

void GraphicsManager::addToCheck(std::variant<sf::Sprite*, sf::Text*, TextBox*, Button*, mutableCell*, constCell*, Cell*> obj)
{
    toCheck.push_back(obj);
}

void GraphicsManager::displayGameCells(int width, int height)
{
    sf::Vector2f cellScale(window.getSize().x/(width * sprites["deadCell"].getLocalBounds().width), window.getSize().y/(height * sprites["deadCell"].getLocalBounds().height));
    sf::Sprite * sprite;
    while (!toCheck.empty()) 
    {
        auto& cell = std::get<Cell*>(toCheck.back());
        if (typeid(*cell) == typeid(mutableCell))
        {
            sprite = (cell->getValue())? &sprites["aliveCell"] : &sprites["deadCell"];
            sprite->setPosition(cell->getX() * sprite->getGlobalBounds().width, cell->getY() * sprite->getGlobalBounds().height);
        } else if (typeid(*cell) == typeid(constCell))
        {
            sprite = (cell->getValue())? &sprites["constAliveCell"] : &sprites["constDeadCell"];
            sprite->setPosition(cell->getX() * sprite->getGlobalBounds().width, cell->getY() * sprite->getGlobalBounds().height);
        }
        sprite->setScale(cellScale);
        window.draw(*sprite);
        toCheck.pop_back();
    }
    window.display();
}