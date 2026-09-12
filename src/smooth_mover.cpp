#include "smooth_mover.hpp"

SmoothMover::SmoothMover(float acceleration, float dampening, float max_speed) : acceleration(acceleration), dampening(dampening), max_speed(max_speed) {}

void SmoothMover::move(float delta_time, sf::Transformable& transformable, sf::Vector2f& velocity, sf::Vector2f dir) {
    if (dir != sf::Vector2f(0.0f, 0.0f)) {
        // Normally, when the character turns around, it accelerates towards the new direction, creating a smooth rotation
        // If the character's velocity is 0, though, this rotation happens instantly, which looks pretty bad
        // This check fixes that (unless the character is turning exactly to the complete opposite direction)
        if (velocity == sf::Vector2f(0.0f, 0.0f)) {
            velocity = sf::Vector2f(this->max_speed * 0.1f, transformable.getRotation());
        }

        velocity += dir.normalized() * this->acceleration * delta_time;
    } else if (velocity != sf::Vector2f(0.0f, 0.0f)) {
        sf::Vector2f old_velocity = velocity;
        velocity -= velocity.normalized() * this->dampening * delta_time;

        // If the signs are different, we force it to 0, since it would just turn around randomly if we didn't
        // Checking only x would work except when moving perfectly vertically
        // Checking only y would work except when moving perfectly horizontally
        if ((velocity.x > 0.0f) != (old_velocity.x > 0.0f) || (velocity.y > 0.0f) != (old_velocity.y > 0.0f)) {
            velocity = sf::Vector2f(0.0f, 0.0f);
        }
    }

    if (velocity != sf::Vector2f(0.0f, 0.0f)) {
        if (velocity.length() > this->max_speed) {
            velocity = velocity.normalized() * this->max_speed;
        }

        transformable.setRotation(velocity.angle());
        transformable.move(velocity * delta_time);
    }
}
