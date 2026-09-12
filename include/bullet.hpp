#pragma once

#include <SFML/Graphics.hpp>

class World;

class Bullet : public sf::CircleShape {
public:

    Bullet(float radius, sf::Vector2f from, sf::Vector2f towards, float speed);
    void update(float delta_time, const World& world);

private:

    sf::Vector2f velocity;
};
