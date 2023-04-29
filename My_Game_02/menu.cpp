#include "menu.h"

//--------------------
// Konstruktor i destruktor
//--------------------

Menu::Menu()
{
    assign_variables();
    creatwindow();
}

Menu::~Menu()
{
    delete window;
}

//--------------------
// Funkcje główne
//--------------------

void Menu::run_menu()
{
    while(window->isOpen())
    {
        update();
        draw();
    }
}

void Menu::draw()
{
    window->clear();
    window->draw(background);
    menu_options();
    window->display();
}

void Menu::update()
{
    sf::Event ev;
    while(window->pollEvent(ev))
    {
        if(ev.Event::type == sf::Event::Closed)
        {
            window->close();
        }
    }
    mouseactions();
}

//--------------------
// Tworzenie okna / załadowanie zmiennych
//--------------------

void Menu::assign_variables()
{
    videomode = sf::VideoMode(1000, 800);
    if(!font.loadFromFile("Fonts/my_font.ttf")){
        std::cout << "Font loading error!" << "\n";
    }
    creatback();
}

void Menu::creatwindow()
{
    window = new sf::RenderWindow(videomode, "Menu", sf::Style::Close);
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}

//--------------------
// Opcje menu
//--------------------

void Menu::menu_options()
{
    if(menukey == 0){
        draw_text();
    }
    else if(menukey == 1){
        window->close();
        game = new Game();
    }
    else if(menukey == 2){
        options();
    }
    else if(menukey == 3){
        credits();
    }
}

void Menu::options()
{
    options_text[0].setFont(font);
    options_text[0].setFillColor(sf::Color::White);
    options_text[0].setString("Shooting: Hold space");
    options_text[0].setScale(1.75, 1.75);
    options_text[0].setPosition(10.0, 10.0);

    options_text[1].setFont(font);
    options_text[1].setFillColor(sf::Color::White);
    options_text[1].setString("Move up: W");
    options_text[1].setScale(1.75, 1.75);
    options_text[1].setPosition(10.0, 100.0);

    options_text[2].setFont(font);
    options_text[2].setFillColor(sf::Color::White);
    options_text[2].setString("Move left: A");
    options_text[2].setScale(1.75, 1.75);
    options_text[2].setPosition(10.0, 200.0);

    options_text[3].setFont(font);
    options_text[3].setFillColor(sf::Color::White);
    options_text[3].setString("Move down: S");
    options_text[3].setScale(1.75, 1.75);
    options_text[3].setPosition(10.0, 300.0);

    options_text[4].setFont(font);
    options_text[4].setFillColor(sf::Color::White);
    options_text[4].setString("Move right: D");
    options_text[4].setScale(1.75, 1.75);
    options_text[4].setPosition(10.0, 400.0);

    options_text[5].setFont(font);
    options_text[5].setFillColor(sf::Color::White);
    options_text[5].setString("Reload: R");
    options_text[5].setScale(1.75, 1.75);
    options_text[5].setPosition(10.0, 500.0);

    goback.setFont(font);
    goback.setFillColor(sf::Color::Red);
    goback.setString("<-- Go back");
    goback.setScale(1.75, 1.75);
    goback.setPosition(10.0, 600.0);
    window->draw(goback);

    for(int i = 0; i < 6; i++){
        window->draw(options_text[i]);
    }
}

void Menu::credits()
{
    credits_texture.loadFromFile("Graphics/Credits.png");
    credits_sprite.setTexture(credits_texture);
    credits_sprite.setScale(1.0, 1.0);
    credits_sprite.setTextureRect(sf::IntRect(0, 0, 1000, 800));
    window->draw(credits_sprite);

    goback.setFont(font);
    goback.setFillColor(sf::Color::Red);
    goback.setString("<-- Go back");
    goback.setScale(1.5, 1.5);
    goback.setPosition(50.0, 700.0);
    window->draw(goback);
}

void Menu::draw_text()
{
    text[0].setFont(font);
    text[0].setFillColor(sf::Color::Red);
    text[0].setString("Play");
    text[0].setScale(3.0, 3.0);
    text[0].setPosition(window->getSize().x/2-(text[0].getGlobalBounds().width/2), window->getSize().y/5);

    text[1].setFont(font);
    text[1].setFillColor(sf::Color::Red);
    text[1].setString("Options");
    text[1].setScale(3.0, 3.0);
    text[1].setPosition(window->getSize().x/2-(text[1].getGlobalBounds().width/2), window->getSize().y/2.5);

    text[2].setFont(font);
    text[2].setFillColor(sf::Color::Red);
    text[2].setString("Exit");
    text[2].setScale(3.0, 3.0);
    text[2].setPosition(window->getSize().x/2-(text[2].getGlobalBounds().width/2), window->getSize().y/1.65);

    text[3].setFont(font);
    text[3].setFillColor(sf::Color::Red);
    text[3].setString("Credits");
    text[3].setScale(1.5, 1.5);
    text[3].setPosition(10.0, window->getSize().y - (2 * text[3].getGlobalBounds().height));

    for(int i = 0; i < 4; i++){
        window->draw(text[i]);
    }
}

//--------------------
// Obsługa myszy
//--------------------

void Menu::mouseactions()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        sf::Vector2f MousePos = window->mapPixelToCoords(mouse_pos);

        if(menukey == 0){
            if(text[0].getGlobalBounds().contains(MousePos)){
                menukey = 1;
            }
            if(text[1].getGlobalBounds().contains(MousePos)){
                menukey = 2;
            }
            if(text[2].getGlobalBounds().contains(MousePos)){
                window->close();
            }
            if(text[3].getGlobalBounds().contains(MousePos)){
                menukey = 3;
            }
        }

        if(menukey == 3 || menukey == 2){
            if(goback.getGlobalBounds().contains(MousePos)){
                menukey = 0;
            }
        }
    }
}

//--------------------
// Tło
//--------------------

void Menu::creatback()
{
    background_texture.loadFromFile("Graphics/Tlo.png");
    background.setTexture(background_texture);
    background.setScale(1.0, 1.0);
    background.setTextureRect(sf::IntRect(0, 850, 1000, 800));
}
