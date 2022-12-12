#pragma once
#include <SFML/Graphics.hpp>
class Rocket {
private:
    // variables
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Color color;
    sf::Vector2f rocketPosition;
    float movementSpeed = 5.f;

    int hp;
    int hpMax;
public:
    Rocket();
    void initRocket();
    void drawlocal(sf::RenderWindow &w);
    void rocketMovement();
    void rocketCollision();
    // Setters getters
    sf::Vector2f getRocketPosition();
    void setRocketPosition(sf::Vector2f &a);
    const sf::FloatRect getBounds() const;

    const int& getHp() const;
    const int& getHpMax() const;
    void setHp(const int hpS);
    void loseHp(const int hpLose);
};