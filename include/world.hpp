#pragma once

#include <vector>
#include <unordered_set>

#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "enemy.hpp"
#include "bullet.hpp"

class World {
public:

    World(const sf::RenderWindow& window);
    void update(float delta_time, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

    void summon(Enemy&& enemy);
    void shoot(Bullet&& bullet);

    void press_mouse_button(sf::Mouse::Button button);
    bool is_mouse_button_just_pressed(sf::Mouse::Button button);

    inline const Player& get_player() const {
        return this->player;
    }

    inline const std::vector<Enemy>& get_enemies() const {
        return this->enemies;
    }

    inline const std::vector<Bullet>& get_bullets() const {
        return this->bullets;
    }

    inline sf::Vector2f get_mouse_world_coords() const {
        return this->mouse_world_coords;
    }

private:

    std::unordered_set<sf::Mouse::Button> mouse_buttons_pressed;
    sf::Vector2f mouse_world_coords;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;

    sf::Color background_color;
    sf::Color background_color_from;
    sf::Color background_color_to;
    float background_color_percent;

    void randomize_background_color();
    void update_background_color(float delta_time);
};
