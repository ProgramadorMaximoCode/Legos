#include "ball.h"
#include <cmath>
#include <SFML/Graphics.hpp>


Ball::Ball(float x, float y) {
    shape.setRadius(10.f);
    shape.setOrigin({10.f, 10.f});
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition({x, y});
    speed = 200.f;
    velocity = {speed, speed};
}

void Ball::resetToCenter(const sf::RenderWindow& window)
{
    shape.setPosition({window.getSize().x / 2.f, window.getSize().y / 2.f});
    velocity = {0.f, 0.f};
}

void Ball::bounceFromPaddle(float relative) {

    float maxAngle = 60.f;
    float angle = relative * maxAngle;

    float rad = angle * 3.14159f / 180.f;

    velocity.x = speed * std::cos(rad);
    velocity.y = -speed * std::sin(rad);
}

void Ball::bounceX() {
    velocity.x = -velocity.x;
}

void Ball::bounceY() {
    velocity.y = -velocity.y;
}

void Ball::update(float dt, sf::RenderWindow& window) {
    shape.move(velocity * dt);

    float top = shape.getPosition().y - shape.getRadius();
    float bottom = shape.getPosition().y + shape.getRadius();

    if (top <= 0.f || bottom >= window.getSize().y)
    {
        bounceY();
    }
    if (shape.getPosition().x - shape.getRadius() <= 0.f || shape.getPosition().x + shape.getRadius() >= window.getSize().x)
    {
        bounceX();
    }
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