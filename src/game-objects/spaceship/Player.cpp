#include "Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Player::Player(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, int lives)
    : Spaceship(window, max_speed, max_acceleration, drag), _lives(lives), _triangle(80, 3)
{

    this->_triangle.setFillColor(sf::Color::Green);
    this->_triangle.setPosition(0, 0);
};

int Player::getLives() const
{
    return this->_lives;
}

bool Player::removeLives(int lives_to_remove)
{
    this->_lives -= lives_to_remove;
    return this->_lives > 0;
}

// Uncomment this stuff when we figure out player sprite
void Player::update()
{
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    // {
    //     // This should only rotate the sprite anticlockwise
    // }

    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    // {
    //     // This should only rotate the sprite clockwise
    // }

    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    // {
    //     // This should only accelerate the sprite towards the direction its pointing
    // }

    // Draw player to screen
    window.draw(this->_triangle);
}
