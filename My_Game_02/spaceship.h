#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "bullet.h"
#include "asteroid.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Spaceship
{
public:
    Spaceship();
    ~Spaceship();

    //Funkcje główne
    void update(sf::Clock& reload_clock);
    void draw(sf::RenderTarget& window);

    //Funkcje poboczne
    void create_bar(sf::RenderTarget& window);
    void create_points();
    void create_ammo();

    bool can_shoot();

    bool asteroid_canspawn();
    std::string rand_asteroid();

    bool has_ammo();
    void decrease_ammo();

    void reload();
    bool is_reloading();

    //Zmienne statku
    int HP= 10 ;
    bool HPchanged = false;
    int points = 0;

    //Dostęp do pozycji
    sf::FloatRect get_ship_bounds();
    sf::Vector2f get_position_for_bullets();


private:

    //Funkcje aktualizujące
    void update_spaceship_animation();
    void update_bar();
    void update_points();
    void update_ammo();
    void update_reload(sf::Clock& reload_clock);
    void spaceship_movement();

    //Ładowanie textur i czcionki
    void load_font();
    void load_texture();

    //Textury, kształty i czcionki
    sf::Font font;
    sf::Text text;
    sf::Texture spaceship_texture;
    sf::Sprite spaceship_sprite;
    sf::IntRect current_sprite;
    sf::Clock animation_timer;
    sf::RectangleShape HP_bar;
    sf::RectangleShape HP_barmax;

    //Bool'e
    bool moveing_left = false;
    bool moveing_right = false;
    bool has_ammunition = true;
    bool reloading = false;

    //Colldowny
    float attack_cooldown = 10;
    const float attack_cooldownmax = 20;
    float asteroid_cooldown = -25;
    float asteroid_cooldownmax = 5;
    sf::Clock asteroid_clock;

    //Ammo
    float ammo = 30;
    sf::Text ammo_text;

    //Reload
    float reloading_timer = 0;
    float reloading_timer_max = 2.5;

    //Hp
    float HPbuffor = 1;
    int HPmax = 10;
};

#endif // SPACESHIP_H
