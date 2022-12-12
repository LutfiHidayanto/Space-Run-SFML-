#include "mainMenu.hpp"

MainMenu::MainMenu(float width, float height){
    if (!font.loadFromFile("D:/Coding/Project/SFML/RocketUp/Fonts/VT323-Regular.ttf")){
        std::cout << "ERROR ! FONT IS NOT FOUND !" << std::endl;
    }

    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(sf::Vector2f(640.f - mainMenu[0].getGlobalBounds().width / 2.f, 
    360.f - mainMenu[0].getGlobalBounds().height / 2.f));
    //Credits
    mainMenu[1] = mainMenu[0];
    mainMenu[1].setString("Credits");
    mainMenu[1].setPosition(sf::Vector2f(640.f - mainMenu[0].getGlobalBounds().width / 2.f, 500.f));

    mainMenuSelected = -1;
}

MainMenu::~MainMenu() {
    // delete mainMenu;
}

void MainMenu::draw(sf::RenderWindow &window) {
    for (int i = 0; i < MAX; ++i) {
        window.draw(mainMenu[i]);
    }
}

void MainMenu::MoveUp() {
    if (mainMenuSelected - 1 >= 0) {
        mainMenu[mainMenuSelected].setFillColor(sf::Color::White);
        mainMenuSelected--;
        if (mainMenuSelected == -1) {
            mainMenuSelected = 1;
        }
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue);
    }
}

void MainMenu::MoveDown() {
    if (mainMenuSelected + 1 <= MAX) {
        mainMenu[mainMenuSelected].setFillColor(sf::Color::White);
        mainMenuSelected++;
        if (mainMenuSelected == 2) {
            mainMenuSelected = 0;
        }
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue);
    }
}

// Render Main menu
