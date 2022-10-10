#ifndef SRC_GAME_OBJECTS_SPACESHIP_ENEMY_HPP
#define SRC_GAME_OBJECTS_SPACESHIP_ENEMY_HPP

#include "./Spaceship.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Enemy : public Spaceship
{
  private:
    float _health;

  public:
    Enemy(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, float health, float size,
          float x_scale, float y_scale)
        : Spaceship(window, max_speed, max_acceleration, drag, size, x_scale, y_scale), _health(health){};

    float getHealth() const;

    /**
     * @brief Remove health from the enemy
     *
     * @param health_to_remove How much health to remove from the enemy
     * @returns If the enemy is alive (true) or not (false)
     */
    bool removeHealth(float health_to_remove);

    void update(float delta_time) override;
};

#endif // SRC_GAME_OBJECTS_SPACESHIP_ENEMY_HPP
