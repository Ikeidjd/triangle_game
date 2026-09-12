#include "world.hpp"

#include <cmath>
#include <random>

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

    this->randomize_background_color();
    this->randomize_background_color();
}

void World::update(float delta_time, const sf::RenderWindow& window) {
    this->mouse_world_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    this->update_background_color(delta_time);

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
    window.clear(this->background_color);
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
    return this->mouse_buttons_pressed.contains(button);
}

void World::summon(Enemy&& enemy) {
    this->enemies.push_back(std::move(enemy));
}

void World::shoot(Bullet&& bullet) {
    this->bullets.push_back(std::move(bullet));
}

void World::randomize_background_color() {
    this->background_color_from = this->background_color_to;
    this->background_color = this->background_color_to;
    this->background_color_percent = 0.0f;

    std::mt19937 a(std::time(NULL));
    this->background_color_to = sf::Color(a(), a(), a());
}

void World::update_background_color(float delta_time) {
    this->background_color.r = std::lerp(this->background_color_from.r, this->background_color_to.r, this->background_color_percent);
    this->background_color.g = std::lerp(this->background_color_from.g, this->background_color_to.g, this->background_color_percent);
    this->background_color.b = std::lerp(this->background_color_from.b, this->background_color_to.b, this->background_color_percent);

    this->background_color_percent += 0.5f * delta_time;

    if (this->background_color_percent >= 1.0f) {
        this->randomize_background_color();
    }
}
