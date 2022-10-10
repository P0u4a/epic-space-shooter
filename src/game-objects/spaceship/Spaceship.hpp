#ifndef SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP
#define SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP

#include "game-objects/abstract/GameObject.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Spaceship : public GameObject
{
  protected:
    float max_speed;
    float max_acceleration;
    sf::CircleShape sprite;

  public:
    Spaceship(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, float sprite_size);

    void setVelocity(const Vector2f &new_velocity) override;
    void setAcceleration(const Vector2f &new_acceleration) override;
    void update(float delta_time) override;
};

#endif // SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP
