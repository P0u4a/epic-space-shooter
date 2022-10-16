#ifndef SRC_CONTROLLERS_GAMECONTROLLER_HPP
#define SRC_CONTROLLERS_GAMECONTROLLER_HPP

#include "game-objects/spaceship/Enemy.hpp"
#include "game-objects/spaceship/Player.hpp"
#include "game-objects/Projectile.hpp"
#include "interfaces/Updatable.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "algorithm"

class GameController : public Updatable
{
  private:
    sf::RenderWindow &_window;
    Player _firstPlayer;
    Player _secondPlayer;
    std::vector<Enemy> _enemies;
    std::vector<Updatable> _updatables;
    std::vector<std::unique_ptr<Projectile>> _projectiles;
    // bool _isPaused;

  public:
    explicit GameController(sf::RenderWindow &window);
    void update(float delta_time) override;
};

#endif // SRC_CONTROLLERS_GAMECONTROLLER_HPP
