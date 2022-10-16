#ifndef SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
#define SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP

#include "./Spaceship.hpp"
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
    sf::Sprite _flames_sprite;
    int _curr_flames_tex_i = 0;
    int _lives;

    struct MoveKeys
    {
        // This works without using the enum keyword at the beginning i guess
        sf::Keyboard::Key move_up;
        sf::Keyboard::Key rotate_left;
        sf::Keyboard::Key rotate_right;

    } _keys;

  public:
    Player(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, int lives, Vector2f scale,
           MoveKeys keys);

    int getLives() const;

    /**
     * @brief Removes lives from the player
     *
     * @param lives_to_remove Number of lives to remove
     * @returns If the player is alive (true) or not (false)
     */
    bool removeLives(int lives_to_remove);

    void rotate(float angle) override;
    void setPosition(float x, float y) override;

    void accelerateForwards();

    void update(float delta_time) override;
};

#endif // SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
