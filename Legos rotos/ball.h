#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Ball {
    private:
        sf::CircleShape shape;
        sf::Vector2f velocity;
        float speed;

    public:
        Ball(float x, float y);

        void bounceFromPaddle(float relative);
        void bounceX();
        void bounceY();
        void update(float dt, RenderWindow& window);
        void draw(RenderWindow& window);

        const CircleShape& getShape();
        void resetToCenter(const sf::RenderWindow& window);
        sf::FloatRect getGlobalBounds() const;
        void setPosition(sf::Vector2f pos) { shape.setPosition(pos); }
        sf::Vector2f getPosition() const { return shape.getPosition(); }
        float getRadius() const { return shape.getRadius(); }
};