#include "paddle.h"
#include <SFML/Graphics.hpp>

Paddle::Paddle(float x, float y) {
    shape.setSize({150, 20});
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition({x, y});
}

void Paddle::moveRight(float dt) {
    shape.move({speed * dt, 0});
}
void Paddle::moveLeft(float dt) {
    shape.move({-speed * dt, 0});
}


const sf::RectangleShape& Paddle::getShape() {
    return shape;
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
sf::FloatRect Paddle::getGlobalBounds() const
{
    return shape.getGlobalBounds();
}