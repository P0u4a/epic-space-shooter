#ifndef SRC_CONTROLLERS_GAMECONTROLLER_HPP
#define SRC_CONTROLLERS_GAMECONTROLLER_HPP

#include "game-objects/spaceship/Enemy.hpp"
#include "game-objects/spaceship/Player.hpp"
#include "game-objects/Projectile.hpp"
#include "interfaces/Updatable.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class GameController : public Updatable
{
  private:
    sf::RenderWindow &_window;
    Player _player;
    std::vector<Enemy> _enemies;
    std::vector<Updatable> _updatables;
    bool _isPaused;

  public:
    explicit GameController(sf::RenderWindow &window);
    bool getPaused() const;
    void setPaused(bool paused);
    // Need to implement updatable function
    void update(float delta_time) override;
    static std::vector<Projectile> _projectiles;
};

#endif // SRC_CONTROLLERS_GAMECONTROLLER_HPP
