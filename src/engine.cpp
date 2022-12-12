#include "engine.hpp"
#include "rocket.hpp"
#include "obstacle.hpp"
#include <stdlib.h>
#include <iostream>
#include <sstream>

// cons decs
Engine::Engine():
    timer(0.f), 
    maxTimer(3.f),
    timerBoss(0.f),
    maxTimerBoss(30.f),
    timerRocket(0.f),
    maxTimerRocket(5.f),
    timerPika(0.f),
    maxTimerPika(10.f)
{
    initWindows();
}

Engine::~Engine() {
    for (auto &ufo : ufos)
        delete ufo;
    for (auto &boss : bosses)
        delete boss;
    for (auto &pika : pikachus)
        delete pika;
    for (auto &REnemies : rocketEnemies)
        delete REnemies;
}
// accessor
const bool Engine::getWindowOpen() const
{
    return window.isOpen();
}

void Engine::closeGame()
{
    return window.close();
}

// private functions
void Engine::initVariable() {
    // INIT OBJ ITE
    background;
    rocket;
    i = 1;
    j = 1;
    k = 1;
    l = 1;
    // INIT MUSIC
    if (!gameMusic.openFromFile("D:/Coding/Project/SFML/RocketUp/Sound/GameSound.wav")) {
        std::cout << "CANNOT FIND MUSIC" << std::endl;
    }
    gameMusic.play();
    gameMusic.setLoop(true);

    // INIT HP
    hpBar.setSize(sf::Vector2f(250.f, 40.f));
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setPosition(sf::Vector2f(1000.f, 20.f));

    hpBarBack = hpBar;
    hpBarBack.setFillColor(sf::Color(230, 230, 230, 150));
    hpBarBack.setOutlineColor(sf::Color(230, 230, 230, 150));
    hpBarBack.setOutlineThickness(3);

    // INIT GAME OVER
    if (!gameOverTxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/GameOver.png")) {
        std::cout << "CANNOT FIND MUSIC" << std::endl;
    }
    gameOverSp.setTexture(gameOverTxt);
    gameOverSp.setPosition(640.f - 300.f, window.getSize().y / 2);
}
// initialize window
void Engine::initWindows() {
    videoMode.width = 1280;
    videoMode.height = 720;
    window.create(videoMode, "Space Run");
    window.setFramerateLimit(60);
}


/*
MAIN LOOP
*/

void Engine::run() {
    initVariable();
    initPoints();
    
    while(window.isOpen()) {
        pollEvent();
        if (rocket.getHp() > 0)
            update();
        render();
    }
}
// poll event inside main loop
void Engine::pollEvent() {
    event;
    while(window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }

    // Handle Keyboard Input
        if (event.type == sf::Event::KeyPressed) {
            // Quit
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
    }
}

/*
AFTER POLL EVENT
*/

void Engine::render() {
    // drawing
    window.clear(sf::Color::Black); 
    // BACKGROUND AND GUI 
    background.drawBackground(window);
    window.draw(Pointsbg);
    window.draw(PointsTxt);
    window.draw(hpBarBack);
    window.draw(hpBar);
    // OBJECT
    rocket.drawlocal(window);
    for (auto &ufo : ufos)
        ufo->drawObsl(window);
    for (auto &boss : bosses)
        boss->drawObsl(window);
    for (auto &pika : pikachus)
        pika->drawObsl(window);
    for (auto &REnemies : rocketEnemies)
        REnemies->drawObsl(window);
    // GAME OVER
    if (rocket.getHp() <= 0) {
        rocket.setHp(0);
        window.draw(gameOverSp);
    }
    window.display();
 }
 
// updating conditions - inside render

void Engine::update()
{
    updatePoints();
    updateHpBar();
    rocket.rocketMovement();
    rocket.rocketCollision();
    background.moveBackground();
    /*
        PHYSICS
    */


    // Set Timer
    deltaTime = dtclock.restart().asSeconds(); 

    /*
        CREATING OBSTACLES
    */
    
    timer += 1.f * deltaTime;// timer for ufo 
    // Create a new ufo
    if (timer >= maxTimer)
    {
        ufos.push_back(new Ufo(sf::Vector2f(rand() % (1280 - 80), -70.f), i));
        timer = 0.f;
        i++; // ufo type 
        j++; // ufo movement
        k++; // boss and pika movement
    }
    if (i == 5) i = 1;

    // Create a new boss
    timerBoss += 1.f * deltaTime;
    if (timerBoss >= maxTimerBoss)
    {
        bosses.push_back(new Boss(sf::Vector2f(520.f, -178.f)));
        timerBoss = 0.f;
    }
    // movement boss reset
    if (k == 6) k = 1;

    // Create a new Rocket enemy
    timerRocket += 1.f * deltaTime;
    if (timerRocket >= maxTimerRocket) {
        rocketEnemies.push_back(new RocketEnemy(sf::Vector2f(-80.f , rand() % (720 - 80))));
        timerRocket = 0.f;
    }

    // Create a new pikachu
    timerPika += 1.f * deltaTime;
    if (timerPika >= maxTimerRocket) {
        pikachus.push_back(new Pikachu(sf::Vector2f(rand() % (1280 - 80), -70.f)));
        timerPika = 0.f;
    }



    // Update TIMER 
    switch (points)
    {
    case 5:
        maxTimer = 2.5;
        break;
    case 10:
        maxTimer = 2.25;
        break;
    case 20:
        maxTimer = 2.f;
        maxTimerBoss = 27.5;
        break;
    case 30:
        maxTimer = 1.75;
        break;
    case 50:
        maxTimer = 1.5;
        maxTimerBoss = 25.f;
        break;
    case 75:
        maxTimer = 1.25;
        break;
    case 100:
        maxTimer = 1.f;
        maxTimerBoss = 22.5;
        break;
    case 130:
        maxTimer = 0.75;
        break;
    case 170:
        maxTimer = 0.5;
        maxTimerBoss = 20.f;
        break;
    default:
        break;
    }
    // UFO MOVEMENT UPDATE
    if (points <= 5) {
        if (j == 2) j = 1; 
    } else if (points <= 10) {
        if (j == 3) j = 1;
    } else if (points <= 20) {
        if (j == 4) j = 1;
    } else if (points <= 50) {
        if (j == 5) j = 1;
    } else if (points <= 100) {
        if (j == 6) j = 1;
    } else if (points <= 150) {
        if (j == 7) j = 1;
    } else {
        if (j == 8) j = 1;
    }
    // OBSTACLES MOVEMENT & WINDOW COLLISION
    for (auto &ufo : ufos){
        ufo->movementUfo(j);
        ufo->collision(); // window collision
    }

    for (auto &boss : bosses){
        boss->movementBoss(k);
        boss->collision(); // window collision
    }
    
    for (auto &pika : pikachus){
        pika->movementPika(k);
        pika->collision(); // window collision
    }

    for (auto &REnemies : rocketEnemies){
        REnemies->movementREnemy();
    }

    /*
        DELETING OBSTACLES
    */    
    
    for (int i = 0; i < ufos.size(); ++i){
        // window ufo collision
        if(ufos[i]->getposition().y + 60 >= window.getSize().y){
            delete ufos[i];
            ufos.erase(ufos.begin()+i);
            points++;
        }
        // rocket ufo collision
        if(ufos[i]->getBounds().intersects(rocket.getBounds()))
		{
			rocket.loseHp(1);
			delete ufos[i];
			ufos.erase(ufos.begin() + i);
		}
    }
    
    for (int i = 0; i < bosses.size(); ++i){
        // window boss collision
        if(bosses[i]->getposition().y + 174.f >= window.getSize().y){
            delete bosses[i];
            bosses.erase(bosses.begin()+ i);
            points++;
        }
        // rocket boss collision
        if(bosses[i]->getBounds().intersects(rocket.getBounds()))
		{
			rocket.loseHp(3);
			delete bosses[i];
			bosses.erase(bosses.begin() + i);
		}
    }

    for (int i = 0; i < pikachus.size(); ++i){
        // window PIKACHU collision
        if (pikachus[i]->getposition().y + 40.f > window.getSize().y) {
            delete pikachus[i];// ERROR GDB
            pikachus.erase(pikachus.begin() + i);
            points++;
        } 
        // rocket boss collision
        if (pikachus[i]->getBounds().intersects(rocket.getBounds()))
		{
			rocket.loseHp(2);
			delete pikachus[i];
			pikachus.erase(pikachus.begin() + i);
		}
    }
    
    for (int i = 0; i < rocketEnemies.size(); ++i){
        // window rocket enemies collision
        if(rocketEnemies[i]->getposition().x + 77.f >= window.getSize().x){
            delete rocketEnemies[i]; // ERRIR GDB
            rocketEnemies.erase(rocketEnemies.begin()+ i);
            points++;
        }
        // rocket rocket enemies collision
        if(rocketEnemies[i]->getBounds().intersects(rocket.getBounds()))
		{
			rocket.loseHp(1);
			delete rocketEnemies[i];
			rocketEnemies.erase(rocketEnemies.begin() + i);
		}
    }
}



/*
    POINTS
*/

void Engine::initPoints() {
    if (!Pointsbgtxt.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/Pointsbg.png")){
        std::cout << "ERROR ! PNG IS NOT FOUND !" << std::endl;
    }
    if (!font.loadFromFile("D:/Coding/Project/SFML/RocketUp/Fonts/VT323-Regular.ttf")){
        std::cout << "ERROR ! FONT IS NOT FOUND !" << std::endl;
    }
    Pointsbg.setTexture(Pointsbgtxt);
    Pointsbg.setPosition(sf::Vector2f(10.f, 10.f));
    PointsTxt.setFont(font);
    PointsTxt.setPosition(15.f , 10.f);
    PointsTxt.setCharacterSize(32);
    PointsTxt.setFillColor(sf::Color::White);
}

void Engine::updatePoints() {
    std::stringstream ss;
    ss << "POINTS : " << points;
    PointsTxt.setString(ss.str());
}

int Engine::getPoints() {
    return points;
}

void Engine::updateHpBar() {
    float hpPercent = static_cast<float>( rocket.getHp()) / rocket.getHpMax();
    hpBar.setSize(sf::Vector2f(250.f * hpPercent, hpBar.getSize().y));
}




