#include "paddle.h"
#include <SFML/Graphics.hpp>

Paddle::Paddle(float x, float y) {
    shape.setSize({100, 10});
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

void Paddle::increaseSize() {
    shape.setSize({120, shape.getSize().y});
}

void Paddle::increaseSpeed() {
    speed = 400.f;
}
void Paddle::decreaseSpeed() {
    speed = 200.f;
}
void Paddle::decreaseSize() {
    shape.setSize({80, shape.getSize().y});
}

void Paddle::setNormal() {
    shape.setSize({100, shape.getSize().y});
    speed = 300.f;
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