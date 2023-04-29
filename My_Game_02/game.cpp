#include "game.h"

//--------------------
// Konstruktor i destruktor
//--------------------

Game::Game()
{
    create_window();
    spaceship = new Spaceship();
    spaceship->create_bar(*window);
    spaceship->create_points();
    spaceship->create_ammo();
    sounds = new Sounds();
    create_bullets();
    create_asteroids();
    create_background();
    create_font();
    create_explosions();
    create_events();
    restart_timers();
    run();
}

Game::~Game()
{
    delete window;
    delete spaceship;
    for(auto &i : asteroid){
        delete i.second;
    }
    for(auto* i : asteroids){
        delete i;
    }
    for(auto &i : bullet){
        delete i.second;
    }
    for(auto* i : bullets){
        delete i;
    }
    for(auto &i : explosion){
        delete i.second;
    }
    for(auto* i : explosions){
        delete i;
    }
    delete sounds;
    delete hp_event;
}

//--------------------
// Stworzenie okna i timerów
//--------------------

void Game::create_window()
{
    window = new sf::RenderWindow(sf::VideoMode(1000, 800), "Game", sf::Style::Close);
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}

void Game::restart_timers()
{
    explosion_timer.restart();
    event_timer.restart();
    reload_clock.restart();
}

//--------------------
// Funkcje główne
//--------------------

void Game::run()
{
    while(window->isOpen()){
        update();
        draw();
    }
}

void Game::update()
{
    sf::Event ev;
    while(window->pollEvent(ev))
    {
        if(ev.Event::type == sf::Event::Closed)
        {
            window->close();
        }
        if(ev.type == sf::Event::KeyPressed){
            if(ev.key.code == sf::Keyboard::R){
                if(spaceship->is_reloading() == false){
                    reload_clock.restart();
                    spaceship->reload();
                    sounds->play_reloading_sound();
                }
            }
        }
    }
    if(!endgame)
    {
        spaceship->update(reload_clock);
        update_asteroids();
        update_bullets();
        update_backgroung();
        update_bullet_asteroid_collisions();
        update_spaceship_asteroid_collisions();
        update_spaceship_hp_collisions();
        update_explosions();
        update_explosions_animation();
        update_events();
    }
}

void Game::draw()
{
    window->clear();

    window->draw(background);

    for(auto *i : asteroids){
        i->draw(window);
    }
    for(auto *i : bullets){
        i->draw(window);
    }
    for(auto *i : explosions){
        i->draw(window);
    }
    draw_spaceship();
    draw_events();

    //if(circleexist)window->draw(*circle);

    if(endgame) gamelost();

    window->display();
}

void Game::gamelost()
{
    text[0].setFont(font);
    text[0].setFillColor(sf::Color::Red);
    text[0].setString("You lost!");
    text[0].setScale(3.0, 3.0);
    text[0].setPosition(
                window->getSize().x / 2 - text[0].getGlobalBounds().width / 2,
                window->getSize().y / 4);
    window->draw(text[0]);

    text[1].setFont(font);
    text[1].setFillColor(sf::Color::White);
    text[1].setString("Click here to play again");
    text[1].setScale(2.0, 2.0);
    text[1].setPosition(
                window->getSize().x / 2 - text[1].getGlobalBounds().width / 2,
                window->getSize().y / 2 );
    window->draw(text[1]);

    text[2].setFont(font);
    text[2].setFillColor(sf::Color::White);
    text[2].setString("Click here to end game");
    text[2].setScale(2.0, 2.0);
    text[2].setPosition(
                window->getSize().x / 2 - text[1].getGlobalBounds().width / 2,
                window->getSize().y / 1.5 );
    window->draw(text[2]);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        sf::Vector2f MousePos = window->mapPixelToCoords(mouse_pos);

        if(text[1].getGlobalBounds().contains(MousePos)){
            window->close();
            Game game;
        }
        if(text[2].getGlobalBounds().contains(MousePos)){
            window->close();
        }
    }
}

//--------------------
// Funkcje rysujące
//--------------------

void Game::draw_spaceship()
{
    spaceship->draw(*window);
}

void Game::draw_events()
{
    hp_event->drawhp(*window);
}

//--------------------
// Obsługa asteroid
//--------------------

void Game::create_asteroids()
{
    asteroid["ASTEROID1"] = new sf::Texture;
    asteroid["ASTEROID2"] = new sf::Texture;
    asteroid["ASTEROID3"] = new sf::Texture;
    asteroid["ASTEROID4"] = new sf::Texture;
    if(!asteroid["ASTEROID1"]->loadFromFile("Graphics/asteroid1.png")){
        std::cout << "Asteroid1 texture loading error!";
    }
    if(!asteroid["ASTEROID2"]->loadFromFile("Graphics/asteroid2.png")){
        std::cout << "Asteroid2 texture loading error!";
    }
    if(!asteroid["ASTEROID3"]->loadFromFile("Graphics/asteroid3.png")){
        std::cout << "Asteroid3 texture loading error!";
    }
    if(!asteroid["ASTEROID4"]->loadFromFile("Graphics/asteroid4.png")){
        std::cout << "Asteroid4 texture loading error!";
    }
}

