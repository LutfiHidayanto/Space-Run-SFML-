#pragma once
#include <SFML/Graphics.hpp>
class Rocket {
private:
    // variables
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Color color;
    sf::Vector2f rocketPosition;
    float movementSpeed = 6.f;

    // hp
    int hp;
    int hpMax;

    // attack
    float attCd;
	float attCdMax;
public:
    Rocket();
    void initRocket();
    void drawlocal(sf::RenderWindow &w);
    void rocketMovement();
    void rocketCollision();

    // Setters getters Position
    const sf::Vector2f & getRocketPosition() const;
    void setRocketPosition(sf::Vector2f &a);
    const sf::FloatRect getBounds() const;
    void resetRocketPosition();


    // hp accessors setters funcion
    const int& getHp() const;
    const int& getHpMax() const;
    void setHp(const int hpS);
    void loseHp(const int hpLose);

    // For Attacking
    const bool canAtt();
	void updateAtt();
};