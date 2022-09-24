#include "./Enemy.hpp"

float Enemy::getHealth() const {
    return this->_health;
}

bool Enemy::removeHealth(float health_to_remove) {
    this->_health -= health_to_remove;
    return this->_health > 0;
}
