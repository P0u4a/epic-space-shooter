#ifndef SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
#define SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP

#include "./Spaceship.hpp"
#include "ui/MenuButton.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

class Player : public Spaceship
{
  private:
    const float kRotateSpeed = 400;
    std::vector<sf::Texture *> _flames_textures;
    std::vector<sf::Texture *> _explosion_textures;
    sf::Sprite _flames_sprite;
    sf::Sprite _explosion_sprite;
    int _curr_flames_tex_i = 0;
    int _curr_explosion_tex_i = 0;
    int _lives;
    float _time_since_fire;
    MenuButton _game_over;
    MenuButton _game_over_msg;

    struct MoveKeys
    {
        // This works without using the enum keyword at the beginning i guess
        // Awesome !!
        sf::Keyboard::Key move_up;
        sf::Keyboard::Key rotate_left;
        sf::Keyboard::Key rotate_right;
        sf::Keyboard::Key fire;

    } _keys;

  public:
    Player(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, int lives, Vector2f scale,
           MoveKeys keys);

    int getLives() const;

    bool fired;

    /**
     * @brief Removes lives from the player
     *
     * @param lives_to_remove Number of lives to remove
     * @returns If the player is alive (true) or not (false)
     */
    bool removeLives(int lives_to_remove);

    /**
     * @brief Rotate Player sprite and hitbox
     *
     * @param angle The angle in which the player is rotated
     */
    void rotate(float angle) override;

    /**
     * @brief Set the Position of Player
     *
     * @param x x position of player
     * @param y y position of player
     */
    void setPosition(float x, float y) override;

    /**
     * @brief adjust acceleration based on player rotation
     *
     */
    void accelerateForwards();

    /**
     * @brief Update player; move player, check lives, draw necessary textures/sprites, fire bullets, adjust
     * accleration/velocity
     *
     * @param delta_time Time since last frame
     */
    void update(float delta_time) override;
};

#endif // SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
