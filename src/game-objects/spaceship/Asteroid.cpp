#include "Asteroid.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

Asteroid::Asteroid(sf::RenderWindow &window, float max_speed, Vector2f scale, bool is_destroyed)
    : Spaceship(window, max_speed, max_acceleration, drag, scale, {(rand() % 1700) + 1, (rand() % 1000) + 1}, "asteroid.png"),
      _isDestroyed(is_destroyed)
{
    srand(time(nullptr));
    this->setVelocity(Vector2f((rand() % 200) + 150, (rand() % 200) + 150));
}

// Vector2f Asteroid::generateAsteroids()
// {

//     srand(time(nullptr));
//     int side = (rand() % 4) + 1;

//     switch (side)
//     {
//     case 1:
//         return {(rand() % 1700) + 1, 0};
//         break;
    
//     case 2:
//         return {1700.F, (rand() % 700) + 1};
//         break;
//     case 3:
//         return {(rand() % 1700) + 1, 700};
//         break;
//     case 4:
//         return {(rand() % 1700) + 1, (rand() % 700) + 1};
//         break;

//     default:
//         return {0,0};
//         break;
//     }
// }


bool Asteroid::getIsDestroyed() const
{
    return this->_isDestroyed;
}

void Asteroid::setIsDestroyed(bool destroyed)
{
    this->_isDestroyed = destroyed;
}

void Asteroid::update(float delta_time)
{
    // Give the asteroid constant speed in a set direction
    Spaceship::update(delta_time);

    // Wrap asteroid around to opposite edge of screen if exited on one edge
    auto [window_w, window_h] = static_cast<sf::Vector2f>(window.getSize());
    auto [asteroid_x, asteroid_y] = this->hitbox.getPosition();
    auto bounding_rect = this->hitbox.getGlobalBounds();
    auto asteroid_w = bounding_rect.width;
    auto asteroid_h = bounding_rect.height;
    // Origin set at centre, so use half asteroid_w / asteroid_h in calculations
    // Add some offset to push asteroid further into screen to prevent being stuck outside in corners
    const float push_offset = 50;
    // Exited right edge
    if (bounding_rect.left > window_w)
        this->setPosition(push_offset - (asteroid_w / 2), asteroid_y);
    // Exited left edge
    else if (bounding_rect.left + asteroid_w < 0)
        this->setPosition(window_w + (asteroid_w / 2) - push_offset, asteroid_y);
    // Exited bottom edge - y-axis points down
    if (bounding_rect.top > window_h)
        this->setPosition(asteroid_x, push_offset - (asteroid_w / 2));
    // Exited top edge - y-axis points down
    else if (bounding_rect.top + asteroid_h < 0)
        this->setPosition(asteroid_x, window_h + (asteroid_h / 2) - push_offset);

    window.draw(this->sprite);
}