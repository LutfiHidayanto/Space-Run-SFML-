#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX 2

class MainMenu
{
private:
    int mainMenuSelected;
    sf::Font font;
    sf::Text mainMenu[MAX];
public:
    MainMenu(float width, float height);
    ~MainMenu();

    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int mainMenuPressed() {
        return mainMenuSelected;
    }
};


