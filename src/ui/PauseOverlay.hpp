#ifndef SRC_UI_PAUSEOVERLAY_HPP
#define SRC_UI_PAUSEOVERLAY_HPP

#include "./MenuButton.hpp"
#include "interfaces/Updatable.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class PauseOverlay
{
  private:
    sf::RenderWindow &_window;
    MenuButton _resume;
    MenuButton _quit;
    bool _is_esc_pressed = false;
    // Control the visibility of the pause overlay with this
    inline static bool is_visible = false;

  public:
    explicit PauseOverlay(sf::RenderWindow &window);

    static bool getVisibility();
    static void setVisibility(bool visibility);

    /**
     * @brief Create pause overlay
     *
     * @return True if exit to main menu
     */
    bool update(float delta_time);
};

#endif // SRC_UI_PAUSEOVERLAY_HPP
