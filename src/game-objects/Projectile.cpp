#include "./Projectile.hpp"
#include "cmath"

Projectile::Projectile(sf::RenderWindow &window, float drag, const sf::Vector2f &position, float rotation,
                       Player &player)
    : GameObject(window, drag), _player(player), render(true)
{
    auto theta = static_cast<float>(-rotation * M_PI / 180);
    this->velocity = {-1111 * std::sin(theta),
                      -1111 * std::cos(theta)}; // change to be max_vel in dir of ship using angle
    this->acceleration = {0, 0};
    this->_sprite.setTexture(Projectile::_texture);
    // Set initial sprite position
    this->_sprite.setPosition(position); // window.getsize().x
    // set initial sprite rotation
    this->_sprite.setRotation(rotation - 90); // supposed to rotate image to point same direction as ship
    // Apply custom x and y scaling to sprite
    this->_sprite.setScale({0.2, 0.2});
    // Set sprite origin to centroid of texture
    this->_sprite.setOrigin(static_cast<sf::Vector2f>(Projectile::_texture.getSize()) / 2.0F);
};

void Projectile::update(float delta_time)
{

    // checking for collisions with player
    if (inPlayer())
    {
        this->_player.removeLives(1);
        this->render = false;
        std::cout << "player hit" << std::endl;
    }

    // checking for collisions with asteroids

    // move projectile in its own manner
    this->_sprite.move(this->velocity * delta_time);

    // checking if on screen
    auto [window_w, window_h] = static_cast<sf::Vector2f>(this->window.getSize());
    if (this->_sprite.getPosition().x > window_w || this->_sprite.getPosition().x < 0 ||
        this->_sprite.getPosition().y > window_h || this->_sprite.getPosition().y < 0)
    {
        // allows the larger controller to know to not render this object
        this->render = false;
    }

    // pushing changes to window
    this->window.draw(this->_sprite);
};

void Projectile::setVelocity(const Vector2f &new_velocity)
{
    this->velocity = new_velocity;
}

void Projectile::setAcceleration(const Vector2f &new_acceleration)
{
    this->acceleration = new_acceleration;
}

bool Projectile::inPlayer()
{
    // get vector of all points in hitbox
    auto points = 3;
    // std::cout << points << std::endl;

    // vector of bullet location transformed same as the player
    auto me = this->_sprite.getPosition();
    // std::cout << "Here" << std::endl;

    // vector storing points in player
    std::vector<sf::Vector2f> temp;
    temp.assign(points, {0, 0});
    for (int i = 0; i < points; i++)
    {
        temp.at(i) = this->_player.hitbox.getTransform().transformPoint(this->_player.hitbox.getPoint(i));
    }
    // std::cout << "Here" << std::endl;

    // calculate all triangle areas
    float areas_total = 0;
    // std::cout<<areas_total<<std::endl;
    for (int i = 0; i < 3; i++)
    {
        areas_total += std::abs(((temp.at(i).x - me.x) * (temp.at((i + 1) % points).y - me.y)) -
                                ((temp.at((i + 1) % points).x - me.x) * (temp.at(i).y - me.y)));
    }
    // std::cout << areas_total << std::endl;

    // TODO rename
    const float check = std::abs(((temp.at(1).x - temp.at(0).x) * (temp.at(2).y - temp.at(0).y)) -
                                 ((temp.at(2).x - temp.at(0).x) * (temp.at(1).y - temp.at(0).y)));

    return areas_total == check;
}
