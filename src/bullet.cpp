#include "bullet.hpp"

#include "world.hpp"

Bullet::Bullet(float radius, sf::Vector2f from, sf::Vector2f towards, float speed) : sf::CircleShape(radius), velocity((towards - from).normalized() * speed) {
    this->setOrigin(this->getLocalBounds().size * 0.5f);
    this->setPosition(from);
}

void Bullet::update(float delta_time, const World& world) {
    this->move(this->velocity * delta_time);
}
