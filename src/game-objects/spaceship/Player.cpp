#include "Player.hpp"

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
void update()
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
}
