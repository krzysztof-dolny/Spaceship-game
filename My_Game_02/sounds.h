#ifndef SOUNDS_H
#define SOUNDS_H

#include <iostream>
#include <vector>

#include <SFML/Audio.hpp>

class Sounds
{
public:
    Sounds();

    //Odtwrzarze dźwięków
    void play_losing_hp_sound();
    void play_explosion_sound();
    void play_gameover_sound();
    void play_reloading_sound();
    void play_get_hp_sound();

private:
    //Metody
    void create_sounds();

    //Zmienne
    sf::SoundBuffer sound_expl;
    std::vector<sf::Sound> sound_explosion;
    sf::SoundBuffer sound_loshp;
    std::vector<sf::Sound> sound_losinghp;
    sf::SoundBuffer sound_gameov;
    sf::Sound sound_gameover;
    sf::SoundBuffer reloading_sound_buffer;
    sf::Sound reloading_sound;
    sf::SoundBuffer get_hp_sound_buffer;
    sf::Sound get_hp_sound;
};

#endif // SOUNDS_H
