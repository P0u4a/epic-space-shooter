#ifndef SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP
#define SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP

#include "game-objects/abstract/GameObject.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class Spaceship : public GameObject
{
  protected:
    const float kRotateSpeed = 400;
    float max_speed;
    float max_acceleration;
    sf::Sprite sprite;
    sf::Texture texture;

  public:
    Spaceship(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, Vector2f scale,
              Vector2f init_pos, const std::string &sprite_file);

    void setVelocity(const Vector2f &new_velocity) override;
    void setAcceleration(const Vector2f &new_acceleration) override;
    void update(float delta_time) override;
    virtual void rotate(float angle);
    virtual void setPosition(float x, float y);
    void setSprite(sf::Color color);
    sf::CircleShape hitbox;
};

#endif // SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP
