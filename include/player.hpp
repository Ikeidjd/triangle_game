#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "smooth_mover.hpp"

class Player : public sf::Drawable {
public:

	Player(std::unique_ptr<sf::Shape> shape);
	void update(float delta_time);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	inline sf::Vector2f get_position() const {
		return this->shape->getPosition();
	}

private:

	std::unique_ptr<sf::Shape> shape;
	SmoothMover smooth_mover;
	sf::Vector2f velocity;
};
