#include "booster.h"

Booster::Booster(float x, float y, typeBooster t) {
    type = t;

    shape.setRadius(10.f);
    shape.setOrigin({10.f, 10.f});
    shape.setPosition({x, y});

    // Color según tipo
    switch(type) {
        case typeBooster::Life: shape.setFillColor(sf::Color::Cyan); break;
        case typeBooster::BiggerPaddle: shape.setFillColor(sf::Color::Green); break;
        case typeBooster::FastPaddle: shape.setFillColor(sf::Color::Blue); break;
        case typeBooster::SlowerPaddle: shape.setFillColor(sf::Color::Red); break;
        case typeBooster::SmallerPaddle: shape.setFillColor(sf::Color::Yellow); break;
    }

    speed = 200.f;
    velocity = {0.f, speed};
}
void Booster::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
const sf::CircleShape& Booster::getShape() {
    return shape;
}
void Booster::update(float dt) {
    shape.move(velocity * dt);
}

void Booster::setPosition(float new_x, float new_y) {
    shape.setPosition({new_x, new_y});
}
void Booster::setColor(sf::Color color) {
    shape.setFillColor(color);
}