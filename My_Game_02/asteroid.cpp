#include "asteroid.h"

//--------------------
// Konstuktory i destruktory
//--------------------

Asteroid::Asteroid()
{

}

Asteroid::~Asteroid()
{

}

Asteroid::Asteroid(sf::Texture* asteroidtexture, float movement_speed_)
{
    asteroid_sprite.setTexture(*asteroidtexture);
    asteroid_sprite.setScale(0.5, 0.5);
    asteroid_sprite.setPosition(rand() % 1000, 0.0 - asteroid_sprite.getGlobalBounds().height);
    direction.x = randx();
    direction.y = 1.0;
    movement_speed = movement_speed_ * (static_cast<float>(rand() % 150) / 100.0 + 1.0);
    rotation_speed = 0.75;
}

//--------------------
// Funkcje główne
//--------------------

void Asteroid::update()
{
    asteroid_sprite.move(movement_speed * direction);
    asteroid_sprite.rotate(rotation_speed);
}

void Asteroid::draw(sf::RenderTarget* window)
{
    window->draw(asteroid_sprite);
}

//--------------------
// Dostęp do pozycji
//--------------------

sf::FloatRect Asteroid::get_asteroid_bounds()
{
    return asteroid_sprite.getGlobalBounds();
}

sf::Vector2f Asteroid::explosion_position()
{
    float x = asteroid_sprite.getGlobalBounds().left;
    float y = asteroid_sprite.getGlobalBounds().top;

    return {x, y};
}

//--------------------
// Losowe liczby
//--------------------

float Asteroid::randx()
{
    int i = rand() % 2;
    float x = rand() % 5;
    //std::cout << x << "\n";
    x = x/10;
    //std::cout << x << "\n";
    if(i == 0){
        return -x;
    }
    return x;
}


