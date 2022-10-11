#ifndef SRC_GAME_OBJECTS_ABSTRACT_GAMEOBJECT_HPP
#define SRC_GAME_OBJECTS_ABSTRACT_GAMEOBJECT_HPP

#include "interfaces/Updatable.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject : public Updatable
{
  protected:
    sf::RenderWindow &window;
    Vector2f velocity;
    Vector2f acceleration;
    float drag;

  public:
    explicit GameObject(sf::RenderWindow &window, float drag)
        : window(window), velocity({0, 0}), acceleration({0, 0}), drag(drag){};

    [[nodiscard]] virtual Vector2f getVelocity() const;
    virtual void setVelocity(const Vector2f &new_velocity) = 0;
    [[nodiscard]] virtual Vector2f getAcceleration() const;
    virtual void setAcceleration(const Vector2f &new_acceleration) = 0;
};

#endif // SRC_GAME_OBJECTS_ABSTRACT_GAMEOBJECT_HPP
