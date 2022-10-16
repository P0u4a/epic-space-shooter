#include "./GameController.hpp"
#include "game-objects/spaceship/Player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ui/PauseOverlay.hpp"

GameController::GameController(sf::RenderWindow &window)
    : _window(window), _firstPlayer(Player(window, 1000.0, 500.0, 1.5, 3, {10, 10},
                                           {sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::D})),
      _secondPlayer(
          Player(window, 1000.0, 500.0, 1.5, 3, {10, 10}, {sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Right}))
{
    auto [window_w, window_h] = static_cast<sf::Vector2f>(window.getSize());
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

    // Loop through all enemies and update their state
    for (auto &enemy : this->_enemies)
        enemy.update(delta_time);
    // Loop through all remaining updateable objects and update their state
    for (auto &updateable : this->_updatables)
        updateable.update(delta_time);
}
