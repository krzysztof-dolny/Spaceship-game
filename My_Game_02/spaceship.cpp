#include "spaceship.h"

//--------------------
// Konstruktor i destruktor
//--------------------

Spaceship::Spaceship()
{
    load_texture();
    load_font();
    animation_timer.restart();
    asteroid_clock.restart();
}

Spaceship::~Spaceship()
{

}

//--------------------
// Funkcje główne
//--------------------

void Spaceship::update(sf::Clock& reload_clock)
{
    spaceship_movement();
    update_spaceship_animation();
    can_shoot();
    update_bar();
    update_points();
    update_ammo();
    update_reload(reload_clock);
}

void Spaceship::draw(sf::RenderTarget& window)
{
    window.draw(HP_barmax);
    window.draw(HP_bar);
    window.draw(text);
    window.draw(ammo_text);
    window.draw(spaceship_sprite);
}

//--------------------
// Obsługa statku kosmicznego
//--------------------

void Spaceship::load_texture()
{
    if(!spaceship_texture.loadFromFile("Graphics/SpaceShip.png")){
        std::cout << "Spaceship texture loading error!";
    }
     spaceship_sprite.setTexture(spaceship_texture);
     spaceship_sprite.scale(1.0, 1.0);

     current_sprite = sf::IntRect(190.0, 0.0, 95.0, 150.0);
     spaceship_sprite.setTextureRect(current_sprite);
     spaceship_sprite.setPosition(450.0, 500.0);
}

void Spaceship::spaceship_movement()
{
    moveing_left = false;
    moveing_right = false;

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
            (spaceship_sprite.getGlobalBounds().left + spaceship_sprite.getGlobalBounds().width <= 1000))
    {
        spaceship_sprite.move(2.0, 0.0);
        moveing_right = true;
    }
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
            (spaceship_sprite.getGlobalBounds().left >= 0))
    {
        spaceship_sprite.move(-2.0, 0.0);
        moveing_left = true;
    }
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) &&
            (spaceship_sprite.getGlobalBounds().top >= 0))
    {
        spaceship_sprite.move(0.0, -2.0);
    }
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) &&
            (spaceship_sprite.getGlobalBounds().top + spaceship_sprite.getGlobalBounds().height <= 800))
    {
        spaceship_sprite.move(0.0, 2.0);
    }
}

void Spaceship::update_spaceship_animation()
{
    if(animation_timer.getElapsedTime().asSeconds() >= 0.075)
    {
        if((moveing_left == false && moveing_right == false) && (current_sprite.left == 95 || current_sprite.left == 285)){
            current_sprite.left = 190.0;
            animation_timer.restart();
        }
        else if((moveing_left == false && moveing_right == false) && current_sprite.left == 0){
            current_sprite.left += 95;
            animation_timer.restart();
        }
        else if((moveing_left == false && moveing_right == false) && current_sprite.left == 380){
            current_sprite.left -=95;
            animation_timer.restart();
        }

        if(moveing_left == true && moveing_right == false)
        {
            if(current_sprite.left >= 95)
            {
                current_sprite.left -= 95;
                animation_timer.restart();
            }
        }
        if(moveing_left == false && moveing_right == true)
        {
            if(current_sprite.left < 380)
            {
                current_sprite.left += 95;
                animation_timer.restart();
            }
        }
    }
    spaceship_sprite.setTextureRect(current_sprite);
}

sf::FloatRect Spaceship::get_ship_bounds()
{
    return spaceship_sprite.getGlobalBounds();
}

//--------------------
// Obsługa asteroid
//--------------------

bool Spaceship::asteroid_canspawn()
{
    if(asteroid_clock.getElapsedTime().asSeconds() > 5.0 && asteroid_cooldownmax > 1.0){
        asteroid_cooldownmax -= 0.1;
        asteroid_clock.restart();
    }
    if(asteroid_cooldown < asteroid_cooldownmax){
        asteroid_cooldown += 0.1;
    }
    if(asteroid_cooldown >= asteroid_cooldownmax){
        asteroid_cooldown = 0.0;
        return true;
    }
    return false;
}

