#pragma once

#include <SFML/Graphics.hpp>

class SmoothMover {
public:

    SmoothMover(float acceleration, float dampening, float max_speed);
    void move(float delta_time, sf::Transformable& transformable, sf::Vector2f& velocity, sf::Vector2f dir);

private:

	float acceleration;
	float dampening;
	float max_speed;
};
