#include "./Projectile.hpp"
#include "cmath"

Projectile::Projectile(sf::RenderWindow &window, float drag, const sf::Vector2f &position, float rotation, Player &player) : GameObject(window, drag), _player(player), render(true)
{
    auto theta = static_cast<float>(-rotation * M_PI / 180);
    this->velocity = {-1111*std::sin(theta), -1111*std::cos(theta)}; //change to be max_vel in dir of ship using angle
    this->acceleration = {0, 0};
    this->_sprite.setTexture(Projectile::_texture);
    // Set initial sprite position
    this->_sprite.setPosition(position); //window.getsize().x
    // set initial sprite rotation
    this->_sprite.setRotation(rotation - 90); //supposed to rotate image to point same direction as ship
    // Apply custom x and y scaling to sprite
    this->_sprite.setScale({0.2, 0.2});
    // Set sprite origin to centroid of texture
    this->_sprite.setOrigin(static_cast<sf::Vector2f>(Projectile::_texture.getSize()) / 2.0F);
};

void Projectile::update(float delta_time) {
    //move projectile in its own manner
    this->_sprite.move(this->velocity * delta_time);

    //checking for collisions with player
    this->_player.hitbox.;

    //checking for collisions with asteroids


    //checking if on screen
    auto [window_w, window_h] = static_cast<sf::Vector2f>(this->_window.getSize());
    if (this->_sprite.getPosition().x > window_w || this->_sprite.getPosition().x < 0 || this->_sprite.getPosition().y > window_h || this->_sprite.getPosition().y < 0){
        //allows the larger controller to know to not render this object
        this->render = false;
    }
    
    //pushing changes to window
    this->_window.draw(this->_sprite);
};

Vector2f Projectile::getVelocity() {
    return this->velocity;
}

Vector2f Projectile::getAcceleration() {
    return this->acceleration;
}

void Projectile::setVelocity(const Vector2f &new_velocity) {
    this->velocity = new_velocity;
}

void Projectile::setAcceleration(const Vector2f &new_acceleration){
    this->acceleration = new_acceleration;
}