#ifndef SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP
#define SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP

#include "game-objects/abstract/GameObject.hpp"
#include "util/Vector.hpp"

class Spaceship : public GameObject
{
  protected:
    float max_speed;
    float max_acceleration;

  public:
    Spaceship(float max_speed, float max_acceleration, float drag)
        : GameObject(drag), max_speed(max_speed), max_acceleration(max_acceleration){};

    void setVelocity(const Vector2f &new_velocity) override;
    void setAcceleration(const Vector2f &new_acceleration) override;
};

#endif // SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP
