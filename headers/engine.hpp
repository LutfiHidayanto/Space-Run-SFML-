#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "rocket.hpp"
#include "background.hpp"
#include "obstacle.hpp"

class Engine {
private:
    // variable
    sf::RenderWindow window;
    sf::VideoMode videoMode;
    sf::Event event;
    sf::Clock dtclock;

    float deltaTime;
    float timer;
    float maxTimer;

    float timerBoss;
    float maxTimerBoss;

    float timerRocket;
    float maxTimerRocket;

    float timerPika;
    float maxTimerPika;
    // iterables
    int i; // for ufo type
    int j; // for ufo movement
    int k; // for boss and pika movement
    int l; // for pikachu movement

    // obstacles
    std::vector<Ufo*> ufos;
    std::vector<Boss*> bosses;
    std::vector<Pikachu*> pikachus;
    std::vector<RocketEnemy*> rocketEnemies;
    sf::Vector2f position;
    sf::Vector2f position2;

    // rocket
    Rocket rocket;
    float movementSpeed = 5.f;

    // background
    Background background;

    // init
    void initWindows();
    void initVariable();
    void initPoints();

    // points
    int points = 0;;
    sf::Font font;
    sf::Text PointsTxt;
    sf::Sprite Pointsbg;
    sf::Texture Pointsbgtxt;

    // SOUND AND MUSIC
    // Gameplay Music
    sf::Music gameMusic;
    // Crash Sound
    sf::SoundBuffer bufferSound;
    sf::Sound sound;

    // PLAYER HP
    sf::RectangleShape hpBar;
    sf::RectangleShape hpBarBack;

    // GAME OVER
    sf::Sprite gameOverSp;
    sf::Texture gameOverTxt;
public:
    // cons decs
    Engine();
    ~Engine();
    // functions
    void run();
    void pollEvent();
    void render();
    void update();

    const bool getWindowOpen() const;
    void closeGame();

    // points
    int getPoints();
    void updatePoints();
    void updateUfoTime();

    // Hp bar
    void updateHpBar();

};