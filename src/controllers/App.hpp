// TODO: Add Main Menu to App

#ifndef SRC_CONTROLLERS_APP_HPP
#define SRC_CONTROLLERS_APP_HPP

#include "./GameController.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class App
{
  private:
    // TODO screen resolution
    sf::RenderWindow _window = sf::RenderWindow(sf::VideoMode(800, 600), "Epic Space Shooter");
    GameController _gameController;
    bool _isInGame;

  public:
    App();
    bool getIsInGame() const;
    void setIsInGame(bool in_game);
    int beginGameLoop();
};

#endif // SRC_CONTROLLERS_APP_HPP
