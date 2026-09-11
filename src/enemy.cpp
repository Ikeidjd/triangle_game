#include "enemy.hpp"

Enemy::Enemy(sf::Vector2f initial_position, float width, float height, float indent_width_proportion) : shape(4), smooth_mover(900.0f, 300.0f, 300.0f), velocity(0.0f, 0.0f) {
    this->shape.setPoint(0, {width, height * 0.5f});
    this->shape.setPoint(1, {0.0f, height});
    this->shape.setPoint(2, {width * indent_width_proportion, height * 0.5f});
    this->shape.setPoint(3, {0.0f, 0.0f});

    this->shape.setOrigin(this->shape.getLocalBounds().size * 0.5f);
    this->shape.setPosition(initial_position);

    this->shape.setFillColor(sf::Color::Red);
}

void Enemy::update(float delta_time, sf::Vector2f player_pos) {
    sf::Vector2f dir = player_pos - this->shape.getPosition();
    this->smooth_mover.move(delta_time, this->shape, this->velocity, dir);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->shape);
}
