#include "./Spaceship.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

Spaceship::Spaceship(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, Vector2f scale,
                     Vector2f init_pos, const std::string &sprite_file)
    : GameObject(window, drag), max_speed(max_speed), max_acceleration(max_acceleration), hitbox(1, 3)
{
    // Load texture and set as sprite texture
    if (!this->texture.loadFromFile("assets/" + sprite_file))
        // Error while loading texture - exit program
        exit(1); // NOLINT(concurrency-mt-unsafe)
    this->setTexture(this->texture);
    // TODO remove debug
    this->hitbox.setFillColor(sf::Color::Green);
    // Set initial sprite position
    sf::Sprite::setPosition(init_pos);
    this->hitbox.setPosition(init_pos);
    // Apply custom x and y scaling to sprite
    this->setScale(scale);
    this->hitbox.setScale(scale * 10.0F);
    // Set hitbox transform origin to centre of spaceship for rotation etc.
    float x_vert_sum = 0;
    float y_vert_sum = 0;
    for (int i = 0; i < 3; i++)
    {
        x_vert_sum += this->hitbox.getPoint(i).x;
        y_vert_sum += this->hitbox.getPoint(i).y;
    }
    // Triangle centroid is the average x / y coordinates of the vertices
    this->hitbox.setOrigin(x_vert_sum / 3, y_vert_sum / 3);
    this->setOrigin(static_cast<sf::Vector2f>(this->texture.getSize()) / 2.0F);
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
    this->setVelocity(this->velocity + (this->acceleration * delta_time));
    // Change position based on current velocity
    auto move_by = this->velocity * delta_time;
    this->move(move_by);
    this->hitbox.move(move_by);
}

void Spaceship::rotate(float angle)
{
    // Apply rotation to hitbox
    this->hitbox.rotate(angle);
    // Apply rotation to self and texture
    sf::Sprite::rotate(angle);
}

void Spaceship::setPosition(float x, float y)
{
    // Apply position to hitbox
    this->hitbox.setPosition(x, y);
    // Apply rotation to self and texture
    sf::Sprite::setPosition(x, y);
}
