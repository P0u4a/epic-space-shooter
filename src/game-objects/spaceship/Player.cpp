#include "Player.hpp"
#include "game-objects/spaceship/Spaceship.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>

int Player::getLives() const
{
    return this->_lives;
}

bool Player::removeLives(int lives_to_remove)
{
    this->_lives -= lives_to_remove;
    return this->_lives > 0;
}

void Player::update(float delta_time)
{
    // Rotate player anticlockwise
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->sprite.rotate(-0.1);
    // Rotate player clockwise
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->sprite.rotate(0.1);

    // Reset acceleration for this tick
    this->setAcceleration({0, 0});
    // Add forward acceleration in direction being faced
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // Get rotation in radians
        auto theta = static_cast<float>((this->sprite.getRotation() * M_PI / 180) - M_PI_2);
        this->setAcceleration(Vector2f(std::cos(theta), std::sin(theta)) * 1000);
    }

    // Draw player to screen
    window.draw(this->sprite);
    // TODO remove debug
    // Draw direction line to screen
    auto a = sf::RectangleShape(Vector2f(30, 5));
    a.setFillColor(sf::Color::Blue);
    a.setOrigin(15, 2.5);
    a.setPosition(this->sprite.getPosition());
    a.setRotation(this->sprite.getRotation() - 90);
    window.draw(a);

    // Run common spaceship update tick
    Spaceship::update(delta_time);

    // No acceleration applied - apply drag
    if (this->acceleration.x == 0 && this->acceleration.y == 0 && this->velocity.magnitude() > 0)
    {
        // Draw vector in the same direction as velocity proportional to the current speed
        auto drag_vec = (this->velocity.norm() * (this->velocity.magnitude() / drag)).abs();
        // All components of the velocity vector must be positive after subtracting drag
        if (this->velocity.x < 0)
            drag_vec.x = -drag_vec.x;
        if (this->velocity.y < 0)
            drag_vec.y = -drag_vec.y;
        // Apply the drag vector as deceleration to the velocity
        this->velocity -= drag_vec * delta_time;
    }
}
