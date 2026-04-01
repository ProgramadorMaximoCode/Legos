#pragma once
#include <SFML/Graphics.hpp>

class Booster {
    public:
        enum typeBooster {
            Life,
            BiggerPaddle,
            FastPaddle,
            SlowerPaddle,
            SmallerPaddle,

        };
    
    private: 
        sf::CircleShape shape;
        float speed;
        sf::Vector2f velocity;
        typeBooster type;

    public:
        Booster(float x, float y, typeBooster t);
        void draw(sf::RenderWindow& window);
        const sf::CircleShape& getShape();
        void update(float dt);
        void setPosition(float x, float y);
        typeBooster getType() { return type; }
        void setColor(sf::Color color);
};