#ifndef GAME_H
#define GAME_H

#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include "explosion.h"
#include "sounds.h"
#include "game_event.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Game
{
public:
    Game();
    ~Game();

private:

    //Okno
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text text[3];

    //Statek
    Spaceship* spaceship;
    sf::Clock reload_clock;

    //Pociski
    std::map<std::string, sf::Texture*> bullet;
    std::vector<Bullet*> bullets;

    //Asteroidy
    std::map<std::string, sf::Texture*> asteroid;
    std::vector<Asteroid*> asteroids;

    //Interfejs
    sf::Texture background_texture;
    sf::Sprite background;
    sf::IntRect current_backgraound;

    //Eksplozje
    std::map<std::string, sf::Texture*> explosion;
    std::vector<Explosion*> explosions;
    sf::Vector2f explosionpos = {0, 0};
    sf::Clock explosion_timer;

    //Funkcje główne
    void run();
    void update();
    void draw();
    void gamelost();

    //Funkcje tworzące
    void create_window();
    void create_bullets();
    void create_asteroids();
    void create_background();
    void create_explosions();
    void create_font();
    void create_events();
    void restart_timers();

    //Funkcje poboczne
    void draw_spaceship();
    void draw_events();
    void update_bullets();
    void update_asteroids();
    void update_backgroung();
    void update_bullet_asteroid_collisions();
    void update_spaceship_asteroid_collisions();
    void update_spaceship_hp_collisions();
    void update_explosions();
    void update_explosions_animation();
    void update_events();

    //Bool'e
    bool explosion_bool = false;
    bool endgame = false;

    //Eventy
    Game_event* hp_event;
    sf::Clock event_timer;

    //Dźwięki zmienne
    Sounds* sounds;
};

#endif // GAME_H
