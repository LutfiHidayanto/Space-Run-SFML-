#include "rocket.hpp"
#include <iostream>
#include <cstdlib>
#include "engine.hpp"

// constructor
Rocket::Rocket() {
    initRocket();
}

// public functions

void Rocket::initRocket() {
    if(!texture.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/Roketplayer.png")) {
        std::cout << "File not found" << std:: endl;
    }
    sprite.setTexture(texture);
    // set position
    rocketPosition.x = 1080.f/2.f; // - rocket size
    rocketPosition.y = 720.f - 120.f; 
    sprite.setPosition(rocketPosition);
    sprite.setScale(1.3, 1.3);

    // INIT HP
    hpMax = 10;
    hp = hpMax;
}

// Drawing
void Rocket::drawlocal(sf::RenderWindow &w) {
    w.draw(sprite);
}
// rocket movement with keyboard
void Rocket::rocketMovement() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.move(-movementSpeed, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move(movementSpeed, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite.move(0.f, -movementSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0.f, movementSpeed);
    }
}

// setters getters position

void Rocket::setRocketPosition(sf::Vector2f &newPosition) {
    rocketPosition = newPosition;
}

const sf::FloatRect Rocket::getBounds() const
{
    return sprite.getGlobalBounds();
}

const int &Rocket::getHp() const
{
    return hp;
}

const int &Rocket::getHpMax() const
{
    return hpMax;
}

void Rocket::setHp(const int hpS)
{
    hp = hpS;
}

void Rocket::loseHp(const int hpLose)
{
    hp -= hpLose;
    if (hp < 0) hp = 0;
}

sf::Vector2f Rocket::getRocketPosition() {
    return rocketPosition;
}

// World collision

void Rocket::rocketCollision() {
    // Left
    if (sprite.getPosition().x < 0.f) {
        sprite.setPosition(sf::Vector2f(0.f, sprite.getPosition().y));
    }
    // Right
    if (sprite.getPosition().x > 1280.f - (texture.getSize().x * 1.3) ) {
        sprite.setPosition(sf::Vector2f(1280.f - (texture.getSize().x * 1.3), sprite.getPosition().y));
    }
    // Top
    if (sprite.getPosition().y < 0.f) {
        sprite.setPosition(sf::Vector2f(sprite.getPosition().x, 0.f));
    }
    // Bottom
    if (sprite.getPosition().y > 720.f - (texture.getSize().y * 1.3)) {
        sprite.setPosition(sf::Vector2f(sprite.getPosition().x, 720.f - (texture.getSize().y * 1.3)));
    }
}

