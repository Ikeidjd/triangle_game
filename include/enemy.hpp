#pragma once

#include <SFML/Graphics.hpp>

#include "smooth_mover.hpp"

class Enemy : public sf::Drawable {
public:

	Enemy(sf::Vector2f initial_position, float width, float height, float indent_width_proportion);
	void update(float delta_time, sf::Vector2f player_pos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	sf::ConvexShape shape;
	SmoothMover smooth_mover;
	sf::Vector2f velocity;
};
