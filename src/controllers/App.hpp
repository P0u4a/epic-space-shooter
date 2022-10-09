// TODO: Add Main Menu to App

#ifndef SRC_CONTROLLERS_APP_HPP
#define SRC_CONTROLLERS_APP_HPP

#include "./GameController.hpp"

class App
{
  private:
    GameController _gameController;
    bool _isInGame;

  public:
    App();
    bool getIsInGame() const;
    void setIsInGame(bool in_game);
    int beginGameLoop();
};

#endif // SRC_CONTROLLERS_APP_HPP
