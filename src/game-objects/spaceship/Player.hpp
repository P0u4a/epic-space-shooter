#ifndef SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
#define SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP

#include "./Spaceship.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Player : public Spaceship
{
  private:
    int _lives;

  public:
    Player(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, int lives, float size,
           float x_scale, float y_scale)
        : Spaceship(window, max_speed, max_acceleration, drag, size, x_scale, y_scale), _lives(lives){};

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
