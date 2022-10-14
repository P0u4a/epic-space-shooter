// #include "util/Vector.hpp"
#include "../../src/util/Vector.hpp"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <cmath>
#include <stdexcept>

// NOLINTBEGIN

using namespace Catch;

TEST_CASE("vector components can be reassigned", "[vector]")
{
    Vector2f vector;

    // Vector must be initialised to {0, 0}
    REQUIRE(vector.x == 0);
    REQUIRE(vector.y == 0);

    int new_x = 10;
    int new_y = 20;

    vector.x = new_x;
    vector.y = new_y;

    // Vector components must have been updated
    REQUIRE(vector.x == new_x);
    REQUIRE(vector.y == new_y);
}

TEST_CASE("vectors can be multiplied by scalars", "[vector]")
{
    SECTION("multiplying by positive scalars works")
    {
        REQUIRE(Vector2f(1, 1) * 10 == Vector2f(10, 10));
        REQUIRE(Vector2f(1, 1) * 1 == Vector2f(1, 1));
        REQUIRE(Vector2f(10, 10) * 10 == Vector2f(100, 100));
    }

    SECTION("multiplying by negative scalars works")
    {
        REQUIRE(Vector2f(1, 1) * -1 == Vector2f(-1, -1));
        REQUIRE(Vector2f(-1, -1) * -1 == Vector2f(1, 1));
        REQUIRE(Vector2f(10, -10) * -10 == Vector2f(-100, 100));
    }

    SECTION("multiplying by 0 works")
    {
        REQUIRE(Vector2f(1, 1) * 0 == Vector2f(0, 0));
        REQUIRE(Vector2f(0, 0) * 1 == Vector2f(0, 0));
        REQUIRE(Vector2f(-1, -1) * 0 == Vector2f(0, 0));
    }

    SECTION("multiplication is commutative")
    {
        REQUIRE(Vector2f(1, 1) * 10 == 10 * Vector2f(1, 1));
        REQUIRE(Vector2f(-10, 10) * -1 == -1 * Vector2f(-10, 10));
        REQUIRE(Vector2f(1, 1) * 0 == 0 * Vector2f(1, 1));
    }
}

TEST_CASE("vectors can be added", "[vector]")
{
    SECTION("positive vectors can be added")
    {
        REQUIRE(Vector2f(1, 1) + Vector2f(1, 1) == Vector2f(2, 2));
        REQUIRE(Vector2f(10, 20) + Vector2f(10, 20) == Vector2f(20, 40));
    }

    SECTION("negative vectors can be added")
    {
        REQUIRE(Vector2f(-1, -1) + Vector2f(-1, -1) == Vector2f(-2, -2));
        REQUIRE(Vector2f(-10, -20) + Vector2f(-10, -20) == Vector2f(-20, -40));
    }

    SECTION("mixed sign vectors can be added")
    {
        REQUIRE(Vector2f(-1, -1) + Vector2f(1, 1) == Vector2f(0, 0));
        REQUIRE(Vector2f(10, -10) + Vector2f(-10, 10) == Vector2f(0, 0));
        REQUIRE(Vector2f(100, -50) + Vector2f(1, -1) == Vector2f(101, -51));
    }

    SECTION("adding 0 vectors works")
    {
        REQUIRE(Vector2f(1, 1) + Vector2f(0, 0) == Vector2f(1, 1));
        REQUIRE(Vector2f(10, -10) + Vector2f(0, 0) == Vector2f(10, -10));
        REQUIRE(Vector2f(0, 0) + Vector2f(0, 0) == Vector2f(0, 0));
    }

    SECTION("addition is commutative")
    {
        REQUIRE(Vector2f(1, 1) + Vector2f(2, 2) == Vector2f(2, 2) + Vector2f(1, 1));
        REQUIRE(Vector2f(-10, -20) + Vector2f(10, 20) == Vector2f(10, 20) + Vector2f(-10, -20));
        REQUIRE(Vector2f(1, 1) + Vector2f(0, 0) == Vector2f(0, 0) + Vector2f(1, 1));
    }
}

