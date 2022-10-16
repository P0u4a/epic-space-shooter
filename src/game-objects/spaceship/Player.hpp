#ifndef SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
#define SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP

#include "./Spaceship.hpp"
#include "util/Vector.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

class Player : public Spaceship
{
  private:
    std::vector<sf::Texture> _flames_textures;
    sf::Sprite _flames_sprite;
    int _curr_flames_tex_i = 0;
    int _lives;
    
    struct moveKeys
    {
        // This works without using the enum keyword at the beginning i guess
        sf::Keyboard::Key moveUp;
        sf::Keyboard::Key rotateLeft;
        sf::Keyboard::Key rotateRight;
        sf::Keyboard::Key fire;

    } _keys;

  public:
    Player(float max_speed, float max_acceleration, float drag, int lives, Vector2f scale,
           moveKeys keys);
    Player(const Player &player) = default;

    int getLives() const;

    bool fired;

    /**
     * @brief Removes lives from the player
     *
     * @param lives_to_remove Number of lives to remove
     * @returns If the player is alive (true) or not (false)
     */
    bool removeLives(int lives_to_remove);

    void rotate(float angle) override;
    void setPosition(float x, float y) override;

    void update(float delta_time) override;
};

#endif // SRC_GAME_OBJECTS_SPACESHIP_PLAYER_HPP
