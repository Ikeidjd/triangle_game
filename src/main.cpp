#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "world.hpp"

int main() {
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode({900, 900}), "TRIANGLE GAME", sf::State::Windowed, settings);
	sf::Clock clock;
	clock.start();

	World world(window);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} else if(const auto event2 = event->getIf<sf::Event::MouseButtonPressed>()) {
				world.press_mouse_button(event2->button);
			}
		}

		float delta_time = clock.restart().asSeconds();
		world.update(delta_time, window);

		window.clear();
		world.draw(window);
		window.display();
	}
}
