#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "behaviors/behavior.hpp"

class Enemy : public sf::Drawable {
public:

    Enemy(std::unique_ptr<sf::Shape> shape, std::unique_ptr<behaviors::Behavior> behavior, sf::Color color);
    void update(float delta_time, sf::Vector2f player_pos);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    std::unique_ptr<sf::Shape> shape;
    std::unique_ptr<behaviors::Behavior> behavior;
};
