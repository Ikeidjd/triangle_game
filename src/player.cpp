#include "player.hpp"

Player::Player(sf::Vector2f initial_position, float width, float height, float indent_width_proportion) : shape(4), smooth_mover(600.0f, 300.0f, 300.0f), velocity(0.0f, 0.0f) {
    this->shape.setPoint(0, {width, height * 0.5f});
    this->shape.setPoint(1, {0.0f, height});
    this->shape.setPoint(2, {width * indent_width_proportion, height * 0.5f});
    this->shape.setPoint(3, {0.0f, 0.0f});

    this->shape.setOrigin(this->shape.getLocalBounds().size * 0.5f);
    this->shape.setPosition(initial_position);
}

void Player::update(float delta_time) {
    sf::Vector2f dir;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
        dir.y--;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        dir.x--;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
        dir.y++;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        dir.x++;
    }

    this->smooth_mover.move(delta_time, this->shape, this->velocity, dir);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->shape);
}

sf::Vector2f Player::get_position() const {
    return this->shape.getPosition();
}
