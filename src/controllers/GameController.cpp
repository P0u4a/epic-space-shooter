#include "./GameController.hpp"
#include "game-objects/spaceship/Player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

GameController::GameController(sf::RenderWindow &window)
    : _window(window), _player(Player(window, 1000.0, 500.0, 1.5, 3, {10, 10})), _isPaused(false)
{
    //Projectile::_player = &_player;
}

bool GameController::getPaused() const
{
    return this->_isPaused;
}

void GameController::setPaused(bool paused)
{
    this->_isPaused = paused;
}

/**
 * @brief Run single game loop iteration - single game tick
 */
void GameController::update(float delta_time)
{
    // Don't run main game logic if paused
    if (this->_isPaused)
        return;

    // Update player state
    this->_player.update(delta_time);
    // Loop through all enemies and update their state
    for (auto &enemy : this->_enemies)
        enemy.update(delta_time);
    // Loop through all remaining updateable objects and update their state
    for (auto &updateable : this->_updatables)
        updateable.update(delta_time);
    // Loop through all bullets
    for (auto &projectile : _player._projectiles)
        projectile.update(delta_time);
}
