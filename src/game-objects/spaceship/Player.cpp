#include "Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

int Player::getLives() const
{
    return this->_lives;
}

bool Player::removeLives(int lives_to_remove)
{
    this->_lives -= lives_to_remove;
    return this->_lives > 0;
}

void Player::update()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // This should only rotate the sprite anticlockwise
        this->sprite.rotate(-0.1);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // This should only rotate the sprite clockwise
        this->sprite.rotate(0.1);
    }

    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    // {
    //     // This should only accelerate the sprite towards the direction its pointing
    // }

    // Draw player to screen
    window.draw(this->sprite);
}
