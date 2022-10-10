#include "./Spaceship.hpp"
#include "util/Vector.hpp"
#include <algorithm>
#include <iostream>

Spaceship::Spaceship(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, float sprite_size)
    : GameObject(window, drag), max_speed(max_speed), max_acceleration(max_acceleration), sprite(sprite_size, 3)
{
    this->sprite.setFillColor(sf::Color::Green);
    this->sprite.setPosition(300, 300);
    // Set transform origin to centre of spaceship for rotation etc.
    float x_vert_sum = 0;
    float y_vert_sum = 0;
    for (int i = 0; i < 3; i++)
    {
        x_vert_sum += this->sprite.getPoint(i).x;
        y_vert_sum += this->sprite.getPoint(i).y;
    }
    // Triangle centroid is the average x / y coordinates of the vertices
    this->sprite.setOrigin(x_vert_sum / 3, y_vert_sum / 3);
};

void Spaceship::setVelocity(const Vector2f &new_velocity)
{
    this->velocity.setWithCappedMagnitude(new_velocity, this->max_speed);
}

void Spaceship::setAcceleration(const Vector2f &new_acceleration)
{
    this->acceleration.setWithCappedMagnitude(new_acceleration, this->max_acceleration);
}

void Spaceship::update(float delta_time)
{
    // Change velocity based on current acceleration
    this->velocity += this->acceleration * delta_time;
    // Change position based on current velocity
    auto move_by = this->velocity * delta_time;
    this->move(move_by);
    this->sprite.move(move_by);
}
