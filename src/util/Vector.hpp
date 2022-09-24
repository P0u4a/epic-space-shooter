#ifndef SRC_UTIL_VECTOR_HPP
#define SRC_UTIL_VECTOR_HPP

#include <SFML/System/Vector2.hpp>

/**
 * @brief 2-dimensional vector with x and y componenets as floats
 */
class Vector2f : public sf::Vector2f {
  public:
    Vector2f(float x, float y) : sf::Vector2f(x, y){};

    /**
     * @brief Get the magnitude of the vector
     *
     * @return The magnitude of the vector
     */
    [[nodiscard]] float magnitude() const;

    /**
     * @brief Set the vector to a new vector
     *
     * @param new_vector The new vector to set to this vector
     */
    void set(const Vector2f &new_vector);

    /**
     * @brief Set vector to a new vector, capping length of the vector to a maximum magnitude
     *
     * @param new_vector The new vector to set to this vector
     * @param max_magnitude The max magnitude to set this vector to. If the magnitude of
     * new_vector is greater than that of max_magnitude, its magnitude will be set to max_magnitude
     */
    void setWithCappedMagnitude(const Vector2f &new_vector, float max_magnitude);

    /**
     * @brief Multiply vector by a scalar
     *
     * @param scalar Scalar to multiply by
     * @return The multiplied vector
     */
    Vector2f operator*(float scalar);
};

/**
 * @brief Multiplication operator overload
 *
 * @param left The vector to multiply
 * @param right The scalar to multiply the vector by
 * @return The multiplied vector
 */
Vector2f operator*(const Vector2f &left, float right);

/**
 * @brief Multiplication operator overload
 *
 * @param left The scalar to multiply the vector by
 * @param right The vector to multiply
 * @return The multiplied vector
 */
Vector2f operator*(float left, const Vector2f &right);

#endif // SRC_UTIL_VECTOR_HPP
