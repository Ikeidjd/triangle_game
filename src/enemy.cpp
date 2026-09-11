#include "enemy.hpp"

Enemy::Enemy(std::unique_ptr<sf::Shape> shape, std::unique_ptr<behaviors::Behavior> behavior, sf::Color color) : shape(std::move(shape)), behavior(std::move(behavior)) {
    this->shape->setOrigin(this->shape->getLocalBounds().size * 0.5f);
    this->shape->setFillColor(color);
}

void Enemy::update(float delta_time, sf::Vector2f player_pos) {
    this->behavior->execute(delta_time, *this->shape, player_pos);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*this->shape);
}