void Game::update_asteroids()
{
    if(spaceship->asteroid_canspawn())
    {
        asteroids.push_back(new Asteroid(asteroid[spaceship->rand_asteroid()], 2.0));
    }
    unsigned counter = 0;
    for(auto *i : asteroids){
        i->update();
        if(i->get_asteroid_bounds().top >= 800){
            delete asteroids.at(counter);
            asteroids.erase(asteroids.begin() + counter);
            --counter;
        }
        ++counter;
    }
}

//--------------------
// Obsługa pocisków
//--------------------

void Game::create_bullets()
{
    bullet["BULLET"] = new sf::Texture;
    if(!bullet["BULLET"]->loadFromFile("Graphics/bullet.png")){
        std::cout << "Bullet texture loading error!";
    }
}

void Game::update_bullets()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spaceship->can_shoot() && spaceship->has_ammo() && !spaceship->is_reloading())
    {
        bullets.push_back(new Bullet(bullet["BULLET"], spaceship->get_position_for_bullets(), 0.0, -1.0, 5.0));
        spaceship->decrease_ammo();
    }
    unsigned counter = 0;
    for(auto *i : bullets){
        i->update();
        if (i->get_bullet_bounds().top + i->get_bullet_bounds().height <= 0.0){
            delete bullets.at(counter);
            bullets.erase(bullets.begin() + counter);
            --counter;
        }
        ++counter;
    }
}

//--------------------
// Interfejs
//--------------------

void Game::create_font()
{
    if(!font.loadFromFile("Fonts/my_font.ttf")){
        std::cout << "Font loading error!" << "\n";
    }
}

void Game::create_background()
{
    background_texture.loadFromFile("Graphics/Tlo.png");
    background.setTexture(background_texture);
    background.setScale(1.0, 1.0);
    current_backgraound = sf::IntRect(0, 850, 1000, 800);
    background.setTextureRect(current_backgraound);
}

void Game::update_backgroung()
{
    current_backgraound.top -= 1.0;
    background.setTextureRect(current_backgraound);
    if(current_backgraound.top < 0){
        current_backgraound.top = 850;
    }
}

//--------------------
// Obsługa kolizji
//--------------------

void Game::update_bullet_asteroid_collisions()
{
    unsigned bulletcounter = 0;
    for(auto *bullet : bullets)
    {
        unsigned asteroidcounter = 0;
        for(auto *asteroid : asteroids)
        {
            if(bullet->get_bullet_bounds().intersects(asteroid->get_asteroid_bounds()))
            {
                explosionpos = asteroid->explosion_position();
                explosion_bool = true;
                spaceship->points += 1;
                sounds->play_explosion_sound();

                delete bullets.at(bulletcounter);
                bullets.erase(bullets.begin() + bulletcounter);
                delete asteroids.at(asteroidcounter);
                asteroids.erase(asteroids.begin() + asteroidcounter);

                --bulletcounter;
                --asteroidcounter;
            }
            ++asteroidcounter;
        }
        ++bulletcounter;
    }
}

void Game::update_spaceship_asteroid_collisions()
{
    unsigned asteroidcounter = 0;
    for(auto *asteroid : asteroids)
    {
        if(asteroid->get_asteroid_bounds().intersects(spaceship->get_ship_bounds()))
        {
            explosionpos = asteroid->explosion_position();
            explosion_bool = true;
            spaceship->HP--;
            spaceship->HPchanged = true;
            sounds->play_losing_hp_sound();

            if(spaceship->HP == 0)
            {
                endgame = true;
                spaceship->update(reload_clock);
                sounds->play_gameover_sound();
            }
            delete asteroids.at(asteroidcounter);
            asteroids.erase(asteroids.begin() + asteroidcounter);
        }
        ++asteroidcounter;
    }
}

void Game::update_spaceship_hp_collisions()
{
    if(spaceship->get_ship_bounds().intersects(hp_event->get_hp_bounds()))
    {
        hp_event->restarthp();
        sounds->play_get_hp_sound();
        if(spaceship->HP < 10)
        {
            spaceship->HP++;
            spaceship->HPchanged = true;
        }
    }
}

//--------------------
// Obsługa eksplozji
//--------------------

void Game::create_explosions()
{
    explosion["EXPLOSION"] = new sf::Texture;
    if(!explosion["EXPLOSION"]->loadFromFile("Graphics/explosion.png")){
        std::cout << "Explosion texture loading error!";
    }
}

void Game::update_explosions()
{
    if(explosion_bool == true)
    {
        explosion_bool = false;
        explosions.push_back(new Explosion(explosion["EXPLOSION"], explosionpos));
    }
}

void Game::update_explosions_animation()
{
    if(explosion_timer.getElapsedTime().asSeconds() >= 0.05){
        explosion_timer.restart();
        for(auto *i : explosions){
            if(i->update()){
                delete explosions.at(0);
                explosions.erase(explosions.begin());
            }
        }
    }
}

//--------------------
// Obsługa eventów
//--------------------

void Game::update_events()
{
    sf::Time elapsed = event_timer.restart();
    hp_event->update(elapsed);
}

void Game::create_events()
{
    hp_event = new Game_event(true);
}



