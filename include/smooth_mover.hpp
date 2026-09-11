#pragma once

#include <SFML/Graphics.hpp>

class SmoothMover {
public:

    SmoothMover(float acceleration, float dampening, float max_speed);
    void move(float delta_time, sf::Transformable& transformable, sf::Vector2f& velocity, sf::Vector2f dir);

	inline float get_acceleration() const {
		return acceleration;
	}

	inline float get_dampening() const {
		return dampening;
	}

	inline float get_max_speed() const {
		return max_speed;
	}

private:

	float acceleration;
	float dampening;
	float max_speed;
};
