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
    auto move_by = this->velocity * delta_time;
    this->sprite.move(move_by);
    this->hitbox.move(move_by);
    // TODO actually complete the update
}

Asteroid::Asteroid(sf::RenderWindow &window, float drag, Vector2f scale, const std::string &sprite_file)
    : GameObject(window, drag)
{
    float speed = 10;
    double angle = rand() % 2 * M_PI;
    velocity.set({speed * cos(angle), speed * sin(angle)});
    acceleration.set({0, 0});

    int[window_w, window_h] = static_cast<sf::Vector2f>(window.getSize());

    position_x = rand() % window_w;
    position_y = rand() % window_h;
    Vector2f init_pos = {position_x, position_y};

    // Load texture and set as sprite texture
    if (!this->texture.loadFromFile(FileSystem::getExecutablePath() + "assets/" + sprite_file))
        // Error while loading texture - exit program
        exit(1); // NOLINT(concurrency-mt-unsafe)
    this->sprite.setTexture(this->texture);
    // TODO remove debug
    this->hitbox.setFillColor(sf::Color::Green);
    // Set initial sprite position
    this->sprite.setPosition(init_pos);
    this->hitbox.setPosition(init_pos);
    // Apply custom x and y scaling to sprite
    this->sprite.setScale(scale);
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
    // Set sprite origin to centroid of texture
    this->sprite.setOrigin(static_cast<sf::Vector2f>(this->texture.getSize()) / 2.0F);
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
