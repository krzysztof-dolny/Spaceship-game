#ifndef ASTEROID_H
#define ASTEROID_H

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Asteroid
{
public:
    Asteroid();
    Asteroid(sf::Texture* asteroidtexture, float movementspeed);
    ~Asteroid();

    //Funkcje główne
    void update();
    void draw(sf::RenderTarget* window);

    //Dostęp do pozycji
    sf::FloatRect get_asteroid_bounds();
    sf::Vector2f explosion_position();

    //HP asteroidy
    int asteroidHP;

private:

    //Textury
    sf::Sprite asteroid_sprite;

    //Ruch asteroidy
    sf::Vector2f direction;
    float movement_speed;
    float rotation_speed;

    //Funkcja losująca
    float randx();
};

#endif // ASTEROID_H
