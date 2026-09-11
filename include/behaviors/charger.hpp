#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

#include "behaviors/behavior.hpp"
#include "smooth_mover.hpp"

namespace behaviors {

	class Charger : public Behavior {
	public:

		Charger(const SmoothMover& smooth_mover);
		~Charger() override;
		void execute(float delta_time, sf::Transformable& transformable, sf::Vector2f player_pos) override;

	private:

		SmoothMover smooth_mover;
		sf::Vector2f velocity;

		enum class State {
			TARGETING,
			ACCELERATING,
			DECELERATING,
		} state;
	};

}
