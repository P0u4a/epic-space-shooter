#ifndef SRC_INTERFACES_UPDATABLE_HPP
#define SRC_INTERFACES_UPDATABLE_HPP

#include <SFML/Graphics/Sprite.hpp>

class Updatable : public sf::Sprite
{
  public:
    virtual void update(float delta_time) = 0;
};

#endif // SRC_INTERFACES_UPDATABLE_HPP
