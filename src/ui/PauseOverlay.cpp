#include "PauseOverlay.hpp"
#include "controllers/App.hpp"
#include <SFML/Window/Keyboard.hpp>

PauseOverlay::PauseOverlay(sf::RenderWindow &window)
    : _window(window), _resume(MenuButton(window, 0.5, 0.3, "Press ESC to Resume")),
      _quit(window, 0.5, 0.5, "Press R to Return Home")
{
}

void PauseOverlay::update(float delta_time)
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        _is_esc_pressed = false;

    if (_isVisible)
    {
        _window.draw(_resume.getButton());
        _window.draw(_quit.getButton());

        if (!_is_esc_pressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            _isVisible = false;
            _is_esc_pressed = true;
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            _isVisible = false;
            App::setIsInGame(false);
        }
    }
    else
    {
        if (!_is_esc_pressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            _isVisible = true;
            _is_esc_pressed = true;
            return;
        }
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
