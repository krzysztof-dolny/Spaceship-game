#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <iostream>
#include <ctime>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Explosion
{
public:
    Explosion();
    Explosion(sf::Texture* explosion_texture, sf::Vector2f explosion_position);
    ~Explosion();

    //Funkcje główne
    bool update();
    void draw(sf::RenderTarget* window);


private:
    //Textrury
    sf::Sprite explosion_sprite;
};

#endif // EXPLOSION_H
