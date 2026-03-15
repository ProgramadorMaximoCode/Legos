#include <SFML/Graphics.hpp>
#include "paddle.h"
#include "ball.h"


using namespace sf;

int main() {
    RenderWindow window(VideoMode({800, 600}), "Legos Rotos!");
    Clock clock;
    Paddle paddle(400, 600);
    Ball ball(window.getSize().x / 2.f, window.getSize().y / 2.f);

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Key::Right))
            paddle.moveRight(dt);{
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Left))
            paddle.moveLeft(dt);{
        }
        ball.update(dt, window);

        window.clear(Color::Black);
        paddle.draw(window);
        ball.draw(window);
        window.display();
    }

    return 0;
}