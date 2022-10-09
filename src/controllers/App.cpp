#include "App.hpp"
#include "controllers/GameController.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

App::App() : _isInGame(false)
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
    // Create the window
    // TODO screen resolution
    sf::RenderWindow window(sf::VideoMode(800, 600), "Epic Space Shooter");
    // Run main game loop as long as the window is open
    while (window.isOpen())
    {
        // Check all window events triggered since the last iteration
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // Close requested - close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear previous frames
        window.clear(sf::Color::Black);

        // Run next game tick if in game
        if (this->_isInGame)
            this->_gameController.update();

        // Display the current frame
        window.display();
    }
    return 0;
}
