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
    sf::RenderWindow _window = sf::RenderWindow(
        sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height - 100,
                      sf::VideoMode::getDesktopMode().bitsPerPixel),
        "Epic Space Shooter", sf::Style::Titlebar | sf::Style::Close, _settings);
    sf::Clock _clock;
    GameController _gameController;
    PauseOverlay _pauseOverlay;
    MainMenu _mainMenu;
    bool _is_game_over = false;
    inline static bool is_in_game = false;

  public:
    App();
    /**
     * @return True if in game
     */
    static bool getIsInGame();
    static void setIsInGame(bool in_game);
    /**
     * @brief Begins game loop, creates GameController object, runs game ticks
     * @return Code of the game {0 if no error, 1 if error}
     */
    int beginGameLoop();
};

#endif // SRC_CONTROLLERS_APP_HPP
