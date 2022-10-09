#ifndef SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
#define SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP

#include "./Spaceship.hpp"
#include <SFML/Graphics.hpp>

class Player : public Spaceship
{
  private:
    int _lives;
    // I don't know if we want to draw the player like this or not
    // sf::CircleShape *_asset;

  public:
    Player() = delete;
    Player(float max_speed, float max_acceleration, float drag, int lives)
        : Spaceship(max_speed, max_acceleration, drag), _lives(lives){};

    int getLives() const;

    /**
     * @brief Removes lives from the player
     *
     * @param lives_to_remove Number of lives to remove
     * @returns If the player is alive (true) or not (false)
     */
    bool removeLives(int lives_to_remove);

    void update() override;
};

#endif // SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
