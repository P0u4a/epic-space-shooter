#include "./GameController.hpp"
#include "game-objects/Projectile.hpp"
#include "game-objects/spaceship/Player.hpp"
#include "ui/PauseOverlay.hpp"
#include "util/AssetLoader.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <memory>
#include <string>
#include <utility>

GameController::GameController(sf::RenderWindow &window)
    : _window(window), _firstPlayer(Player(window, 1000.0, 500.0, 1.5, 5, {10, 10},
                                           {sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::S})),
      _secondPlayer(Player(window, 1000.0, 500.0, 1.5, 5, {10, 10},
                           {sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Down}))
{
    // Load projectile texture
    AssetLoader::loadAsset(Projectile::texture, "bullet.png");
    auto [window_w, window_h] = static_cast<sf::Vector2f>(this->_window.getSize());
    // Configure player 1 position and colour
    this->_firstPlayer.setSprite(sf::Color::Red);
    this->_firstPlayer.setPosition(0.25F * window_w, 0.5F * window_h);
    // Configure player 2 position and colour
    this->_secondPlayer.setSprite(sf::Color::Green);
    this->_secondPlayer.setPosition(0.75F * window_w, 0.5F * window_h);
    // Load font for player lives text
    sf::Font *font = nullptr;
    AssetLoader::loadAsset(font, "Minecraftia-Regular.ttf");
    // Setup player lives texts
    if (font != nullptr)
    {
        const std::array<sf::Text *, 3> lives_texts = {&this->_p1_lives_text, &this->_p2_lives_text,
                                                       &this->_lives_text};
        for (auto *lives_text : lives_texts)
        {
            lives_text->setFont(*font);
            lives_text->setString("Player lives: ");
            lives_text->setFillColor(sf::Color::Yellow);
            lives_text->setStyle(sf::Text::Bold);
            lives_text->setCharacterSize(40);
        }
        this->_lives_text.setString("Lives Remaining");
        this->_lives_text.setStyle(sf::Text::Underlined | sf::Text::Bold);
        // Set player health text locations
        this->_lives_text.setPosition(30.0F, window_h - (this->_lives_text.getLocalBounds().height) - 400.0F);
        this->_p1_lives_text.setPosition(30.0F, window_h - (this->_p1_lives_text.getLocalBounds().height) - 300.0F);
        this->_p2_lives_text.setPosition(30.0F, window_h - (this->_p2_lives_text.getLocalBounds().height) - 200.0F);
    }
}

/**
 * @brief Run single game loop iteration - single game tick
 */
bool GameController::runGameTick(float delta_time)
{
    // Don't run main game logic if paused
    if (PauseOverlay::getVisibility())
        return false;

    // Update player states
    this->_firstPlayer.update(delta_time);
    this->_secondPlayer.update(delta_time);

    // Flag GameController for recreation after one player killed - game over
    if (this->_firstPlayer.getLives() <= 0 || this->_secondPlayer.getLives() <= 0)
        return true;

    // For both palyers check if they fired and create more projectiles
    if (this->_firstPlayer.fired)
    {
        auto new_projectile =
            std::make_unique<Projectile>(this->_window, 0, this->_firstPlayer.getHitbox().getPosition(),
                                         this->_firstPlayer.getHitbox().getRotation(), this->_secondPlayer);
        this->_projectiles.push_back(std::move(new_projectile));
        this->_firstPlayer.fired = false;
    }
    if (this->_secondPlayer.fired)
    {
        auto new_projectile =
            std::make_unique<Projectile>(this->_window, 0, this->_secondPlayer.getHitbox().getPosition(),
                                         this->_secondPlayer.getHitbox().getRotation(), this->_firstPlayer);
        this->_projectiles.push_back(std::move(new_projectile));
        this->_secondPlayer.fired = false;
    }

    // Loop through all projectiles
    for (auto itr = this->_projectiles.begin(); itr != this->_projectiles.end();)
    {
        (*itr)->update(delta_time);
        if (!(*itr)->render)
            // Delete projectile
            this->_projectiles.erase(itr);
        else
            ++itr;
    }

    // Update player health text
    this->_p1_lives_text.setString("Player 1:   " + std::to_string(this->_firstPlayer.getLives()));
    this->_p2_lives_text.setString("Player 2:   " + std::to_string(this->_secondPlayer.getLives()));
    // Draw player lives text
    this->_window.draw(this->_lives_text);
    this->_window.draw(this->_p1_lives_text);
    this->_window.draw(this->_p2_lives_text);

    return false;
}
