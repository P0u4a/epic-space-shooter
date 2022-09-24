#include "./Spaceship.hpp"
#include <algorithm>
#include "util/Vector.hpp"

void Spaceship::setVelocity(const Vector2f &new_velocity) {
    this->velocity.setWithCappedMagnitude(new_velocity, this->max_speed);
}

void Spaceship::setAcceleration(const Vector2f &new_acceleration) {
    this->acceleration.setWithCappedMagnitude(new_acceleration, this->max_acceleration);
}
