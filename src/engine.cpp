#include "engine.hpp"
#include "rocket.hpp"
#include "obstacle.hpp"
#include "mainMenu.hpp"
#include <stdlib.h>
#include <iostream>
#include <sstream>

// cons decs
Engine::Engine(){
    initWindows();
    initVariable();
}

Engine::~Engine() {
    delete rocket;
    for (auto &ufo : ufos)
        delete ufo;
    for (auto &boss : bosses)
        delete boss;
    for (auto &pika : pikachus)
        delete pika;
    for (auto &REnemies : rocketEnemies)
        delete REnemies;
    for (auto &bullet : bullets)
        delete bullet;
    for (auto &bulletTXT : bulletTxtS)
        delete bulletTXT.second;
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
    // int points
    points = 0;
    // INT TIMER 
    timer = 0.f;
    maxTimer = 3.f ;
    timerBoss = 0.f;
    maxTimerBoss = 30.f;
    timerRocket = 0.f;
    maxTimerRocket = 5.f;
    timerPika = 0.f;
    maxTimerPika = 10.f;


    // INIT OBJ ITE
    background;
    rocket = new Rocket();
    rocket->setHp(10);
    rocket->resetRocketPosition();

    i = 1;
    j = 1;
    k = 1;
    l = 1;

    // INIT BULLET TEXTURE
    bulletTxtS["BULLET"] = new sf::Texture();
	bulletTxtS["BULLET"]->loadFromFile("../Gambar/bullet.png");
    
    // INIT MUSIC
    if (!gameMusic.openFromFile("../Sound/GameSound.wav")) {
        std::cout << "CANNOT FIND MUSIC" << std::endl;
    }
    gameMusic.play();
    gameMusic.setLoop(true);
    // INIT SOUND
    if (!bufferdestroy.loadFromFile("../Sound/Destroy.wav")) {
        std::cout << "CANNOT FIND SOUND" << std::endl; 
    }
    soundDs.setBuffer(bufferdestroy);
    if (!bufferCrash.loadFromFile("../Sound/Losehp.wav")) {
        std::cout << "CANNOT FIND SOUND" << std::endl; 
    }
    soundcr.setBuffer(bufferCrash);
    if (!buffergameOver.loadFromFile("../Sound/GameOverSound.wav")) {
        std::cout << "CANNOT FIND SOUND" << std::endl; 
    }
    soundgO.setBuffer(buffergameOver);

    // INIT HP
    hpBar.setSize(sf::Vector2f(250.f, 40.f));
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setPosition(sf::Vector2f(1000.f, 20.f));

    hpBarBack = hpBar;
    hpBarBack.setFillColor(sf::Color(230, 230, 230, 150));
    hpBarBack.setOutlineColor(sf::Color(230, 230, 230, 150));
    hpBarBack.setOutlineThickness(3);

    initPoints();
  
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
    while(window.isOpen()) {
        pollEvent();
        if (!isGameOver())
            update();
        if (RestartPressed()){
            update();
        }
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
            if(isGameOver()){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    window.close();
                    Menu *menu = new Menu;
                    menu->run_menu();
                }
            }
        }
        
        if (RestartPressed()){
            initVariable();
            run();
        }

    }
}

