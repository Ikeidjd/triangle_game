#include <iostream>

#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "enemy.hpp"

int main() {
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode({600, 600}), "TRIANGLE GAME", sf::State::Windowed, settings);
	sf::Clock clock;
	clock.start();

	Player player(static_cast<sf::Vector2f>(window.getSize()) * 0.5f, 40, 40, 0.25);
	Enemy enemy({0.0f, 0.0f}, 30, 30, 0.25);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		float delta_time = clock.restart().asSeconds();

		player.update(delta_time);
		enemy.update(delta_time, player.get_position());

		window.clear();

		window.draw(player);
		window.draw(enemy);

		window.display();
	}
}
