#include "world.hpp"

#include <algorithm>

#include "shapes/pseudo_triangle.hpp"
#include "behaviors/chaser.hpp"
#include "behaviors/charger.hpp"

World::World(const sf::RenderWindow& window) : player(std::make_unique<shapes::PseudoTriangle>(static_cast<sf::Vector2f>(window.getSize()) * 0.5f, 40, 40, 0.25)) {
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

    this->summon(std::move(chaser));
    this->summon(std::move(charger));
}

void World::update(float delta_time, const sf::RenderWindow& window) {
    this->mouse_world_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    this->player.update(delta_time, *this);

    for (Enemy& enemy : this->enemies) {
        enemy.update(delta_time, *this);
    }

    for (Bullet& bullet : this->bullets) {
        bullet.update(delta_time, *this);
    }

    this->mouse_buttons_pressed.clear();
}

void World::draw(sf::RenderWindow& window) const {
    window.draw(this->player);

    for (const Enemy& enemy : this->enemies) {
        window.draw(enemy);
    }

    for (const Bullet& bullet : this->bullets) {
        window.draw(bullet);
    }
}

void World::press_mouse_button(sf::Mouse::Button button) {
    this->mouse_buttons_pressed.insert(button);
}

bool World::is_mouse_button_just_pressed(sf::Mouse::Button button) {
    return this->mouse_buttons_pressed.find(button) != this->mouse_buttons_pressed.end();
}

void World::summon(Enemy&& enemy) {
    this->enemies.push_back(std::move(enemy));
}

void World::shoot(Bullet&& bullet) {
    this->bullets.push_back(std::move(bullet));
}
