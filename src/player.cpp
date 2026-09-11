#include "player.hpp"

Player::Player(std::unique_ptr<sf::Shape> shape) : shape(std::move(shape)), smooth_mover(600.0f, 300.0f, 300.0f), velocity(0.0f, 0.0f) {}

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

    this->smooth_mover.move(delta_time, *this->shape, this->velocity, dir);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*this->shape);
}
