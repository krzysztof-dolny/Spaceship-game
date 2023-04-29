#include "explosion.h"

//--------------------
// Konstruktory i destruktory
//--------------------

Explosion::Explosion()
{

}

Explosion::~Explosion()
{

}

Explosion::Explosion(sf::Texture* explosiontexture, sf::Vector2f explosionpos)
{
    explosion_sprite.setTexture(*explosiontexture);
    explosion_sprite.setPosition(explosionpos);
    explosion_sprite.setScale(0.5, 0.5);
    explosion_sprite.setTextureRect(sf::IntRect(0, 0, 192, 192));
}

//--------------------
// Funkcje główne
//--------------------

void Explosion::draw(sf::RenderTarget *window)
{    
    window->draw(explosion_sprite);
}

bool Explosion::update()
{
    if(explosion_sprite.getTextureRect() == sf::IntRect(0, 0, 192, 192)){
        explosion_sprite.setTextureRect(sf::IntRect(192, 0, 192, 192));
    }
    else if(explosion_sprite.getTextureRect() == sf::IntRect(192, 0, 192, 192)){
        explosion_sprite.setTextureRect(sf::IntRect(384, 0, 192, 192));
    }
    else if(explosion_sprite.getTextureRect() == sf::IntRect(384, 0, 192, 192)){
        explosion_sprite.setTextureRect(sf::IntRect(576, 0, 192, 192));
    }
    else if(explosion_sprite.getTextureRect() == sf::IntRect(576, 0, 192, 192)){
        explosion_sprite.setTextureRect(sf::IntRect(768, 0, 192, 192));
    }
    else if(explosion_sprite.getTextureRect() == sf::IntRect(768, 0, 192, 192)){
        explosion_sprite.setTextureRect(sf::IntRect(0, 192, 192, 192));
    }
    else if(explosion_sprite.getTextureRect() == sf::IntRect(0, 192, 192, 192)){
        explosion_sprite.setTextureRect(sf::IntRect(192, 192, 192, 192));
    }
    else if(explosion_sprite.getTextureRect() == sf::IntRect(192, 192, 192, 192)){
        return true;
    }
    return false;
}

