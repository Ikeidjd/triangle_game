#include "world.hpp"

#include <algorithm>

#include "shapes/pseudo_triangle.hpp"

World::World(const sf::RenderWindow& window) : player(std::make_unique<shapes::PseudoTriangle>(static_cast<sf::Vector2f>(window.getSize()) * 0.5f, 40, 40, 0.25)) {}

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
