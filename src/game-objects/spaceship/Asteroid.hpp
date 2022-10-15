#ifndef SRC_GAME_OBJECTS_SPACESHIP_ASTEROID_HPP
#define SRC_GAME_OBJECTS_SPACESHIP_ASTEROID_HPP
#include "./Spaceship.hpp"
#include <SFML/Graphics/ConvexShape.hpp>

class Asteroid : public Spaceship
{
    private:
        // This is for later when we have collision detection, set to true when collides w/ player or bullet
        bool _isDestroyed;

    public:
        Asteroid(sf::RenderWindow &window, float max_speed, Vector2f scale, bool is_destroyed);
        // static Vector2f generateAsteroids();
        bool getIsDestroyed() const;
        void setIsDestroyed(bool destroyed);
        void update(float delta_time) override;
};

#endif // SRC_GAME_OBJECTS_SPACESHIP_ASTEROID_HPP