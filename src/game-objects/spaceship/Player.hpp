#ifndef SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
#define SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP

#include "./Spaceship.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Player : public Spaceship
{
  private:
    const float kRotateSpeed = 400;
    int _lives;

  public:
    Player(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, int lives, Vector2f scale)
        : Spaceship(window, max_speed, max_acceleration, drag, scale,
                    {static_cast<float>(window.getSize().x / 2.0), static_cast<float>(window.getSize().y / 2.0)},
                    "player-sprite.png"),
          _lives(lives){};

    int getLives() const;

    /**
     * @brief Removes lives from the player
     *
     * @param lives_to_remove Number of lives to remove
     * @returns If the player is alive (true) or not (false)
     */
    bool removeLives(int lives_to_remove);

    void update(float delta_time) override;
};

#endif // SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
