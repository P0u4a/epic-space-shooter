#include "./GameController.hpp"
#include "game-objects/Projectile.hpp"
#include "game-objects/spaceship/Player.hpp"
#include "ui/PauseOverlay.hpp"
#include "util/AssetLoader.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <utility>

GameController::GameController(sf::RenderWindow &window)
    : _window(window), _firstPlayer(Player(window, 1000.0, 500.0, 1.5, 3, {10, 10},
                                           {sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::S})),
      _secondPlayer(Player(window, 1000.0, 500.0, 1.5, 3, {10, 10},
                           {sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Down}))
{
    // Load projectile texture
    AssetLoader::loadTextureAsset(Projectile::texture, "bullet.png");
    auto [window_w, window_h] = static_cast<sf::Vector2f>(this->_window.getSize());
    // Configure player 1 position and colour
    _firstPlayer.setSprite(sf::Color::Red);
    _firstPlayer.setPosition(0.25F * window_w, 0.5F * window_h);
    // Configure player 2 position and colour
    _secondPlayer.setSprite(sf::Color::Green);
    _secondPlayer.setPosition(0.75F * window_w, 0.5F * window_h);
}

/**
 * @brief Run single game loop iteration - single game tick
 */
void GameController::update(float delta_time)
{
    // Don't run main game logic if paused
    if (PauseOverlay::getVisibility())
        return;

    // Update player states
    this->_firstPlayer.update(delta_time);
    this->_secondPlayer.update(delta_time);

    // For both palyers check if they fired and create more projectiles
    if (this->_firstPlayer.fired)
    {
        auto new_projectile =
            std::make_unique<Projectile>(this->_window, 0, this->_firstPlayer.getHitbox().getPosition(),
                                         this->_firstPlayer.getHitbox().getRotation(), this->_secondPlayer);
        this->_projectiles.push_back(std::move(new_projectile));
        this->_firstPlayer.fired = false;
    }
    if (this->_secondPlayer.fired)
    {
        auto new_projectile =
            std::make_unique<Projectile>(this->_window, 0, this->_secondPlayer.getHitbox().getPosition(),
                                         this->_secondPlayer.getHitbox().getRotation(), this->_firstPlayer);
        this->_projectiles.push_back(std::move(new_projectile));
        this->_secondPlayer.fired = false;
    }

    // Loop through all projectiles
    for (auto itr = this->_projectiles.begin(); itr != this->_projectiles.end();)
    {
        (*itr)->update(delta_time);
        if (!(*itr)->render)
            // Delete projectile
            _projectiles.erase(itr);
        else
            ++itr;
    }
}