std::string Spaceship::rand_asteroid()
{
    int x = rand() % 4;
    if(x == 0){
        return "ASTEROID1";
    }
    else if(x == 1){
        return "ASTEROID2";
    }
    else if(x == 2){
        return "ASTEROID3";
    }
    else if(x == 3){
        return "ASTEROID4";
    }
    return "ASTEROID1";
}

//--------------------
// Obsługa strzałów
//--------------------

sf::Vector2f Spaceship::get_position_for_bullets()
{
    float x = spaceship_sprite.getPosition().x - spaceship_sprite.getGlobalBounds().width / 2 + 90.0;
    float y = spaceship_sprite.getPosition().y - 40.0;
    return {x, y};
}

bool Spaceship::can_shoot()
{
    if(attack_cooldown < attack_cooldownmax){
        attack_cooldown += 0.25;
    }
    if(attack_cooldown >= attack_cooldownmax){
        attack_cooldown = 0.0;
        return true;
    }
    return false;
}

void Spaceship::create_ammo()
{
    ammo_text.setFont(font);
    ammo_text.setFillColor(sf::Color::White);
    ammo_text.setScale(0.75, 0.75);
    ammo_text.setPosition(
                HP_barmax.getGlobalBounds().left,
                HP_barmax.getGlobalBounds().top - 100.0);
}

void Spaceship::update_ammo()
{
    std::stringstream ss;
    if(has_ammo()){
        ss << "Ammo: " << ammo;
        ammo_text.setString(ss.str());
    }
    if(!has_ammo()){
        ss << "Ammo: " << ammo << ", press \'R\' to reload!";
        ammo_text.setString(ss.str());
    }
}

void Spaceship::update_reload(sf::Clock& reload_clock)
{
    if(reloading == true){
        reloading_timer += reload_clock.getElapsedTime().asSeconds();
        reload_clock.restart();
        if(reloading_timer >= reloading_timer_max){
            reloading_timer = 0;
            ammo = 30;
            has_ammunition = true;
            reloading = false;
        }
    }
}

void Spaceship::reload()
{
    reloading = true;
}

bool Spaceship::has_ammo()
{
    return has_ammunition;
}

bool Spaceship::is_reloading()
{
    return reloading;
}

void Spaceship::decrease_ammo()
{
    ammo--;
    if(ammo == 0){
        has_ammunition = false;
    }
}

//--------------------
// Pasek życia
//--------------------

void Spaceship::create_bar(sf::RenderTarget& window)
{
    HP_bar.setSize(sf::Vector2f(300.0, 30.0));
    HP_bar.setFillColor(sf::Color::Red);
    HP_bar.setPosition(window.getSize().x - HP_bar.getGlobalBounds().width - 20, window.getSize().y - HP_bar.getGlobalBounds().height - 20);

    HP_barmax.setSize(sf::Vector2f(300.0, 30.0));
    HP_barmax.setFillColor(sf::Color(20, 20, 20, 200));
    HP_barmax.setPosition(window.getSize().x - HP_bar.getGlobalBounds().width - 20, window.getSize().y - HP_bar.getGlobalBounds().height - 20);
}

void Spaceship::update_bar()
{
    if(HPchanged)
    {
        HPchanged = false;
        HPbuffor = static_cast<float>(HP) / static_cast<float>(HPmax);
        HP_bar.setSize(sf::Vector2f(HP_barmax.getSize().x * HPbuffor, HP_bar.getSize().y));
    }
}

//--------------------
// Pasek życia
//--------------------

void Spaceship::create_points()
{
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setScale(0.75, 0.75);
    text.setPosition(
                HP_barmax.getGlobalBounds().left,
                HP_barmax.getGlobalBounds().top - 50.0);
}

void Spaceship::update_points()
{
    std::stringstream ss;
    ss << "Asteroids destroyed: " << points;
    text.setString(ss.str());
}

//--------------------
// Ładowanie czionki
//--------------------

void Spaceship::load_font()
{
    if(!font.loadFromFile("Fonts/my_font.ttf")){
        std::cout << "Font loading error!" << "\n";
    }
}

