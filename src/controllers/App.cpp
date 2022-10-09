#include "App.hpp"
#include "controllers/GameController.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

App::App() : _gameController(_window), _isInGame(false)
{
}

bool App::getIsInGame() const
{
    return this->_isInGame;
}

void App::setIsInGame(bool in_game)
{
    this->_isInGame = in_game;
}

int App::beginGameLoop()
{
    // TODO debug, remove
    this->_isInGame = true;

    // Run main game loop as long as the window is open
    while (this->_window.isOpen())
    {
        // Check all window events triggered since the last iteration
        sf::Event event{};
        while (this->_window.pollEvent(event))
        {
            // Close requested - close the window
            if (event.type == sf::Event::Closed)
                this->_window.close();
        }
        // Clear previous frames
        this->_window.clear(sf::Color::Red);

        // Run next game tick if in game
        if (this->_isInGame)
            this->_gameController.update();

        // Display the current frame
        this->_window.display();
    }
    return 0;
}
