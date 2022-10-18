#ifndef SRC_CONTROLLERS_APP_HPP
#define SRC_CONTROLLERS_APP_HPP

#include "./GameController.hpp"
#include "ui/MainMenu.hpp"
#include "ui/PauseOverlay.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

class App
{
  private:
    sf::ContextSettings _settings = sf::ContextSettings(0, 0, 8, 1, 1, sf::ContextSettings::Default, false);
    sf::RenderWindow _window =
        sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height),
                         "Epic Space Shooter", sf::Style::None, _settings);
    sf::Clock _clock;
    GameController _gameController;
    PauseOverlay _pauseOverlay;
    MainMenu _mainMenu;
    bool _is_game_over = false;
    inline static bool is_in_game = false;

  public:
    App();
    static bool getIsInGame();
    static void setIsInGame(bool in_game);
    int beginGameLoop();
};

#endif // SRC_CONTROLLERS_APP_HPP
