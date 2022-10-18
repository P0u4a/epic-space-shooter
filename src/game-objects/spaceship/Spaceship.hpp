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
    sf::Texture *texture = nullptr;
    sf::CircleShape hitbox;

  public:
    Spaceship(sf::RenderWindow &window, float max_speed, float max_acceleration, float drag, Vector2f scale,
              Vector2f init_pos, const std::string &sprite_file);

    void setVelocity(const Vector2f &new_velocity) override;
    void setAcceleration(const Vector2f &new_acceleration) override;

    /**
     * @brief Rotate Spacehsip Spite and Hitbox
     *
     * @param angle The angle in which the Spaceship is rotated
     */
    virtual void rotate(float angle);

    /**
     * @brief Set the Position Spaceship
     *
     * @param x x position of spaceship
     * @param y y position of spaceship
     */
    virtual void setPosition(float x, float y);

    /**
     * @brief Set the color of the spaceship
     *
     * @param color sf:Color for the sprite of the spaceship
     */
    void setSprite(sf::Color color);

    /**
     * @brief Move spaceship sprite and hitbox
     *
     * @param delta_time Time since last frame
     */
    void update(float delta_time) override;

    /**
     * @brief Get the Hitbox of the spaceship object
     *
     * @return sf::CircleShape&: adress of spaceship hitbox
     */
    sf::CircleShape &getHitbox();
};

#endif // SRC_GAME_OBJECTS_ABSTRACT_SPACESHIP_HPP