// Game Over
bool Engine::isGameOver()
{
    if (rocket->getHp() <= 0) {
        soundgO.play();
        return true;
    } else {
        return false;
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
    rocket->drawlocal(window);
    for (auto &ufo : ufos)
        ufo->drawObsl(window);
    for (auto &boss : bosses)
        boss->drawObsl(window);
    for (auto &pika : pikachus)
        pika->drawObsl(window);
    for (auto &REnemies : rocketEnemies)
        REnemies->drawObsl(window);
    for (auto &bullet : bullets)
        bullet->render(window);
    // GAME OVER
    if (isGameOver()){
        gameMusic.stop();
        GameOverDisplay();
        window.draw(gameOverSp);  
        window.draw(PlayAgain);
    }
    window.display();
 }

// updating conditions - inside render

void Engine::update()
{
    updatePoints();
    updateHpBar();
    rocket->rocketMovement();
    rocket->rocketCollision();
    background.moveBackground();
    updateBullets();

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
        maxTimerRocket = 4.75;
        break;
    case 30:
        maxTimer = 1.75;
        break;
    case 50:
        maxTimer = 1.5;
        maxTimerBoss = 25.f;
        maxTimer = 4.5;
        maxTimerPika = 9.5;
        break;
    case 75:
        maxTimer = 1.25;
        break;
    case 100:
        maxTimer = 1.f;
        maxTimerBoss = 22.5;
        maxTimerRocket = 4.f;
        maxTimerPika = 9.f;
        break;
    case 130:
        maxTimer = 0.75;
        break;
    case 170:
        maxTimer = 0.5;
        maxTimerBoss = 20.f;
        maxTimerRocket = 3.5;
        maxTimerPika = 8.f;
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
        }
        // rocket ufo collision
        if(ufos[i]->getBounds().intersects(rocket->getBounds()))
		{
            soundcr.play();
			rocket->loseHp(1);
			delete ufos[i];
			ufos.erase(ufos.begin() + i);
		}
        // ufo bullet collision
        for (int k = 0; k < bullets.size(); ++k)
		{
			if (ufos[i]->getBounds().intersects(bullets[k]->getBounds()))
			{
                soundDs.play();
                points++;
                ufos[i]->loseHp(1);
                if (ufos[i]->getHp() <= 0){
                    delete ufos[i];
				    ufos.erase(ufos.begin() + i);
                }
				delete bullets[k];
				bullets.erase(bullets.begin() + k);	
			}
		}
    }
    
    for (int i = 0; i < bosses.size(); ++i){
        // window boss collision
        if(bosses[i]->getposition().y + 174.f >= window.getSize().y){
            delete bosses[i];
            bosses.erase(bosses.begin()+ i);
        }
        // rocket boss collision
        if(bosses[i]->getBounds().intersects(rocket->getBounds()))
		{
            soundcr.play();
			rocket->loseHp(3);
			delete bosses[i];
			bosses.erase(bosses.begin() + i);
		}
        // Boss Bullet
        for (int k = 0; k < bullets.size(); ++k)
		{
			if (bosses[i]->getBounds().intersects(bullets[k]->getBounds()))
			{
                soundDs.play();
                points += 10;
                bosses[i]->loseHp(1);
                if (bosses[i]->getHp() <= 0){
                    delete bosses[i];
				    bosses.erase(bosses.begin() + i);
                }
				delete bullets[k];
				bullets.erase(bullets.begin() + k);	
			}
		}
    }

    for (int i = 0; i < pikachus.size(); ++i){
        // window PIKACHU collision
        if (pikachus[i]->getposition().y + 40.f > window.getSize().y) {
            delete pikachus[i];// ERROR GDB
            pikachus.erase(pikachus.begin() + i);
        } 
        // pikachu boss collision
        if (pikachus[i]->getBounds().intersects(rocket->getBounds()))
		{
            soundcr.play();
			rocket->loseHp(2);
			delete pikachus[i];
			pikachus.erase(pikachus.begin() + i);
		}
        // pikachu bullet collision
        for (int k = 0; k < bullets.size(); ++k)
		{
			if (pikachus[i]->getBounds().intersects(bullets[k]->getBounds()))
			{
                soundDs.play();
                points++;
                pikachus[i]->loseHp(1);
                if (pikachus[i]->getHp() <= 0){
                    delete pikachus[i];
				    pikachus.erase(pikachus.begin() + i);
                }
				delete bullets[k];
				bullets.erase(bullets.begin() + k);	
			}
		}
    }
    
    for (int i = 0; i < rocketEnemies.size(); ++i){
        // window rocket enemies collision
        if(rocketEnemies[i]->getposition().x + 77.f >= window.getSize().x){
            delete rocketEnemies[i]; // ERRIR GDB
            rocketEnemies.erase(rocketEnemies.begin()+ i);
        }
        // rocket rocket enemies collision
        if(rocketEnemies[i]->getBounds().intersects(rocket->getBounds()))
		{
            soundcr.play();
			rocket->loseHp(1);
			delete rocketEnemies[i];
			rocketEnemies.erase(rocketEnemies.begin() + i);
		}
        // Rocket enemy bullet collision
        for (int k = 0; k < bullets.size(); ++k)
		{
			if (rocketEnemies[i]->getBounds().intersects(bullets[k]->getBounds()))
			{
                soundDs.play();
                points++;
                rocketEnemies[i]->loseHp(1);
                delete rocketEnemies[i];
                rocketEnemies.erase(rocketEnemies.begin() + i);
				delete bullets[k];
				bullets.erase(bullets.begin() + k);	
			}
		}
    }
}



/*
    POINTS
*/

void Engine::initPoints() {
    if (!Pointsbgtxt.loadFromFile("../Gambar/Pointsbg.png")){
        std::cout << "ERROR ! PNG IS NOT FOUND !" << std::endl;
    }
    if (!font.loadFromFile("../Fonts/VT323-Regular.ttf")){
        std::cout << "ERROR ! FONT IS NOT FOUND !" << std::endl;
    }
    Pointsbg.setTexture(Pointsbgtxt);
    Pointsbg.setPosition(sf::Vector2f(10.f, 10.f));
    PointsTxt.setFont(font);
    PointsTxt.setPosition(15.f , 10.f);
    PointsTxt.setCharacterSize(32);
    PointsTxt.setFillColor(sf::Color::Red);
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
    float hpPercent = static_cast<float>( rocket->getHp()) / rocket->getHpMax();
    hpBar.setSize(sf::Vector2f(250.f * hpPercent, hpBar.getSize().y));
}

/*
    GAME OVER
*/

void Engine::GameOverDisplay()
{
      // INIT GAME OVER
    if (!gameOverTxt.loadFromFile("../Gambar/GameOver.png")) {
        std::cout << "CANNOT FIND MUSIC" << std::endl;
    }
    gameOverSp.setTexture(gameOverTxt);
    gameOverSp.setPosition(640.f - 300.f, window.getSize().y / 2);

    PlayAgain.setFont(font);
    PlayAgain.setString("Press Enter to Play Again\n\nPress Space to go to Main Menu");
    PlayAgain.setPosition(sf::Vector2f(640 - PlayAgain.getGlobalBounds().width / 2, 500 - PlayAgain.getGlobalBounds().height / 2));
    PlayAgain.setCharacterSize(40);
    PlayAgain.setOutlineColor(sf::Color::Black);
    PlayAgain.setOutlineThickness(3);
}

bool Engine::RestartPressed()
{
    if (isGameOver()){
        if(event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                return true;
            }
        }
    } 
    return false;
}

/*
    BULLETS AND ATTACKING
*/


void Engine::updateBullets()
{
    // bullet mouse input
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rocket->canAtt())
	{
		bullets.push_back(
			new RocketBullet(bulletTxtS["BULLET"], rocket->getRocketPosition().x + rocket->getBounds().width/2.f - 6.f, 
			rocket->getRocketPosition().y, 0.f, -1.f, 5.f)
        );
    }

    rocket->updateAtt();

    for (auto &bullet : bullets) {
        bullet->update();
    }

	// Deleting
    for (int i = 0; i < bullets.size(); ++i){
        // window bullet collision
        if (bullets[i]->getBounds().top + bullets[i]->getBounds().height < 0.f) {
            //Delete bullet
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }

    }

   
}

