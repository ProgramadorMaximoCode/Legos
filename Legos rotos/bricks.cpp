#include "bricks.h"

Brick::Brick(float x, float y) {
        shape.setPosition({x, y});
        shape.setSize({50.f, 20.f});
        shape.setFillColor(sf::Color::Red);
    }

void Brick::draw(sf::RenderWindow& window) {
        if (!destroyed)
            window.draw(shape);
}

void Brick::destroy() {
        destroyed = true;
    }

bool Brick::isDestroyed() const {
        return destroyed;
    }
const sf::RectangleShape& Brick::getShape() {
    return shape;
}