#include <SFML/Graphics.hpp>
#include <vector>
#include "paddle.h"
#include "ball.h"
#include "bricks.h"

using namespace sf;
using namespace std;

void deployMenu(RenderWindow& window) {
    Font font("C:/Windows/Fonts/arial.ttf");
    Text text(font, "Breakout", 80);
    text.setPosition({window.getSize().x / 3.f - 10, window.getSize().y / 4.f});
    RectangleShape boton_play;
    boton_play.getFillColor(Color::Red)

    float mouse_x = Mouse::getPosition().x;
    float mouse_y = Mouse::getPosition().y;

    float x1 = boton_play.getPosition().x;
    float x2 = x1 + boton_play.getSize().x;
    float y1 = boton_play.getPosition().y;
    float y2 = y1 + boton_play.getSize().y;
}

int main() {
    RenderWindow window(VideoMode({800, 600}), "Legos Rotos!");

    Clock clock;
    Paddle paddle(400, 600);
    Ball ball(window.getSize().x / 2.f, window.getSize().y / 2.f);
    vector<Brick> bricks;

    Font font("C:/Windows/Fonts/arial.ttf");
    Text text(font, "Breakout", 80);
    

    enum Estado {
        Menu,
        Playing
    };
    Estado estado = Menu;

    if(estado == Menu) {
        deployMenu(window);
    }

    for (int i = 0; i < 10; ++i) { 
        for (int j = 0; j < 5; ++j) { 
            bricks.emplace_back(100 + i * 55, 100 + j * 40); 
        } 
    }

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        //Eventos
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        //Movimiento de la pala
        if(Keyboard::isKeyPressed(Keyboard::Key::Right)){
            paddle.moveRight(dt);       
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Left)) {
            paddle.moveLeft(dt);
        }

        if(ball.getGlobalBounds().findIntersection(paddle.getGlobalBounds())) {
            ball.bounceY();
        }
        for(auto& brick : bricks) {
            if(brick.isDestroyed()) {
                continue;
            }
            if (ball.getGlobalBounds().findIntersection(brick.getShape().getGlobalBounds())) { 
                brick.destroy(); 
                auto ballBounds = ball.getGlobalBounds(); 
                auto brickBounds = brick.getShape().getGlobalBounds(); 

                float dx = (ballBounds.position.x + ballBounds.size.x / 2) - (brickBounds.position.x + brickBounds.size.x / 2); 
                float dy = (ballBounds.position.y + ballBounds.size.y / 2) - (brickBounds.position.y + brickBounds.size.y / 2); 

                if (std::abs(dx) > std::abs(dy)) 
                    ball.bounceX(); 
                else 
                    ball.bounceY(); 
                    break;
            }

        }

        ball.update(dt, window);

        //Dibujar objetos

        window.clear(Color::Black);
        for(int i = 0; i < bricks.size(); i++) {
            bricks[i].draw(window);
        }
        window.draw(text);
        paddle.draw(window);
        ball.draw(window);
        window.display();
    }

    return 0;
}