#include "sounds.h"

Sounds::Sounds()
{
    create_sounds();
}

void Sounds::create_sounds()
{
    if(!sound_expl.loadFromFile("Sounds/explosion.wav")){
        std::cout << "Explosion sound loading error!";
    }

    if(!sound_loshp.loadFromFile("Sounds/losinghp.wav")){
        std::cout << "Losinghp sound loading error!";
    }
    if(!sound_gameov.loadFromFile("Sounds/gameover.wav")){
        std::cout << "Game over sound loading error!";
    }
    if(!reloading_sound_buffer.loadFromFile("Sounds/reloadingsound.wav")){
        std::cout << "Reloading sound loading error!";
    }
    if(!get_hp_sound_buffer.loadFromFile("Sounds/gethpsound.wav")){
        std::cout << "Gethp sound loading error!";
    }
    sound_gameover.setBuffer(sound_gameov);
    sound_gameover.setVolume(30.0);
    reloading_sound.setBuffer(reloading_sound_buffer);
    reloading_sound.setVolume(30.0);
    get_hp_sound.setBuffer(get_hp_sound_buffer);
    get_hp_sound.setVolume(30.0);
}

void Sounds::play_explosion_sound()
{
    for(auto& i : sound_explosion)
    {
        if(i.getStatus() == 0)
        {
            i.setBuffer(sound_expl);
            i.play();
            return;
        }
    }
    sound_explosion.push_back(sf::Sound());
    sound_explosion.back().setBuffer(sound_expl);
    sound_explosion.back().setVolume(30.0);
    sound_explosion.back().play();
}

void Sounds::play_losing_hp_sound()
{
    for(auto& i : sound_losinghp)
    {
        if(i.getStatus() == 0)
        {
            i.setBuffer(sound_loshp);
            i.play();
            return;
        }
    }
    sound_losinghp.push_back(sf::Sound());
    sound_losinghp.back().setBuffer(sound_loshp);
    sound_losinghp.back().setVolume(30.0);
    sound_losinghp.back().play();
}

void Sounds::play_gameover_sound()
{
    sound_gameover.play();
}

void Sounds::play_reloading_sound()
{
    reloading_sound.play();
}

void Sounds::play_get_hp_sound()
{
    get_hp_sound.play();
}
