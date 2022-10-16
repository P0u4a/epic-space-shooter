#ifndef SRC_GAME_OBJECTS_PROJECTILE_HPP
#define SRC_GAME_OBJECTS_PROJECTILE_HPP
#include "game-objects/spaceship/Player.hpp"
#include "util/FileSystem.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <iostream>
#include <string>


class Projectile: public GameObject
{
    private:
        sf::Sprite _sprite;
        Player _player;
    public:
        Projectile(sf::RenderWindow &_window, float drag, const sf::Vector2f &position, float rotation, Player &player);
        Projectile(const Projectile &projectile) = default;
        void update(float delta_time);
        Vector2f getVelocity();
        Vector2f getAcceleration();
        void setVelocity(const Vector2f &new_velocity);
        void setAcceleration(const Vector2f &new_acceleration);
        //static Spaceship *_player;
        inline static sf::Texture _texture;
        bool render;
        bool in_player();
};


#endif // SRC_GAME_OBJECTS_PROJECTILE_HPP