#include "PauseOverlay.hpp"
#include "controllers/App.hpp"
#include <SFML/Window/Keyboard.hpp>

PauseOverlay::PauseOverlay(sf::RenderWindow &window)
    : _window(window), _resume(MenuButton(window, 0.5, 0.3, "Press ESC to Resume")),
      _quit(window, 0.5, 0.5, "Press R to Return Home")
{
}

void PauseOverlay::update(float /*delta_time*/)
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        _is_esc_pressed = false;

    if (is_visible)
    {
        _window.draw(_resume.getButton());
        _window.draw(_quit.getButton());

        if (!_is_esc_pressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            is_visible = false;
            _is_esc_pressed = true;
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            is_visible = false;
            App::setIsInGame(false);
        }
    }
    else
    {
        if (!_is_esc_pressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            is_visible = true;
            _is_esc_pressed = true;
            return;
        }
    }
}

bool PauseOverlay::getVisibility()
{
    return is_visible;
}

void PauseOverlay::setVisibility(bool visibility)
{
    is_visible = visibility;
}
