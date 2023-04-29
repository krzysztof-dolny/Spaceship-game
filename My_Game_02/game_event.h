#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game_event
{
public:
    Game_event(bool type);

    void update(const sf::Time& elapsed);

    //HPevnent funkcje
    void drawhp(sf::RenderTarget& window);
    void restarthp();
    sf::FloatRect get_hp_bounds();

private:

    //HP
    sf::Texture hptexture;
    sf::Sprite hpsprite;
    bool hpexist = false;
    float hptimer = 0;

    //HPevent funkcje
    void load_hp_texture();
    void updatehp(const sf::Time& elapsed);
};

#endif // GAME_EVENT_H
