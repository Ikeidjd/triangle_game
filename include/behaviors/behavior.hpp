#pragma once

namespace behaviors {

    class Behavior {
    public:

        virtual ~Behavior() = default;
        virtual void execute(float delta_time, sf::Transformable& transformable, sf::Vector2f player_pos) = 0;
    };

}
