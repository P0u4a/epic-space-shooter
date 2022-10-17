#include "Player.hpp"
#include "controllers/App.hpp"
#include "game-objects/abstract/GameObject.hpp"
#include "game-objects/spaceship/Spaceship.hpp"
#include "util/AssetLoader.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <string>
#include <vector>

Player::Player(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, int lives, Vector2f scale,
               MoveKeys keys)
    : Spaceship(window, max_speed, max_acceleration, drag, scale, {0, 0}, "player-sprite.png"), _lives(lives),
      _time_since_fire(69.420), _keys({keys.move_up, keys.rotate_left, keys.rotate_right, keys.fire}), _game_over(window, 0.5, 0.3, "Game Over!"),_game_over_msg(MenuButton(window, 0.5, 0.5, "Press R to Return Home")), fired(false)
{
    this->_flames_textures.resize(4);
    // Load flames textures
    for (int i = 0; i < 4; i++)
        AssetLoader::loadTextureAsset(this->_flames_textures[i], "player-flames-sprite-" + std::to_string(i) + ".png");
    // Set initial flames sprite position and scaling
    this->_flames_sprite.setPosition(this->sprite.getPosition());
    this->_flames_sprite.setScale(scale);
    // Set flames sprite origin to spaceship centroid
    if (this->_flames_textures[0] != nullptr)
        this->_flames_sprite.setOrigin(static_cast<sf::Vector2f>(this->_flames_textures[0]->getSize()) / 2.0F);
    
    this->_explosion_textures.resize(5);

    for (int i = 0; i < 5; i++)
        AssetLoader::loadTextureAsset(this->_explosion_textures[i], "explosion" + std::to_string(i) + ".png");
    
    this->_explosion_sprite.setPosition(this->sprite.getPosition());
    this->_explosion_sprite.setScale(scale);
    if (this->_explosion_textures[0] != nullptr)
        this->_explosion_sprite.setOrigin(static_cast<sf::Vector2f>(this->_explosion_textures[0]->getSize()) / 2.0F);
}

int Player::getLives() const
{
    return this->_lives;
}

bool Player::removeLives(int lives_to_remove)
{
    this->_lives -= lives_to_remove;
    return this->_lives > 0;
}

void Player::rotate(float angle)
{
    // Run parent rotation logic
    Spaceship::rotate(angle);
    // Rotate flames sprite
    this->_flames_sprite.rotate(angle);
}

void Player::setPosition(float x, float y)
{
    // Run parent set position logic
    Spaceship::setPosition(x, y);
    // Set new flames sprite position
    this->_flames_sprite.setPosition(x, y);
}

void Player::accelerateForwards()
{
    // Get rotation in radians
    auto theta = static_cast<float>((this->hitbox.getRotation() * M_PI / 180) - M_PI_2);
    this->setAcceleration(Vector2f(std::cos(theta), std::sin(theta)) * max_acceleration);
    // Display flames sprite this frame
    const int flames_tex_index = std::floor(this->_curr_flames_tex_i / 2);
    if (this->_flames_textures[flames_tex_index] != nullptr)
        this->_flames_sprite.setTexture(*this->_flames_textures[flames_tex_index]);
    // Set new flames sprite texture index - use same texture for 2 frames
    this->_curr_flames_tex_i++;
    if (this->_curr_flames_tex_i >= static_cast<int>(this->_flames_textures.size()) * 2)
        this->_curr_flames_tex_i = 0;
}

void Player::update(float delta_time)
{
    if (this->_lives <=0 ) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            App::setIsInGame(false);
        }

        window.draw(_game_over_msg.getButton());
        window.draw(_game_over.getButton());
        return;
    }

    _time_since_fire += delta_time;
    // Rotate player anticlockwise
    if (sf::Keyboard::isKeyPressed(_keys.rotate_left))
        this->rotate(-kRotateSpeed * delta_time);
    // Rotate player clockwise
    else if (sf::Keyboard::isKeyPressed(_keys.rotate_right))
        this->rotate(kRotateSpeed * delta_time);

    // Reset acceleration for this tick
    this->setAcceleration({0, 0});
    // Add forward acceleration in direction being faced
    if (sf::Keyboard::isKeyPressed(_keys.move_up))
    {
        this->accelerateForwards();
    }

    // after spaceship moved to new position check for firing
    if (sf::Keyboard::isKeyPressed(_keys.fire) && this->_time_since_fire >= 1.0 / 6.0)
    {
        this->fired = true;
        this->_time_since_fire = 0;
    }

    // Run common spaceship update tick
    Spaceship::update(delta_time);

    // Update flames position
    this->_flames_sprite.move(this->velocity * delta_time);
    if (sf::Keyboard::isKeyPressed(_keys.move_up))
        this->window.draw(this->_flames_sprite);

    // No acceleration applied - apply drag
    if (this->acceleration.x == 0 && this->acceleration.y == 0 && this->velocity.magnitude() > 0)
    {
        // Draw vector in the same direction as velocity proportional to the current speed
        auto drag_vec = this->velocity.norm() * (this->velocity.magnitude() / drag);
        // Apply the drag vector as deceleration to the velocity
        this->velocity -= drag_vec * delta_time;
    }

    // Wrap player around to opposite edge of screen if exited on one edge
    auto [window_w, window_h] = static_cast<sf::Vector2f>(this->window.getSize());
    auto [player_x, player_y] = this->hitbox.getPosition();
    auto bounding_rect = this->hitbox.getGlobalBounds();
    auto player_w = bounding_rect.width;
    auto player_h = bounding_rect.height;
    // Origin set at centre, so use half player_w / player_h in calculations
    // Add some offset to push player further into screen to prevent being stuck outside in corners
    const float push_offset = 50;
    // Exited right edge
    if (bounding_rect.left > window_w)
        this->setPosition(push_offset - (player_w / 2), player_y);
    // Exited left edge
    else if (bounding_rect.left + player_w < 0)
        this->setPosition(window_w + (player_w / 2) - push_offset, player_y);
    // Exited bottom edge - y-axis points down
    if (bounding_rect.top > window_h)
        this->setPosition(player_x, push_offset - (player_w / 2));
    // Exited top edge - y-axis points down
    else if (bounding_rect.top + player_h < 0)
        this->setPosition(player_x, window_h + (player_h / 2) - push_offset);

    // Draw hitbox to screen
    // this->_window.draw(this->hitbox);
    // Draw player to screen
    this->window.draw(this->sprite);
}
