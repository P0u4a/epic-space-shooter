#ifndef SRC_GAME_OBJECTS_SPACESHIP_ENEMY_HPP
#define SRC_GAME_OBJECTS_SPACESHIP_ENEMY_HPP

#include "./Spaceship.hpp"

class Enemy : public Spaceship {
  private:
    float _health;

  public:
    Enemy() = delete;
    Enemy(float max_speed, float max_acceleration, float drag, float health) :
        Spaceship(max_speed, max_acceleration, drag), _health(health){};

    float getHealth() const;

    /**
     * @brief Remove health from the enemy
     *
     * @param health_to_remove How much health to remove from the enemy
     * @returns If the enemy is alive (true) or not (false)
     */
    bool removeHealth(float health_to_remove);
};

#endif // SRC_GAME_OBJECTS_SPACESHIP_ENEMY_HPP
