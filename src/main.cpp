#include <iostream>

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
public:

	Player(sf::Vector2f window_size, float width, float height, float indent_width_proportion) : shape(4), velocity(0.0f, 0.0f) {
		this->shape.setPoint(0, {width, height * 0.5f});
		this->shape.setPoint(1, {0.0f, height});
		this->shape.setPoint(2, {width * indent_width_proportion, height * 0.5f});
		this->shape.setPoint(3, {0.0f, 0.0f});

		this->shape.setOrigin(this->shape.getLocalBounds().size * 0.5f);
		this->shape.setPosition(window_size * 0.5f);
	}

	void update(float delta_time) {
		sf::Vector2f dir;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
			dir.y--;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
			dir.x--;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
			dir.y++;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
			dir.x++;
		}

		if (dir != sf::Vector2f(0.0f, 0.0f)) {
			this->velocity += dir.normalized() * this->acceleration * delta_time;
		} else if (this->velocity != sf::Vector2f(0.0f, 0.0f)) {
			auto old_vel = this->velocity;
			this->velocity -= this->velocity.normalized() * this->dampening * delta_time;

			// If signs are different
			if ((this->velocity.x > 0.0f) != (old_vel.x > 0.0f)) {
				this->velocity = sf::Vector2f(0.0f, 0.0f);
			}
		}

		if (this->velocity != sf::Vector2f(0.0f, 0.0f)) {
			if (this->velocity.length() > this->max_speed) {
				this->velocity = this->velocity.normalized() * this->max_speed;
			}

			this->shape.setRotation(this->velocity.angle());
			this->shape.move(this->velocity * delta_time);
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->shape);
	}

private:

	static constexpr float acceleration = 600.0f;
	static constexpr float dampening = 300.0f;
	static constexpr float max_speed = 300.0f;

	sf::ConvexShape shape;
	sf::Vector2f velocity;
};

int main() {
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode({600, 600}), "First window!", sf::State::Windowed, settings);
	sf::Clock clock;
	clock.start();

	Player player(static_cast<sf::Vector2f>(window.getSize()), 40, 40, 0.25);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		float delta_time = clock.restart().asSeconds();

		player.update(delta_time);

		window.clear();

		window.draw(player);

		window.display();
	}
}
