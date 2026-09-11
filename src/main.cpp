#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "shapes/pseudo_triangle.hpp"
#include "behaviors/chaser.hpp"
#include "behaviors/charger.hpp"
#include "player.hpp"
#include "enemy.hpp"

int main() {
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode({900, 900}), "TRIANGLE GAME", sf::State::Windowed, settings);
	sf::Clock clock;
	clock.start();

	Player player(std::make_unique<shapes::PseudoTriangle>(static_cast<sf::Vector2f>(window.getSize()) * 0.5f, 40, 40, 0.25));

	Enemy chaser(
		std::make_unique<shapes::PseudoTriangle>(sf::Vector2f(), 30, 30, 0.25),
		std::make_unique<behaviors::Chaser>(SmoothMover(900.0f, 300.0f, 300.0f)),
		sf::Color::Red
	);

	Enemy charger(
		std::make_unique<sf::CircleShape>(16.0f),
		std::make_unique<behaviors::Charger>(SmoothMover(2200.0f, 800.0f, 800.0f)),
		sf::Color::Blue
	);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		float delta_time = clock.restart().asSeconds();

		player.update(delta_time);
		chaser.update(delta_time, player.get_position());
		charger.update(delta_time, player.get_position());

		window.clear();

		window.draw(player);
		window.draw(chaser);
		window.draw(charger);

		window.display();
	}
}
