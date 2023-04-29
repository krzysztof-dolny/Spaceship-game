#ifndef BULLET_H
#define BULLET_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Bullet
{
public:
    Bullet();
    Bullet(sf::Texture* bullet_texture, sf::Vector2f spaceship_position,float x, float y, float movement_speed_);
    ~Bullet();

    //Funkcje główne
    void update();
    void draw(sf::RenderTarget* window);

    //Funkcje poboczne
    sf::FloatRect get_bullet_bounds();

private:
    //Textura
    sf::Sprite bullet_sprite;

    //Ruch pocisków
    sf::Vector2f direction;
    float movement_speed;

};

#endif // BULLET_H
