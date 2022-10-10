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
        auto theta = static_cast<float>(this->sprite.getRotation() * M_PI / 180);
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
    a.setRotation(this->sprite.getRotation());
    window.draw(a);

    // Run common spaceship update tick
    Spaceship::update(delta_time);
}
