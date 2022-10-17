#include "MainMenu.hpp"
#include "controllers/App.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

MainMenu::MainMenu(sf::RenderWindow &window)
    : _window(window), _play(MenuButton(window, 0.5, 0.3, "Press X to Play")),
      _quit(MenuButton(window, 0.5, 0.5, "Press Esc to Quit"))
{
}

void MainMenu::update(float /*delta_time*/)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        App::setIsInGame(true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        _window.close();
    }

    _window.draw(_play.getButton());
    _window.draw(_quit.getButton());
}
