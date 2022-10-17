#ifndef SRC_GAME_OBJECTS_PROJECTILE_HPP
#define SRC_GAME_OBJECTS_PROJECTILE_HPP

#include "game-objects/spaceship/Player.hpp"
#include "util/FileSystem.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <iostream>
#include <string>

class Projectile : public GameObject
{
  private:
    const float kProjectileSpeed = 1111;
    sf::Sprite _sprite;
    Player _player;

  public:
    Projectile(sf::RenderWindow &window, float drag, const sf::Vector2f &position, float rotation, Player &player);

    void update(float delta_time) override;

    void setVelocity(const Vector2f &new_velocity) override;
    void setAcceleration(const Vector2f &new_acceleration) override;

    bool render;
    bool inPlayer();

    // TODO change to pointer
    inline static sf::Texture texture;
};

#endif // SRC_GAME_OBJECTS_PROJECTILE_HPP
