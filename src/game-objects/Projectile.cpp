#include "./Projectile.hpp"
#include "cmath"
#include "util/Vector.hpp"
#include <SFML/Graphics/Color.hpp>

Projectile::Projectile(sf::RenderWindow &window, float drag, const sf::Vector2f &position, float rotation,
                       Player &player, sf::Color color)
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
    this->_sprite.setRotation(rotation); // supposed to rotate image to point same direction as ship
    // Apply custom x and y scaling to sprite
    this->_sprite.setScale({6, 6});
    // Set custom color to sprite
    this->_sprite.setColor(color);
}

void Projectile::update(float delta_time)
{
    const int n_points = 3;

    // Vector storing points in player
    std::vector<sf::Vector2f> temp;
    temp.assign(n_points, {0, 0});
    for (int i = 0; i < n_points; i++)
        // loading player hitbox points in global coordinate grid not player local grid
        temp[i] = this->_player.getHitbox().getTransform().transformPoint(this->_player.getHitbox().getPoint(i));

    // Check for collisions with player
    if (inPlayer(temp[0], temp[1], delta_time) || inPlayer(temp[0], temp[2], delta_time) || inPlayer(temp[1], temp[2], delta_time))
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

bool Projectile::inPlayer(sf::Vector2f first, sf::Vector2f second, float delta_time)
{
    auto playerVel = second - first;
    auto bulletVel = this->getVelocity();
    

    //if bullet is parallel to this line segment then isnt intersecting
    if (playerVel.x/bulletVel.x == playerVel.y/bulletVel.y){
        return false;
    }

    auto bulletPos = this->_sprite.getPosition();
    //how far along hitbox edge bullet will hit
    float s = (bulletPos.y - first.y + (bulletVel.y/bulletVel.x)*(first.x-bulletPos.x))/
        (playerVel.y - (bulletVel.y/bulletVel.x)*(playerVel.x));

    if (s<0 || s>1){
        //if s outside 0-1 then means bullet will not hit this edge within its vertecies
        return false;
    }

    //time for bullet to hit hitbox
    float t = (first.x - bulletPos.x + s*playerVel.x)/(bulletVel.x);

    //checking if time for bullet to hit edge within the next frame
    if (t<0 || t>delta_time){
        return false;
    }    

    return true;
}
