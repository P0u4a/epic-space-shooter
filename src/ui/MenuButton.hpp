#ifndef SRC_UI_MENUBUTTON_HPP
#define SRC_UI_MENUBUTTON_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>

class MenuButton
{
  private:
    std::string _label;
    sf::Font *_font = nullptr;
    sf::Text _text;

  public:
    MenuButton(sf::RenderWindow &window, float pos_x, float pos_y, std::string label);
    void setButton(sf::Color color);
    sf::Text getButton();
};

#endif // SRC_UI_MENUBUTTON_HPP
