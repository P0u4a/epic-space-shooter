#include <catch2/matchers/catch_matchers.hpp>
#include <iostream>
#define BUILD_TESTING

#include "src/game-objects/spaceship/Player.hpp"
#include "src/util/Vector.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

// NOLINTBEGIN

using namespace Catch;
using namespace Matchers;

TEST_CASE("lives are correctly handled", "[player]")
{
    auto window = sf::RenderWindow();
    int initial_lives = 5;
    Player player(window, 0, 0, 0, 5, {0, 0}, {});

    SECTION("initial lives correctly set")
    {
        REQUIRE(player.getLives() == initial_lives);
    }

    SECTION("lives can be removed")
    {
        int previous_lives = player.getLives();
        int lives_to_remove = 3;
        player.removeLives(lives_to_remove);
        REQUIRE(player.getLives() == previous_lives - lives_to_remove);
    }
}

TEST_CASE("player movement is correctly handled", "[player]")
{
    auto window = sf::RenderWindow();
    int initial_lives = 5;
    int max_speed = 1000;
    int max_acceleration = 1000;
    Player player(window, max_speed, max_acceleration, 0, 5, {0, 0}, {});

    SECTION("player velocity initially zero")
    {
        REQUIRE(player.getVelocity() == Vector2f(0, 0));
    }

    SECTION("player acceleration initially zero")
    {
        REQUIRE(player.getAcceleration() == Vector2f(0, 0));
    }

    SECTION("player can accelerate forwards")
    {
        player.accelerateForwards();
        REQUIRE_THAT(player.getAcceleration().x, WithinAbs(0, 0.0001F));
        REQUIRE_THAT(player.getAcceleration().y, WithinAbs(-max_acceleration, 0.0001F));
    }

    SECTION("player can accelerate towards rotated direction")
    {
        SECTION("player can accelerate towards positive rotated direction")
        {
            float angle = 72;
            player.rotate(angle);
            player.accelerateForwards();
            REQUIRE_THAT(player.getAcceleration().x, WithinAbs(max_acceleration * 0.9510565163F, 0.0001F));
            REQUIRE_THAT(player.getAcceleration().y, WithinAbs(max_acceleration * -0.3090169944F, 0.0001F));
        }

        SECTION("player can accelerate towards negative rotated direction")
        {
            float angle = -72;
            player.rotate(angle);
            player.accelerateForwards();
            REQUIRE_THAT(player.getAcceleration().x, WithinAbs(max_acceleration * -0.9510565163F, 0.0001F));
            REQUIRE_THAT(player.getAcceleration().y, WithinAbs(max_acceleration * -0.3090169944F, 0.0001F));
        }
    }
}

// NOLINTEND
