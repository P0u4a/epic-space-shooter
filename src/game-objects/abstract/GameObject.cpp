#include "./GameObject.hpp"
#include "util/Vector.hpp"

Vector2f GameObject::getVelocity() const
{
    return this->velocity;
}

Vector2f GameObject::getAcceleration() const
{
    return this->acceleration;
}

void GameObject::setWindow(sf::RenderWindow *window) {
    _window = window;
}
