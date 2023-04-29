#include "bullet.h"

//--------------------
// Konstruktory i destruktory
//--------------------

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

Bullet::Bullet(sf::Texture* bullet_texture, sf::Vector2f spaceship_position , float x, float y, float movement_speed_)
{
    bullet_sprite.setTexture(*bullet_texture);
    bullet_sprite.setPosition(spaceship_position);
    direction.x = x;
    direction.y = y;
    movement_speed = movement_speed_;
}

//--------------------
// Funkcje główne
//--------------------

void Bullet::update()
{
    bullet_sprite.move(movement_speed * direction);
}

void Bullet::draw(sf::RenderTarget* window)
{
    window->draw(bullet_sprite);
}

//--------------------
// Funckje poboczne
//--------------------

sf::FloatRect Bullet::get_bullet_bounds()
{
    return bullet_sprite.getGlobalBounds();
}

