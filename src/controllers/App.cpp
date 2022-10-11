#include "App.hpp"
#include "controllers/GameController.hpp"
#include "util/FileSystem.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

App::App() : _gameController(_window), _isInGame(false)
{
    this->_window.setVerticalSyncEnabled(true);
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

    // Add starfield shader
    auto background = sf::RectangleShape(static_cast<sf::Vector2f>(this->_window.getSize()));
    auto shader = sf::Shader{};
    if (!shader.loadFromFile(FileSystem::getExecutablePath() + "shaders/starfield.frag", sf::Shader::Fragment))
        // Error in loading shader
        return 1;
    shader.setUniform("u_resolution", static_cast<sf::Glsl::Vec2>(this->_window.getSize()));

    // Run main game loop as long as the window is open
    while (this->_window.isOpen())
    {
        // Get elapsed time since last frame
        auto time = this->_clock.getElapsedTime();
        this->_clock.restart();
        // Check all window events triggered since the last iteration
        sf::Event event{};
        while (this->_window.pollEvent(event))
        {
            // Close requested - close the window
            if (event.type == sf::Event::Closed)
                this->_window.close();
        }
        // Clear previous frames
        this->_window.clear(sf::Color::Black);

        // Draw background
        this->_window.draw(background, &shader);

        // Run next game tick if in game
        if (this->_isInGame)
            this->_gameController.update(time.asSeconds());

        // Display the current frame
        this->_window.display();
    }
    return 0;
}