TEST_CASE("vectors can be normalised", "[vector]")
{
    Vector2f vector;

    SECTION("positive vector must be normalisable")
    {
        vector.set({1, 1});
        REQUIRE(vector.norm().magnitude() == Approx(1));
        REQUIRE(vector.norm().x == Approx(1 / std::sqrt(2)));
        REQUIRE(vector.norm().y == Approx(1 / std::sqrt(2)));
    }

    SECTION("negative vector must be normalisable")
    {
        vector.set({-1, -1});
        REQUIRE(vector.norm().magnitude() == Approx(1));
        REQUIRE(vector.norm().x == Approx(-1 / std::sqrt(2)));
        REQUIRE(vector.norm().y == Approx(-1 / std::sqrt(2)));
    }

    SECTION("zero vector must not be normalisable")
    {
        vector.set({0, 0});
        REQUIRE_THROWS_AS(vector.norm(), std::runtime_error);
        REQUIRE_THROWS_WITH(vector.norm(), "Attempted to normalise zero vector");
    }
}

TEST_CASE("vectors can calculate the absolute value of their components", "[vector]")
{
    SECTION("positive vectors must remain positive")
    {
        REQUIRE(Vector2f(1, 1).abs() == Vector2f(1, 1));
        REQUIRE(Vector2f(10, 20).abs() == Vector2f(10, 20));
    }

    SECTION("negative vectors must become positive")
    {
        REQUIRE(Vector2f(-1, -1).abs() == Vector2f(1, 1));
        REQUIRE(Vector2f(-10, -20).abs() == Vector2f(10, 20));
    }

    SECTION("mixed sign vectors must become positive")
    {
        REQUIRE(Vector2f(1, -1).abs() == Vector2f(1, 1));
        REQUIRE(Vector2f(-10, 20).abs() == Vector2f(10, 20));
    }
}

TEST_CASE("vectors can be set to a new vector", "[vector]")
{
    Vector2f vector = {0, 0};

    // Positive vector must be settable
    SECTION("positive vector must be settable")
    {
        vector.set({1, 1});
        REQUIRE(vector == Vector2f(1, 1));
    }

    SECTION("zero vector must be settable")
    {
        vector.set({0, 0});
        REQUIRE(vector == Vector2f(0, 0));
    }

    SECTION("negative vector must be settable")
    {
        vector.set({-10, -10});
        REQUIRE(vector == Vector2f(-10, -10));
    }
}

TEST_CASE("vectors can be set to a new vector with a capped magnitude", "[vector]")
{
    Vector2f vector = {0, 0};

    SECTION("setting to a vector with less than max magnitude works")
    {
        vector.setWithCappedMagnitude({1, 1}, 10);
        REQUIRE(vector == Vector2f(1, 1));

        vector.setWithCappedMagnitude({10, 20}, 100);
        REQUIRE(vector == Vector2f(10, 20));

        vector.setWithCappedMagnitude({-5, -10}, 10);
        REQUIRE(vector == Vector2f(-5, -10) * (2 / std::sqrt(5)));
    }

    SECTION("setting to a vector above the max magnitude works")
    {
        vector.setWithCappedMagnitude({1, 1}, 1);
        REQUIRE(vector.x == Approx(1 / std::sqrt(2)));
        REQUIRE(vector.y == Approx(1 / std::sqrt(2)));

        vector.setWithCappedMagnitude({10, 20}, 10);
        REQUIRE(vector.x == Approx(10 / std::sqrt(5)));
        REQUIRE(vector.y == Approx(20 / std::sqrt(5)));

        vector.setWithCappedMagnitude({-10, -20}, 10);
        REQUIRE(vector.x == Approx(-10 / std::sqrt(5)));
        REQUIRE(vector.y == Approx(-20 / std::sqrt(5)));
    }
}

TEST_CASE("vectors can calculate their magnitude", "[vector]")
{
    Vector2f vector;

    SECTION("0 vector will have 0 magnitude")
    {
        vector = {0, 0};
        REQUIRE(vector.magnitude() == 0);
    }

    SECTION("positive vectors will have a positive magnitude")
    {
        vector = {1, 1};
        REQUIRE(vector.magnitude() > 0.0F);
    }

    SECTION("negative vectors will have a positive magnitude")
    {
        vector = {-1, -1};
        REQUIRE(vector.magnitude() > 0.0F);
    }

    SECTION("mixed sign vectors will have a positive magnitude")
    {
        vector = {1, -1};
        REQUIRE(vector.magnitude() > 0.0F);
    }

    SECTION("magnitude should be correct")
    {
        vector = {1, 1};
        REQUIRE(vector.magnitude() == Approx(std::sqrt(2)));
        vector = Vector2f(1 / std::sqrt(2), 1 / std::sqrt(2));
        REQUIRE(vector.magnitude() == Approx(1));
        vector = {3, 4};
        REQUIRE(vector.magnitude() == Approx(5));
    }
}

// NOLINTEND
