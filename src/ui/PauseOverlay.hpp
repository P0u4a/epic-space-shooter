#ifndef SRC_UI_PAUSEOVERLAY_HPP
#define SRC_UI_PAUSEOVERLAY_HPP

#include "./MenuButton.hpp"
#include "interfaces/Updatable.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class PauseOverlay : public Updatable
{
  private:
    sf::RenderWindow &_window;
    MenuButton _resume;
    MenuButton _quit;
    // Control the visibility of the pause overlay with this
    inline static bool _isVisible = false;

  public:
    explicit PauseOverlay(sf::RenderWindow &window);
    void update(float delta_time) override;
    static bool getVisibility();
    static void setVisibility(bool visibility);
};

#endif // SRC_UI_PAUSEOVERLAY_HPP