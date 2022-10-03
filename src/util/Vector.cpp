#include "./Vector.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "./Math.hpp"

float Vector2f::magnitude() const {
    return std::sqrt((this->x * this->x) + (this->y * this->y));
}

void Vector2f::set(const Vector2f &new_vector) {
    this->x = new_vector.x;
    this->y = new_vector.y;
}

void Vector2f::setWithCappedMagnitude(const Vector2f &new_vector, float max_magnitude) {
    // Cap the magnitude of the vector
    if (new_vector.magnitude() > max_magnitude)
        // Set the vector to new_vector, normalising its magnitude then multiplying by the maximum magnitude
        this->set((max_magnitude * Math::Q_rsqrt((new_vector.x * new_vector.x) + (new_vector.y * new_vector.y)) * new_vector));

    // Set the vector to the new vector - no need to modify magnitude less than max
    else
        this->set(new_vector);
}

Vector2f operator*(const Vector2f &left, float right) {
    return {left.x * right, left.y * right};
}

Vector2f operator*(float left, const Vector2f &right) {
    return {right.x * left, right.y * left};
}
