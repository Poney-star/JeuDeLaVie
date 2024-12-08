#include "menu.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Le Jeu de la Vie", sf::Style::Default);
    Menu menu;
    menu.update(window);
    return 0;
}