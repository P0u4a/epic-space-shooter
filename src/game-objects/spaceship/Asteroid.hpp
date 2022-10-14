#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "./Spaceship.hpp"
#include "game-objects/abstract/GameObject.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class Asteroid : public GameObject
{
  public:
    float position_x;
    float position_y;
    sf::CircleShape hitbox;
    sf::Sprite sprite;
    sf::Texture texture;

    Asteroid(sf::RenderWindow &window, float drag, Vector2f scale, const std::string &sprite_file);
    void setVelocity(const Vector2f &new_velocity) override;
    void setAcceleration(const Vector2f &new_acceleration) override;
    void setPosition(float x, float y);
    void update(float delta_time) override;
};

#endif // __ASTEROID_H__
