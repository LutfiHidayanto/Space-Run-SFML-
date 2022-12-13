#pragma once
#include <SFML/Graphics.hpp>


class Obstacle {
protected:
    sf::Vector2f position; 
    sf::Sprite sprite;
    sf::Texture spritetxt;
    sf::Clock dtclock;

    float deltaTime;
    float timer;
    float maxTimer;
    // hp
    int hp;
    int hpMax;
public:
    Obstacle(sf::Vector2f p);
    void drawObsl(sf::RenderWindow &w);
    
    void setposition(sf::Vector2f &p);
    const sf::Vector2f& getposition();
    const sf::FloatRect getBounds() const;

    void collision();
    void MovementF(float vX, float vY);
    // hp
    void setHp(const int hpS);
    void loseHp(const int hpLose);
    const int &getHp() const;
};

class Ufo:public Obstacle {    
public:
    Ufo(sf::Vector2f p, int jenis);
    void movementUfo(int jenis);
};

class Boss:public Obstacle {
public:
    Boss(sf::Vector2f p);
    void movementBoss(int jenis);
};

class Pikachu:public Obstacle {
public:
    Pikachu(sf::Vector2f p);
    void movementPika(int jenis);
};

class RocketEnemy:public Obstacle {
public:
    RocketEnemy(sf::Vector2f p);
    void movementREnemy();
};