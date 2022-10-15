#ifndef SRC_CONTROLLERS_GAMECONTROLLER_HPP
#define SRC_CONTROLLERS_GAMECONTROLLER_HPP

#include "game-objects/spaceship/Asteroid.hpp"
#include "game-objects/spaceship/Player.hpp"
#include "interfaces/Updatable.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class GameController : public Updatable
{
  private:
    sf::RenderWindow &_window;
    Player _firstPlayer;
    Player _secondPlayer;
    // std::vector<Enemy> _enemies;
    // Asteroid _asteroid;
    std::vector<Asteroid>_asteroids;
    std::vector<Updatable> _updatables;
    bool _isPaused;

  public:
    explicit GameController(sf::RenderWindow &window);
    bool getPaused() const;
    void setPaused(bool paused);
    void update(float delta_time) override;
};

#endif // SRC_CONTROLLERS_GAMECONTROLLER_HPP
