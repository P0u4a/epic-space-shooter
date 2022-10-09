#include "./GameController.hpp"
#include "game-objects/spaceship/Player.hpp"

GameController::GameController() : _player(Player(1.0, 1.0, 1.0, 3)), _isPaused(false)
{
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
void GameController::update()
{
    // Don't run main game logic if paused
    if (this->_isPaused)
        return;

    // Update player state
    this->_player.update();
    // Loop through all enemies and update their state
    for (auto &enemy : this->_enemies)
        enemy.update();
    // Loop through all remaining updateable objects and update their state
    for (auto &updateable : this->_updatables)
        updateable.update();
}
