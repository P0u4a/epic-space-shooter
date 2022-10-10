#include "./Spaceship.hpp"
#include "util/Vector.hpp"
#include <algorithm>

Spaceship::Spaceship(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, float sprite_size)
    : GameObject(window, drag), max_speed(max_speed), max_acceleration(max_acceleration), sprite(sprite_size, 3)
{
    this->sprite.setFillColor(sf::Color::Green);
    this->sprite.setPosition(300, 300);
    // Set transform origin to centre of spaceship for rotation etc.
    float x_point_sum = 0;
    float y_point_sum = 0;
    for (int i = 0; i < 3; i++)
    {
        x_point_sum += this->sprite.getPoint(i).x;
        y_point_sum += this->sprite.getPoint(i).y;
    }
    this->sprite.setOrigin(x_point_sum / 3, y_point_sum / 3);
};

void Spaceship::setVelocity(const Vector2f &new_velocity)
{
    this->velocity.setWithCappedMagnitude(new_velocity, this->max_speed);
}

void Spaceship::setAcceleration(const Vector2f &new_acceleration)
{
    this->acceleration.setWithCappedMagnitude(new_acceleration, this->max_acceleration);
}
