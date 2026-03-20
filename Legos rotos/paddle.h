#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
    private:
        sf::RectangleShape shape;
        float speed = 300.f;

    public:
        Paddle(float x, float y);

        void moveRight(float dt);
        void moveLeft(float dt);
        void setPosition(sf::Vector2f pos) { shape.setPosition(pos); }
        void draw(sf::RenderWindow& window);
        const sf::RectangleShape& getShape();
        sf::FloatRect getGlobalBounds() const;
};