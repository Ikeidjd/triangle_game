#include "behaviors/chaser.hpp"

namespace behaviors {

    Chaser::Chaser(const SmoothMover& smooth_mover) : smooth_mover(smooth_mover), velocity() {}

    Chaser::~Chaser() = default;

    void Chaser::execute(float delta_time, sf::Transformable& transformable, sf::Vector2f player_pos) {
        sf::Vector2f dir = player_pos - transformable.getPosition();
        this->smooth_mover.move(delta_time, transformable, this->velocity, dir);
    }

}
