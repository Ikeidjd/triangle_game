#include "player.hpp"

#include "world.hpp"

Player::Player(std::unique_ptr<sf::Shape> shape) : shape(std::move(shape)), smooth_mover(600.0f, 300.0f, 300.0f), velocity(0.0f, 0.0f) {
    this->shape->setOrigin(this->shape->getLocalBounds().size * 0.5f);
}

void Player::update(float delta_time, World& world) {
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

    if (world.is_mouse_button_just_pressed(sf::Mouse::Button::Left)) {
        world.shoot(Bullet(10.0f, this->get_position(), world.get_mouse_world_coords(), this->smooth_mover.get_max_speed()));
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*this->shape);
}
