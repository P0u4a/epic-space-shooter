#include "Asteroid.hpp"
#include "util/FileSystem.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <string>

void Asteroid::update(float delta_time)
{
}

Asteroid::Asteroid(sf::RenderWindow &window, float drag) : GameObject(window, drag)
{
    float speed = 10;
    double angle = rand() % 2 * M_PI;
    velocity.set({speed * cos(angle), speed * sin(angle)});
    acceleration.set({0, 0});

    int[window_w, window_h] = static_cast<sf::Vector2f>(window.getSize());

    position_x = rand() % window_w;
    position_y = rand() % window_h;
}

void Asteroid::setVelocity(const Vector2f &new_velocity)
{
    this->velocity.set(new_velocity);
}

void Asteroid::setAcceleration(const Vector2f &new_acceleration)
{
    this->acceleration.set(new_acceleration);
}

void Asteroid::setPosition(float x, float y)
{
    // Apply position to hitbox
    this->hitbox.setPosition(x, y);
    // Apply rotation to sprite
    this->sprite.setPosition(x, y);
}
