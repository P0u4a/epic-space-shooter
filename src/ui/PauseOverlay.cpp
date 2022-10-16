#include "PauseOverlay.hpp"
#include "controllers/App.hpp"
#include <SFML/Window/Keyboard.hpp>

PauseOverlay::PauseOverlay(sf::RenderWindow &window)
    : _window(window), _resume(MenuButton(window, 0.5, 0.3, "Press Enter to Resume")), _quit(window, 0.5, 0.5, "Press R to Return Home")
{
}

void PauseOverlay::update(float delta_time)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        _isVisible = true;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        _isVisible = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        _isVisible = false;
        App::setIsInGame(false);
    }

    if (_isVisible)
    {
        _window.draw(_resume.getButton());
        _window.draw(_quit.getButton());
    }
}

bool PauseOverlay::getVisibility()
{
    return _isVisible;
}

void PauseOverlay::setVisibility(bool visibility)
{
    _isVisible = visibility;
}