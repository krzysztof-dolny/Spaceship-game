#ifndef MENU_H
#define MENU_H

#include <game.h>

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu();
    ~Menu();
    void run_menu();

private:
    //Funkcje główne
    void update();
    void draw();

    //Tworzenie
    void assign_variables();

    void creatback();
    sf::Texture background_texture;
    sf::Sprite background;

    sf::Texture credits_texture;
    sf::Sprite credits_sprite;
    sf::Text goback;

    void creatwindow();
    sf::RenderWindow* window;
    sf::VideoMode videomode;

    //Menu
    void menu_options();
    void options();
    void credits();
    void draw_text();

    int menukey = 0;

    //Obsługa zdarzeń
    void mouseactions();

    //Text
    sf::Font font;
    sf::Text text[4];
    sf::Text options_text[6];

    //Gra
    Game* game;
};

#endif // MENU_H
