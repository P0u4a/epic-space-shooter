#ifndef SRC_CONTROLLERS_GAMECONTROLLER_HPP
#define SRC_CONTROLLERS_GAMECONTROLLER_HPP

#include "game-objects/spaceship/Enemy.hpp"
#include "game-objects/spaceship/Player.hpp"
#include "interfaces/Updatable.hpp"
#include <vector>

class GameController : public Updatable
{
  private:
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Updatable> updatables;
    bool isPaused;

  public:
    bool getPaused() const;
    void setPaused(bool paused);
    // Need to implement updatable function
    void update();
};

#endif // SRC_CONTROLLERS_GAMECONTROLLER_HPP