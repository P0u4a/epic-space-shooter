#include "PauseOverlay.hpp"
#include "controllers/App.hpp"
#include <SFML/Window/Keyboard.hpp>

PauseOverlay::PauseOverlay(sf::RenderWindow &window)
    : _window(window), _resume(MenuButton(window, 0.5, 0.3, "Press ESC to Resume")),
      _quit(window, 0.5, 0.5, "Press R to Return Home")
{
}

bool PauseOverlay::update(float /*delta_time*/)
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->_is_esc_pressed = false;

    if (is_visible)
    {
        this->_window.draw(this->_resume.getButton());
        this->_window.draw(this->_quit.getButton());

        // Return to game
        if (!_is_esc_pressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            is_visible = false;
            this->_is_esc_pressed = true;
            return false;
        }
        // Exit to main menu
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            is_visible = false;
            App::setIsInGame(false);
            return true;
        }
    }
    else
    {
        // Open pause menu
        if (!_is_esc_pressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            is_visible = true;
            this->_is_esc_pressed = true;
            return false;
        }
    }

    return false;
}

bool PauseOverlay::getVisibility()
{
    return is_visible;
}

void PauseOverlay::setVisibility(bool visibility)
{
    is_visible = visibility;
}
