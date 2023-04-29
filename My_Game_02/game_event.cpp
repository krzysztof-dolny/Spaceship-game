#include "game_event.h"

Game_event::Game_event(bool type)
{
    if(type)
    {
        load_hp_texture();
    }
}

void Game_event::load_hp_texture()
{
    hptexture.loadFromFile("Graphics/HP.png");
    hpsprite.setTexture(hptexture);
    hpsprite.setScale(0.0, 0.0);
}

void Game_event::update(const sf::Time& elapsed)
{
    updatehp(elapsed);
}

void Game_event::updatehp(const sf::Time& elapsed)
{
    hptimer += elapsed.asSeconds();

    if(hpexist == false && hptimer > 10)
    {
        hpsprite.setPosition(rand() % 800 + 100, 0 - hpsprite.getGlobalBounds().height);
        hpsprite.setScale(0.75, 0.75);
        hpexist = true;
    }

    if(hpexist == true && hpsprite.getGlobalBounds().top >= 800.0){
        restarthp();
    }
    hpsprite.move(0.0, 100.0 * elapsed.asSeconds());
}

void Game_event::restarthp()
{
    hpexist = false;
    hptimer = 0;
    hpsprite.setScale(0.0, 0.0);
}

void Game_event::drawhp(sf::RenderTarget& window)
{
    window.draw(hpsprite);
}

sf::FloatRect Game_event::get_hp_bounds()
{
    return hpsprite.getGlobalBounds();
}
