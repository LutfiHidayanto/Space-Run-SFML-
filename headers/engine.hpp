#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "rocket.hpp"
#include "background.hpp"
#include "obstacle.hpp"
#include <vector>
#include "rocketBullet.hpp"

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

    // ROCKET
    Rocket *rocket;
    sf::Vector2f rocketPosition;
    // ROCKET HP
    sf::RectangleShape hpBar;
    sf::RectangleShape hpBarBack;
    // BULLET
    std::map<std::string, sf::Texture*> bulletTxtS;
    std::vector<RocketBullet*> bullets;
    float movementSpeed = 5.f;

    // background
    Background background;

    // init
    void initWindows();
    void initVariable();
    void initPoints();

    // points
    int points;
    sf::Font font;
    sf::Text PointsTxt;
    sf::Sprite Pointsbg;
    sf::Texture Pointsbgtxt;

    // SOUND AND MUSIC
    // Gameplay Music
    sf::Music gameMusic;

    // Crash Sound
    sf::SoundBuffer bufferCrash;
    sf::Sound soundcr;

    // Gameover Sound
    sf::SoundBuffer buffergameOver;
    sf::Sound soundgO;

    // Destroy Sound
    sf::SoundBuffer bufferdestroy;
    sf::Sound soundDs;

    

    // GAME OVER
    sf::Sprite gameOverSp;
    sf::Texture gameOverTxt;
    sf::Text PlayAgain;

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
    const sf::Window getWindowPollEv() const;
    void closeGame();

    // points
    int getPoints();
    void updatePoints();

    // Hp bar
    void updateHpBar();

    bool isGameOver();

    void GameOverDisplay();
    bool RestartPressed();
    void updateBullets();
};