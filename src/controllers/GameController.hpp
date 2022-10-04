#ifndef SRC_CONTROLLERS_GAMECONTROLLER_HPP
#define SRC_CONTROLLERS_GAMECONTROLLER_HPP

#include "game-objects/spaceship/Enemy.hpp"
#include "game-objects/spaceship/Player.hpp"
#include "interfaces/Updatable.hpp"
#include <vector>

class GameController : public Updatable
{
  private:
    // Player player;
    std::vector<Enemy> enemies;
    std::vector<Updatable> updatables;
    // bool isPaused;
    // PauseOverlay pauseOverlay;
  public:
    // need to implement updatable function
    // bool getPaused();
    // void setPaused(bool paused);
    void update();
};

#endif // SRC_CONTROLLERS_GAMECONTROLLER_HPP