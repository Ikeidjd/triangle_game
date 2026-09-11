#pragma once

#include <SFML/Graphics.hpp>

#include "behaviors/behavior.hpp"
#include "smooth_mover.hpp"

namespace behaviors {

	class Chaser : public Behavior {
	public:

		Chaser(const SmoothMover& smooth_mover);
		~Chaser() override;
		void execute(float delta_time, sf::Transformable& transformable, sf::Vector2f player_pos) override;

	private:

		SmoothMover smooth_mover;
		sf::Vector2f velocity;
	};

}
