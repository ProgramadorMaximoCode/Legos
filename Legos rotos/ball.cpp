#include "ball.h"
#include <cmath>
#include <SFML/Graphics.hpp>


Ball::Ball(float x, float y) {
    shape.setRadius(10.f);
    shape.setOrigin({10.f, 10.f});
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition({x, y});
    speed = -200.f;
    velocity = {speed, speed};
}

void Ball::resetToCenter(const sf::RenderWindow& window)
{
    shape.setPosition({window.getSize().x / 2.f, window.getSize().y / 4.f * 3.f});
    velocity = {0.f, 0.f};
}

void Ball::positioningOverThePaddle(RectangleShape& Paddle) {
    shape.setPosition({Paddle.getPosition().x, Paddle.getPosition().y - Paddle.getSize().y / 2.f + shape.getRadius()});
}
void Ball::bounceX() {
    velocity.x = -velocity.x;
}

void Ball::bounceY() {
    velocity.y = -velocity.y;
}

void Ball::update(float dt, sf::RenderWindow& window) {
    shape.move(velocity * dt);
}


void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

const sf::CircleShape& Ball::getShape() {
    return shape;
}

sf::FloatRect Ball::getGlobalBounds() const
{
    return shape.getGlobalBounds();
}