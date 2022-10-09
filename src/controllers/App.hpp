// TODO: Add Main Menu to App

#ifndef SRC_CONTROLLERS_APP_HPP
#define SRC_CONTROLLERS_APP_HPP

#include "./GameController.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/WindowStyle.hpp>

class App
{
  private:
    sf::ContextSettings _settings = sf::ContextSettings(0, 0, 8, 1, 1, sf::ContextSettings::Default, false);
    // TODO screen resolution
    sf::RenderWindow _window =
        sf::RenderWindow(sf::VideoMode(800, 600), "Epic Space Shooter", sf::Style::Default, _settings);
    GameController _gameController;
    bool _isInGame;

  public:
    App();
    bool getIsInGame() const;
    void setIsInGame(bool in_game);
    int beginGameLoop();
};

#endif // SRC_CONTROLLERS_APP_HPP
