#pragma once
#include <SFML/Graphics.hpp>

class Brick {
private:
    sf::RectangleShape shape; 
    bool destroyed = false;

public:
    Brick(float x, float y);
    void draw(sf::RenderWindow& window);
    void destroy();
    bool isDestroyed() const;
    const sf::RectangleShape& getShape();
};