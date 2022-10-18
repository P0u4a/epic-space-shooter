#ifndef SRC_UI_MAINMENU_HPP
#define SRC_UI_MAINMENU_HPP
#include "./MenuButton.hpp"
#include "interfaces/Updatable.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class MainMenu : public Updatable
{
  private:
    sf::RenderWindow &_window;
    std::string _menuTitle;
    MenuButton _play;
    MenuButton _quit;

  public:
    explicit MainMenu(sf::RenderWindow &window);

    /**
     * @brief Update Menu: if X is pressed, return to game, if Escape is pressed, exit game, Draw menu buttons to screen
     *
     * @param delta_time Time since last frame
     */
    void update(float delta_time) override;
};

#endif // SRC_UI_MAINMENU_HPP
