#include "mainMenu.hpp"
#include "engine.hpp"

Menu::Menu(){
    window = new sf::RenderWindow();
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    set_values();
}

Menu::~Menu(){
    delete window;
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Menu::set_values(){
    // Window
    window->create(sf::VideoMode(1280,720), "MAIN MENU", sf::Style::Titlebar | sf::Style::Close);
    
    // play music
    

    pos = 0; // selecting menu
    pressed = theselect = false;
    // Load file
    font->loadFromFile("../Fonts/VT323-Regular.ttf");
    image->loadFromFile("../Gambar/mainMenu.png");
    txtBgtxt.loadFromFile("../Gambar/Button.png");
    if (!txtbgHelpCR.loadFromFile("../Gambar/HelpCreditBg.png")){
        std::cout << "BACKGROUND NOT LOADED" << std::endl;
    }
    txtBg1.setTexture(txtBgtxt);
    txtBg2.setTexture(txtBgtxt);
    txtBg3.setTexture(txtBgtxt);
    txtBg4.setTexture(txtBgtxt);
    bg->setTexture(*image);

    // Background Text
    txtBg1.setScale(0.15, 0.15);
    txtBg2 = txtBg3 = txtBg4 = txtBg1;
    txtBg1.setPosition(sf::Vector2f(525, 400));
    txtBg2.setPosition(sf::Vector2f(525, 460));
    txtBg3.setPosition(sf::Vector2f(525, 520));
    txtBg4.setPosition(sf::Vector2f(525, 580));

    pos_mouse = {0,0};
    mouse_coord = {0, 0};

    options = {"---", "Play", "Help", "Credits", "Quit"};
    texts.resize(5);
    coords = {{590,40},{550,450},{550,510},{550,570},{550,630}};
    sizes = {20,44,40,40,40};

    for (std::size_t i{}; i < texts.size(); ++i){
    texts[i].setFont(*font); 
    texts[i].setString(options[i]); 
    texts[i].setCharacterSize(sizes[i]);
    texts[i].setOutlineColor(sf::Color::Black);
    texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(4);
    pos = 1;

    winclose->setSize(sf::Vector2f(23,26));
    winclose->setPosition(1178,39);
    winclose->setFillColor(sf::Color::Red);

}

void Menu::loop_events(){
    sf::Event event;
    while(window->pollEvent(event)){
        if( event.type == sf::Event::Closed){
            window->close();
        }
        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);
        // MOVING UP AND DOWN
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed){
            if( pos < 4){
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos - 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed){
            if( pos > 1){
                --pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos + 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }
        // SELECTING MENU
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect){
            theselect = true;
            if (pos == 4){
                window->close();
            }
            if (pos == 1) {
                MainMenuMusic.stop();
                window->close();
                Engine engine;
                engine.run();
            } else if (pos == 2){
                window->close();
                sf::RenderWindow Help(sf::VideoMode(1280, 720), "Help");
                // INIT VARIABLE FOR HELP
                sf::Sprite bgHelp;
                bgHelp.setTexture(txtbgHelpCR);
                
                strings = {"CONTROL", 
                "PRESS [ W ] TO MOVE UP", 
                "PRESS [ S ] TO MOVE DOWN", 
                "PRESS [ D ] TO MOVE RIGHT", 
                "PRESS [ A ] TO MOVE LEFT", 
                "LEFT CLICK MOUSE TO SHOOT",
                "PRESS [ ENTER ] TO GO BACK TO MAIN MENU "
                };
                HelpTexts.resize(7);
                coordsHelp = {{530,40},{450,200},{450,240},{450,280},{450,320},{450, 360}, {450, 500}};
                Helptxtsizes = {80, 40, 40, 40, 40, 40, 40};

                for (std::size_t i{}; i < HelpTexts.size(); ++i){
                HelpTexts[i].setFont(*font); 
                HelpTexts[i].setString(strings[i]); 
                HelpTexts[i].setCharacterSize(Helptxtsizes[i]);
                HelpTexts[i].setOutlineColor(sf::Color::Black);
                HelpTexts[i].setPosition(coordsHelp[i]);
                }

                while(Help.isOpen()){
                    sf::Event event;
                    while(Help.pollEvent(event)){
                        if (event.type == sf::Event::Closed) {
                            Help.close();
                        }
                    // Handle Keyboard Input
                        if (event.type == sf::Event::KeyPressed) {
                            // Quit
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                Help.close();
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                                MainMenuMusic.stop();
                                Help.close();
                                Menu *menu = new Menu;
                                menu->run_menu();
                            }
                        }
                    }
                    // update

                    // Render
                    Help.clear();
                    Help.draw(bgHelp);
                    for (auto &txt: HelpTexts){
                        Help.draw(txt);
                    }
                    Help.display();
                }
            } else if(pos == 3) {
                window->close();
                sf::RenderWindow Credit(sf::VideoMode(1280, 720), "Credits");
                // INIT VARIABLE FOR HELP
                sf::Sprite bgCr;
                bgCr.setTexture(txtbgHelpCR);
        
                strings = {"UNIVERSITAS SEBELAS MARET", 
                "1. Eka Putra Meravigliosi\tL0122051", 
                "2. Fadhila Nur Aisyah\t\tL0122058", 
                "3. Hajid Lutfi Hidayanto\tL0122071", 
                "4. Irfan Adi Prasetya\t\tL0122079" 
                };
                CRTexts.resize(5);
                coordsCR = {{300,40},{350,200},{350,240},{350,280},{350,320}};
                CRtxtsizes = {80, 40, 40, 40, 40};

                for (std::size_t i{}; i < CRTexts.size(); ++i){
                CRTexts[i].setFont(*font); 
                CRTexts[i].setString(strings[i]); 
                CRTexts[i].setCharacterSize(CRtxtsizes[i]);
                CRTexts[i].setOutlineColor(sf::Color::Black);
                CRTexts[i].setPosition(coordsCR[i]);
                }

                while(Credit.isOpen()){
                    sf::Event event;
                    while(Credit.pollEvent(event)){
                        if (event.type == sf::Event::Closed) {
                            Credit.close();
                        }
                    // Handle Keyboard Input
                        if (event.type == sf::Event::KeyPressed) {
                            // Quit
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                Credit.close();
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                                Credit.close();
                                MainMenuMusic.stop();
                                Menu *menu = new Menu;
                                menu->run_menu();
                            }
                        }
                    }
                    // update

                    // Render
                    Credit.clear();
                    Credit.draw(bgCr);
                    for (auto &txt: CRTexts){
                        Credit.draw(txt);
                    }
                    Credit.display();
                }
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(winclose->getGlobalBounds().contains(mouse_coord)){
                window->close();
            }
        }
    }
    }

void Menu::draw_all(){
    window->clear();
    window->draw(*bg);
    window->draw(txtBg1);
    window->draw(txtBg2);
    window->draw(txtBg3);
    window->draw(txtBg4);
    for(auto t : texts){
    window->draw(t); 
    }
    window->display();
 }

void Menu::run_menu(){
    if (!MainMenuMusic.openFromFile("../Sound/MmSound.wav")) {
        std::cout << "CANNOT FIND MUSIC" << std::endl;
    }
    MainMenuMusic.setLoop(true);
    MainMenuMusic.play();
    while(window->isOpen()){
        loop_events();
        draw_all();
    }
}