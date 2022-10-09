//TODO: Add Main Menu to App

#ifndef SRC_CONTROLLERS_APP_HPP
#define SRC_CONTROLLERS_APP_HPP

#include "./GameController.hpp"

class App 
{
    private:
        GameController _gameController;
        bool _isInGame;
    public:
        bool getIsInGame() const;
        void setIsInGame(bool in_game);
        void beginGameLoop();
};

#endif // SRC_CONTROLLERS_APP_HPP