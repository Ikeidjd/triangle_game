#pragma once

#include <SFML/Graphics.hpp>

#include "smooth_mover.hpp"

class Player : public sf::Drawable {
public:

	Player(sf::Vector2f initial_position, float width, float height, float indent_width_proportion);
	void update(float delta_time);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f get_position() const;

private:

	sf::ConvexShape shape;
	SmoothMover smooth_mover;
	sf::Vector2f velocity;
};
