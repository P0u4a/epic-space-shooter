#include "App.hpp"
#include "controllers/GameController.hpp"
#include "util/AssetLoader.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

App::App() : _gameController(_window), _pauseOverlay(_window), _mainMenu(_window)
{
    this->_window.setVerticalSyncEnabled(true);
}

bool App::getIsInGame()
{
    return is_in_game;
}

void App::setIsInGame(bool in_game)
{
    is_in_game = in_game;
}

int App::beginGameLoop()
{
    // Add background
    auto background = sf::RectangleShape(static_cast<sf::Vector2f>(this->_window.getSize()));
    sf::Texture *bg_texture = nullptr;
    AssetLoader::loadTextureAsset(bg_texture, "background.png");
    auto [window_w, window_h] = static_cast<sf::Vector2i>(this->_window.getSize());
    if (bg_texture != nullptr)
    {
        bg_texture->setRepeated(true);
        background.setTexture(bg_texture);
    }
    background.setTextureRect({0, 0, window_w, window_h});
    background.setScale({4, 4});

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
        this->_window.draw(background);

        // Update main menu while not in game
        if (!is_in_game)
        {
            this->_mainMenu.update(time.asSeconds());
            // Recreate GameController if game over
            if (this->_is_game_over)
            {
                // Recreate the GameController to reset the game after game over
                this->_gameController.~GameController();
                // deepcode ignore CppMemoryLeak: placement-new will construct GameController in existing stack address
                new (&this->_gameController) GameController(this->_window);
                this->_is_game_over = false;
            }
        }
        // Run next game tick if in game
        else
        {
            this->_is_game_over =
                this->_gameController.runGameTick(time.asSeconds()) || this->_pauseOverlay.update(time.asSeconds());
        }

        // Display the current frame
        this->_window.display();
    }
    return 0;
}
