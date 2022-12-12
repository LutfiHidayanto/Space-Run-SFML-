#pragma once
#include <SFML/Graphics.hpp>

class Background {
private:
    sf::Sprite background;
    sf::Texture texture;
    sf::Shader parallaxShader;
    float offset = 0.f;
    sf::Clock clock;
public:
    Background();
    void drawBackground(sf::RenderWindow &w);
    void initBackground();
    void backgroundPos();
    void moveBackground();
};