#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include "mainMenu.hpp"

int main() {
    Engine engine;
    engine.run();
    return 0;

    // Main Window
    // sf::RenderWindow Menu(sf::VideoMode(1280, 720), "Main Menu");
    // MainMenu mainMenu(Menu.getSize().x, Menu.getSize().y);

    // while (Menu.isOpen()){
    //     sf::Event event;
    //     while (Menu.pollEvent(event)){
    //         if (event.type == sf::Event::Closed){
    //             Menu.close();
    //         }

    //         if (event.type == sf::Event::KeyReleased) {
    //             if (event.key.code == sf::Keyboard::Up) {
    //                 mainMenu.MoveUp();
    //             }

    //             if (event.key.code == sf::Keyboard::Down) {
    //                 mainMenu.MoveUp();
    //             }

    //             if (event.key.code == sf::Keyboard::Return) {
    //                 Engine engine;
    //                 sf::RenderWindow Credits(sf::VideoMode(1280, 720), "CREDITS");

    //                 int x = mainMenu.mainMenuPressed();
    //                 // GAME
    //                 if (x == 0) {
    //                     Credits.close(); 
    //                     engine.run();   
    //                 }
    //                 // CREDITS
    //                 if (x == 1) {
    //                     while (Credits.isOpen()) {
    //                         sf::Event Cevent;
    //                         while (Credits.pollEvent(Cevent)) {
    //                             if (Cevent.type == sf::Event::Closed) {
    //                                 Credits.close();
    //                             }
    //                             if (Cevent.type == sf::Event::KeyPressed) {
    //                                 if (Cevent.key.code == sf::Keyboard::Escape) {
    //                                     Credits.close();
    //                                 }
    //                             }
    //                         }
    //                         engine.closeGame();
    //                         Credits.display();
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     Menu.clear();
    //     mainMenu.draw(Menu);
    //     Menu.display();
    // }
}

