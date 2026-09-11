#include "behaviors/charger.hpp"

namespace behaviors {

    Charger::Charger(const SmoothMover& smooth_mover) : smooth_mover(smooth_mover), velocity(), state(State::TARGETING) {}

    Charger::~Charger() = default;

    void Charger::execute(float delta_time, sf::Transformable& transformable, sf::Vector2f player_pos) {
        switch (this->state) {
			case State::TARGETING: {
                transformable.setRotation((player_pos - transformable.getPosition()).angle());
                this->state = State::ACCELERATING;
            } break;
			case State::ACCELERATING: {
                this->smooth_mover.move(delta_time, transformable, this->velocity, sf::Vector2f(1.0f, transformable.getRotation()));

                if (std::abs(this->velocity.length() - this->smooth_mover.get_max_speed()) <= 1.0f) {
                    this->state = State::DECELERATING;
                }
            } break;
			case State::DECELERATING: {
                this->smooth_mover.move(delta_time, transformable, this->velocity, {0.0f, 0.0f});

                if (this->velocity == sf::Vector2f(0.0f, 0.0f)) {
                    this->state = State::TARGETING;
                }
            } break;
        }
    }

}
