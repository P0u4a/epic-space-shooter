#include "./Projectile.hpp"
#include "cmath"
#include "util/Vector.hpp"

Projectile::Projectile(sf::RenderWindow &window, float drag, const sf::Vector2f &position, float rotation,
                       Player &player)
    : GameObject(window, drag), _player(player), render(true)
{
    auto theta = static_cast<float>(-rotation * M_PI / 180.0F);
    this->velocity = Vector2f(std::sin(theta), std::cos(theta)) * -kProjectileSpeed;
    this->acceleration = {0, 0};
    if (Projectile::texture != nullptr)
    {
        this->_sprite.setTexture(*Projectile::texture);
        // Set sprite origin to centroid of texture
        this->_sprite.setOrigin(static_cast<sf::Vector2f>(Projectile::texture->getSize()) / 2.0F);
    }
    // Set initial sprite position
    this->_sprite.setPosition(position); // window.getsize().x
    // Det initial sprite rotation
    this->_sprite.setRotation(rotation - 90); // supposed to rotate image to point same direction as ship
    // Apply custom x and y scaling to sprite
    this->_sprite.setScale({0.2, 0.2});
}

void Projectile::update(float delta_time)
{

    // Check for collisions with player
    if (inPlayer())
    {
        this->_player.removeLives(1);
        this->render = false;
    }

    // Move projectile forward
    this->_sprite.move(this->velocity * delta_time);

    // Checking if on screen
    auto [window_w, window_h] = static_cast<sf::Vector2f>(this->window.getSize());
    if (this->_sprite.getPosition().x > window_w || this->_sprite.getPosition().x < 0 ||
        this->_sprite.getPosition().y > window_h || this->_sprite.getPosition().y < 0)
    {
        // Flag gamecontroller to not render this projectile
        this->render = false;
    }

    // Push changes to window
    this->window.draw(this->_sprite);
}

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
    const int n_points = 3;
    // Bullet loaded in for use in calculations to check if colliding with player
    auto projectile_pos = this->_sprite.getPosition();

    // Vector storing points in player
    std::vector<sf::Vector2f> temp;
    temp.assign(n_points, {0, 0});
    for (int i = 0; i < n_points; i++)
        // loading player hitbox points in global coordinate grid not player local grid
        temp[i] = this->_player.getHitbox().getTransform().transformPoint(this->_player.getHitbox().getPoint(i));

    // Calculate all triangle areas
    float areas_total = 0;
    for (int i = 0; i < 3; i++)
    {
        areas_total += std::abs(((temp[i].x - projectile_pos.x) * (temp[(i + 1) % n_points].y - projectile_pos.y)) -
                                ((temp[(i + 1) % n_points].x - projectile_pos.x) * (temp[i].y - projectile_pos.y)));
    }

    const float real_hitbox_area = std::abs(((temp[1].x - temp[0].x) * (temp[2].y - temp[0].y)) -
                                            ((temp[2].x - temp[0].x) * (temp[1].y - temp[0].y)));

    // Colliding with player if sum of sub-triangle areas == area of actual hitbox
    return areas_total == real_hitbox_area;
}
