#ifndef SRC_CONTROLLERS_GAMECONTROLLER_HPP
#define SRC_CONTROLLERS_GAMECONTROLLER_HPP

#include "game-objects/Projectile.hpp"
#include "game-objects/spaceship/Player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>

class GameController
{
  private:
    sf::RenderWindow &_window;
    Player _firstPlayer;
    Player _secondPlayer;
    std::vector<std::unique_ptr<Projectile>> _projectiles;
    sf::Text _p1_lives_text;
    sf::Text _p2_lives_text;
    sf::Text _lives_text;

  public:
    explicit GameController(sf::RenderWindow &window);
    /**
     * @brief Run single game loop iteration - single game tick
     *
     * @param delta_time Time since last frame (in seconds)
     * @return True if either player has lives <= 0 {game over}.
     * @return False if game not over
     */
    bool runGameTick(float delta_time);
};

#endif // SRC_CONTROLLERS_GAMECONTROLLER_HPP
