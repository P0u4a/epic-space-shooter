#ifndef SRC_GAME_OBJECTS_ABSTRACT_GAMEOBJECT_HPP
#define SRC_GAME_OBJECTS_ABSTRACT_GAMEOBJECT_HPP

#include <SFML/System/Vector2.hpp>
#include "../../interfaces/Updatable.hpp"

class GameObject : public Updatable {
  protected:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float drag;

  public:
    GameObject() = delete;
    GameObject(sf::Vector2f velocity, sf::Vector2f acceleration, float drag) :
        velocity(velocity), acceleration(acceleration), drag(drag){};
    virtual sf::Vector2f getVelocity() = 0;
    virtual void setVelocity(sf::Vector2f velocity) = 0;
    virtual sf::Vector2f getAcceleration() = 0;
    virtual void setAcceleration(sf::Vector2f acceleration) = 0;
};

#endif // SRC_GAME_OBJECTS_ABSTRACT_GAMEOBJECT_HPP
