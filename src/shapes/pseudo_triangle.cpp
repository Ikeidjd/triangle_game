#include "shapes/pseudo_triangle.hpp"

namespace shapes {

    PseudoTriangle::PseudoTriangle(sf::Vector2f initial_position, float width, float height, float indent_width_proportion) : sf::ConvexShape(4) {
        this->setPoint(0, {width, height * 0.5f});
        this->setPoint(1, {0.0f, height});
        this->setPoint(2, {width * indent_width_proportion, height * 0.5f});
        this->setPoint(3, {0.0f, 0.0f});

        this->setPosition(initial_position);
    }

}
