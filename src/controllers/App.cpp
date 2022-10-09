#include "App.hpp"

bool App::getIsInGame() const
{
    return this->_isInGame;
}

void App::setIsInGame(bool in_game)
{
    this->_isInGame = in_game;
}

// void App::beginGameLoop()
// {
//     while(true)
//     {

//     }
// }