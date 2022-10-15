#include "./GameController.hpp"
#include "game-objects/spaceship/Player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "util/FileSystem.hpp"

GameController::GameController(sf::RenderWindow &window)
    : _window(window), _firstPlayer(Player(window, 1000.0, 500.0, 1.5, 3, {10, 10},
                                           {sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::D})),
      _secondPlayer(
          Player(window, 1000.0, 500.0, 1.5, 3, {10, 10}, {sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Right})), _isPaused(false)
{
    auto [window_w, window_h] = static_cast<sf::Vector2f>(window.getSize());
    // Configure player 1 position and colour
    this->_firstPlayer.setSprite(sf::Color::Red);
    this->_firstPlayer.setPosition(0.25 * window_w, 0.5 * window_h);
    // Configure player 2 position and colour
    this->_secondPlayer.setSprite(sf::Color::Green);
    this->_secondPlayer.setPosition(0.75 * window_w, 0.5 * window_h);

    for (int i = 0; i < 4; i++)
    {
        this->_asteroids.push_back(Asteroid(window, 300, {(rand() % 3)+1, (rand() % 3) +1}, false));
    }

    // for (int i = 0; i < 4; i++)
    // {
    //     Vector2f spawn = Asteroid::generateAsteroids();
    //     this->_asteroids[i].setPosition(spawn.x, spawn.y);
    // }


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

    // Update player states
    this->_firstPlayer.update(delta_time);
    this->_secondPlayer.update(delta_time);

    // Loop through all asteroids and update their state
    for (auto &asteroid : this->_asteroids)
        asteroid.update(delta_time);
    // this->_asteroid.update(delta_time);
    // Loop through all remaining updateable objects and update their state
    for (auto &updateable : this->_updatables)
        updateable.update(delta_time);
}
