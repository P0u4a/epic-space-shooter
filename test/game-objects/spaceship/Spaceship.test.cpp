#include "src/game-objects/spaceship/Spaceship.hpp"
#include "src/util/Vector.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <catch2/catch_test_macros.hpp>

// NOLINTBEGIN

using namespace Catch;

TEST_CASE("initial spaceship velocity and acceleration zero", "[spaceship]")
{
    auto window = sf::RenderWindow();
    Spaceship spaceship(window, 0, 0, 0, {0, 0}, {0, 0}, "player-sprite.png");

    REQUIRE(spaceship.getVelocity() == Vector2f(0, 0));
    REQUIRE(spaceship.getAcceleration() == Vector2f(0, 0));
}

TEST_CASE("can set spaceship velocity", "[spaceship]")
{
    auto window = sf::RenderWindow();
    Spaceship spaceship(window, 100, 0, 0, {0, 0}, {0, 0}, "player-sprite.png");

    // Initial velocity must be zero
    REQUIRE(spaceship.getVelocity() == Vector2f(0, 0));
    // Set new velocity
    Vector2f new_velocity(10, 20);
    spaceship.setVelocity(new_velocity);
    // Spaceship velocity must be what it was updated to
    REQUIRE(spaceship.getVelocity() == new_velocity);
}

TEST_CASE("can set spaceship acceleration", "[spaceship]")
{
    auto window = sf::RenderWindow();
    Spaceship spaceship(window, 0, 100, 0, {0, 0}, {0, 0}, "player-sprite.png");

    // Initial acceleration must be zero
    REQUIRE(spaceship.getAcceleration() == Vector2f(0, 0));
    // Set new acceleration
    Vector2f new_acceleration(10, 20);
    spaceship.setAcceleration(new_acceleration);
    // Spaceship acceleration must be what it was updated to
    REQUIRE(spaceship.getAcceleration() == new_acceleration);
}

TEST_CASE("can update spaceship velocity using acceleration", "[spaceship]")
{
    auto window = sf::RenderWindow();
    Spaceship spaceship(window, 1000, 1000, 0, {0, 0}, {0, 0}, "player-sprite.png");
    float delta_time = 10;

    // Initial velocity and acceleration must be zero
    REQUIRE(spaceship.getVelocity() == Vector2f(0, 0));
    REQUIRE(spaceship.getAcceleration() == Vector2f(0, 0));

    SECTION("positive acceleration works")
    {
        Vector2f new_acceleration(10, 20);
        spaceship.setAcceleration(new_acceleration);
        REQUIRE(spaceship.getAcceleration() == new_acceleration);
        // Run spaceship update method - must update velocity using acceleration
        spaceship.update(delta_time);
        REQUIRE(spaceship.getVelocity() == new_acceleration * delta_time);
    }

    SECTION("negative acceleration works")
    {
        Vector2f new_acceleration(-10, -20);
        spaceship.setAcceleration(new_acceleration);
        REQUIRE(spaceship.getAcceleration() == new_acceleration);
        // Run spaceship update method - must update velocity using acceleration
        spaceship.update(delta_time);
        REQUIRE(spaceship.getVelocity() == new_acceleration * delta_time);
    }

    SECTION("mixed sign acceleration works")
    {
        Vector2f new_acceleration(-10, 20);
        spaceship.setAcceleration(new_acceleration);
        REQUIRE(spaceship.getAcceleration() == new_acceleration);
        // Run spaceship update method - must update velocity using acceleration
        spaceship.update(delta_time);
        REQUIRE(spaceship.getVelocity() == new_acceleration * delta_time);
    }
}

TEST_CASE("setting spaceship velocity respects limits", "[spaceship]")
{
    auto window = sf::RenderWindow();
    float max_speed = 30;
    Spaceship spaceship(window, max_speed, 0, 0, {0, 0}, {0, 0}, "player-sprite.png");

    // Set new velocity
    Vector2f new_velocity(200, 300);
    spaceship.setVelocity(new_velocity);
    // Velocity must have been set in the same direction as the new velocity with magnitude max_speed
    REQUIRE(spaceship.getVelocity() == new_velocity.norm() * max_speed);
}

TEST_CASE("setting spaceship acceleration respects limits", "[spaceship]")
{
    auto window = sf::RenderWindow();
    float max_acceleration = 30;
    Spaceship spaceship(window, 0, max_acceleration, 0, {0, 0}, {0, 0}, "player-sprite.png");

    // Set new acceleration
    Vector2f new_acceleration(200, 300);
    spaceship.setAcceleration(new_acceleration);
    // Acceleration must have been set in the same direction as the new acceleration with magnitude max_acceleration
    REQUIRE(spaceship.getAcceleration() == new_acceleration.norm() * max_acceleration);
}

// NOLINTEND
