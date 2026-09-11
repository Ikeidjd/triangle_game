#pragma once

#include <SFML/Graphics.hpp>

namespace shapes {

    class PseudoTriangle : public sf::ConvexShape {
    public:

        PseudoTriangle(sf::Vector2f initial_position, float width, float height, float indent_width_proportion);
    };

}
