#include "MenuButton.hpp"
#include "util/AssetLoader.hpp"
#include "util/FileSystem.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <utility>

MenuButton::MenuButton(sf::RenderWindow &window, float pos_x, float pos_y, std::string label) : _label(std::move(label))
{
    // Get window size
    auto [window_w, window_h] = static_cast<sf::Vector2f>(window.getSize());

    // Load font
    AssetLoader::loadAsset(this->_font, "Minecraftia-Regular.ttf");
    if (this->_font != nullptr)
    {
        // Configure button text
        this->_text.setFont(*_font);
        this->_text.setString(_label);
        this->_text.setFillColor(sf::Color::Yellow);
        this->_text.setStyle(sf::Text::Bold);
        this->_text.setCharacterSize(50);
        // Set the origin to the center of text
        this->_text.setOrigin(this->_text.getLocalBounds().left + this->_text.getLocalBounds().width / 2.F,
                              this->_text.getLocalBounds().top + this->_text.getLocalBounds().height / 2.F);

        this->_text.setPosition(pos_x * window_w, pos_y * window_h);
    }
}

void MenuButton::setButton(sf::Color color)
{
    if (this->_font != nullptr)
        this->_text.setFillColor(color);
}

sf::Text MenuButton::getButton()
{
    return this->_text;
}
