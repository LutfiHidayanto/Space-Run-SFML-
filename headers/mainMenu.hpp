#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>

class Menu {
private:
    int pos;
    bool pressed, theselect;

    sf::RenderWindow * window;
    sf::RectangleShape * winclose;
    sf::Font * font;
    sf::Texture * image;
    sf::Sprite * bg;
    sf::Sprite txtBg1;
    sf::Sprite txtBg2;
    sf::Sprite txtBg3;
    sf::Sprite txtBg4;
    sf::Texture txtBgtxt;

    sf::Texture txtbgHelpCR;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

// for main menu
    std::vector<const char *> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;
// for Help
    std::vector<const char *> strings;
    std::vector<sf::Vector2f> coordsHelp;
    std::vector<sf::Text> HelpTexts;
    std::vector<std::size_t> Helptxtsizes;
// for credit
    std::vector<const char *> strings2;
    std::vector<sf::Vector2f> coordsCR;
    std::vector<sf::Text> CRTexts;
    std::vector<std::size_t> CRtxtsizes;
// Music
    sf::Music MainMenuMusic;
protected:
    void set_values();
    void loop_events();
    void draw_all();
public:
    Menu();
    ~Menu();
    void run_menu();
};
