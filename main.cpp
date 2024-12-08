#include "graphicsManager.hpp"

int main() {
    GraphicsManager gM;
    gM.renderSFAMMenu();
    while(gM.getWindow()->isOpen()){
    gM.display();
    }
}