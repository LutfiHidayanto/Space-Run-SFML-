#include "obstacle.hpp"
#include <iostream>

/*
    OBSTACLE
*/

// constructor desctructor

Obstacle::Obstacle(sf::Vector2f p)
{
    sprite.setPosition(p);
}


// setter getter

void Obstacle::setposition(sf::Vector2f &p) {
    position = p;
}

const sf::Vector2f& Obstacle::getposition() {
    return sprite.getPosition();
}

const sf::FloatRect Obstacle::getBounds() const
{
    return sprite.getGlobalBounds();
}

// public function

void Obstacle::drawObsl(sf::RenderWindow &w) {
    w.draw(sprite);
}

void Obstacle::MovementF(float vX, float vY) {
    sprite.setPosition(sprite.getPosition().x + vX, sprite.getPosition().y + vY);
}

/*
    UFO
*/

Ufo::Ufo(sf::Vector2f p, int jenis)
        :Obstacle(p) {
    switch (jenis)
    {
    case 1:
        if(!spritetxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/Ufomerah.png")) {
                std::cout << "File not found" << std:: endl;
        }
        break;
    case 2:
        if(!spritetxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/Ufomerah2.png")) {
                std::cout << "File not found" << std:: endl;
        }
        break;
    case 3:
        if(!spritetxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/Ufooren.png")) {
                std::cout << "File not found" << std:: endl;
        }
        break;
    case 4:
        if(!spritetxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/Ufokuning.png")) {
                std::cout << "File not found" << std:: endl;
        }
        break;
    case 5:
        if(!spritetxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/Ufoijo.png")) {
                std::cout << "File not found" << std:: endl;
        }
        break;
    default:
        break;
    }
    sprite.setTexture(spritetxt);
    sprite.setScale({1.1, 1.1});
    // Movement(jenis);
}

// physics ufo

// Movement
void Ufo::movementUfo(int jenis) {
    switch (jenis)
    {
    case 1:
        MovementF(0.f, 3.f);
        break;
    case 2:
        MovementF(3.f, 3.f);
        break;
    case 3:
        MovementF(-3.f, 3.f);
        break;
    case 4:
        MovementF(-4.f, 5.f);
        break;
    case 5:
        MovementF(6.f, 4.f);
        break;
    case 6:
        MovementF(-6.f, 5.f);
        break;
    case 7:
        MovementF(7.f, 2.f);
        break;
    default:
        break;
    }
}



// Collision

void Obstacle::collision() {
    // Left
    if (sprite.getPosition().x < 0.f) {
        sprite.setPosition(sf::Vector2f(1280.f, sprite.getPosition().y));
    }
    // Right
    if (sprite.getPosition().x > 1280.f) {
        sprite.setPosition(sf::Vector2f(0.f, sprite.getPosition().y));
    }   
}

/*
    BOSS
*/

// CONSTRUCTOR
Boss::Boss(sf::Vector2f p):
    Obstacle(p)
{
    if(!spritetxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/PesawatBoss.png")) {
                std::cout << "File not found" << std:: endl;
    }
    sprite.setTexture(spritetxt);
}


// FUNCTIONS

// BOSS MOVEMENT

void Boss::movementBoss(int jenis) {
    switch (jenis)
    {
    case 1:
        MovementF(0.f, 5.f);
        break;
    case 2:
        MovementF(5.f, 0.f);
        break;
    case 3:
        MovementF(-5.f, 0.f);
        break;
    case 4:
        MovementF(-5.f, 5.f);
        break;
    case 5:
        MovementF(5.f, 5.f);
        break;
    default:
        break;
    }
}

/*
    PIKACHU
*/

Pikachu::Pikachu(sf::Vector2f p):
    Obstacle(p) {
    if(!spritetxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/Pikachu.png")){
                std::cout << "ERROR PIKACHU NOT LOADED" << std::endl;
    }
    sprite.setTexture(spritetxt);
}

void Pikachu::movementPika(int jenis)
{
    switch (jenis)
    {
    case 1:
        MovementF(5.f, 5.f);
        break;
    case 2:
        MovementF(-5.f, 5.f);
        break;
    case 3:
        MovementF(5.f, 5.f);
        break;
    case 4:
        MovementF(-5.f, 5.f);
        break;
    case 5:
        MovementF(-5.f, 5.f);
        break;
    default:
        break;
    }
}

RocketEnemy::RocketEnemy(sf::Vector2f p):
    Obstacle(p) {
    if(!spritetxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/Rocket.png")){
                std::cout << "ERROR ROCKET ENEMY NOT LOADED" << std::endl;
    }
    sprite.setTexture(spritetxt);
}

void RocketEnemy::movementREnemy() {
    MovementF(10.f, 0.f);
}
