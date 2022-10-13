#include "./Projectile.hpp"

Projectile::Projectile(sf::RenderWindow &window, float drag, Vector2f &velocity, const sf::Vector2f &position, float &rotation) : GameObject(window, drag){
    this->velocity = velocity * 1.1;
    this->acceleration = {0, 0};
    //add bits for includes to filesys and load sprite/image here with location/position and rotation of ship
    if (!this->_texture.loadFromFile(FileSystem::getExecutablePath() + "assets/" + "bullet.png"))
        // Error while loading texture - exit program
        exit(1); // NOLINT(concurrency-mt-unsafe)
    this->_sprite.setTexture(this->_texture);
    // Set initial sprite position
    this->_sprite.setPosition(position);
    // set initial sprite rotation
    this->_sprite.setRotation(rotation);
    // Apply custom x and y scaling to sprite
    this->_sprite.setScale({10, 10});
};

void Projectile::update(float delta_time) {
    //add pointer for player here to check position/hitbox
    this->_sprite.move(this->velocity * delta_time);

    //checking for collisions


    //checking if on screen
    
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