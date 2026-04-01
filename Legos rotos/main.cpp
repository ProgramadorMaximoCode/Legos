#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include "paddle.h"
#include "ball.h"
#include "bricks.h"
#include "booster.h"

using namespace sf;
using namespace std;

// Función del menú, devuelve true si se clickea Play
bool deployMenu(RenderWindow& window) {
    Font font("C:/Windows/Fonts/arial.ttf");
    // Título
    Text title(font, "Breakout", 80);
    title.setPosition({window.getSize().x / 3.f, window.getSize().y / 4.f});

    // Botón Play
    RectangleShape boton_play;
    boton_play.setSize({200.f, 80.f});
    boton_play.setFillColor(Color::Red);
    boton_play.setPosition({window.getSize().x / 2.f - 100.f, window.getSize().y / 2.f});

    Text playText(font, "PLAY", 30);
    playText.setPosition({boton_play.getPosition().x + 60.f, boton_play.getPosition().y + 20.f});

    // Mouse relativo a la ventana
    Vector2i mousePos = Mouse::getPosition(window);

    // Hover effect
    if (boton_play.getGlobalBounds().contains((Vector2f)mousePos)) {
        boton_play.setFillColor(Color::Green);

        if (Mouse::isButtonPressed(Mouse::Button::Left)) {
            return true; // Cambiar a estado Playing
        }
    }

    // Dibujar
    window.clear(Color::Black);
    window.draw(title);
    window.draw(boton_play);
    window.draw(playText);
    window.display();

    return false;
}

sf::ConvexShape createHeart(float posX, float posY, float scale = 1.f, int points = 100)
{
    sf::ConvexShape heart;
    heart.setPointCount(points);

    for (int i = 0; i < points; i++)
    {
        float t = i * 2.f * 3.1415926f / points;

        float x = 16.f * pow(sin(t), 3);
        float y = -(13.f * cos(t)
                  - 5.f * cos(2.f * t)
                  - 2.f * cos(3.f * t)
                  - cos(4.f * t));

        heart.setPoint(i, {
            posX + x * scale,
            posY + y * scale
        });
    }

    heart.setFillColor(sf::Color::Red);

    return heart;
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);
    uniform_int_distribution<> bt_random(0, 20);
    uniform_int_distribution<> booster_type_random(0, 4);

    RenderWindow window(VideoMode({800, 600}), "Legos Rotos!");

    Clock clock;
    Clock temp;
    Paddle paddle(400, 550);
    Ball ball(window.getSize().x / 2.f, window.getSize().y / 2.f);
    Font fontLoser("C:/Windows/Fonts/comicbd.ttf");
    vector<Booster> boosters;
    
    Text textLoser(fontLoser, "Game Over", 80);
    Text textWinner(fontLoser, "You Win!", 80);
    FloatRect boundsLoser = textLoser.getLocalBounds();
    textLoser.setOrigin({boundsLoser.position.x + boundsLoser.size.x / 2.f, boundsLoser.position.y + boundsLoser.size.y / 2.f});
    textLoser.setPosition({window.getSize().x / 2.f, window.getSize().y / 2.f});

    FloatRect boundsWinner = textWinner.getLocalBounds();
    textWinner.setOrigin({boundsWinner.position.x + boundsWinner.size.x / 2.f, boundsWinner.position.y + boundsWinner.size.y / 2.f});
    textWinner.setPosition({window.getSize().x / 2.f, window.getSize().y / 2.f});

    vector<Brick> bricks;
    int lifes = 3;
    bool started = false;
    bool loser = false;
    bool winner = false;

    enum Estado { 
        Menu, 
        Playing 
    };
    Estado estado = Menu;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {

            if (dist(gen) == 0) {
                continue;
            }
            bricks.emplace_back(100 + i * 70, 80 + j * 40);
        }
    }

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        // Menú
        if (estado == Menu) {
            if (deployMenu(window)) {
            estado = Playing;
            }
            continue;
        }

        // Movimiento de la pala
        if(!loser && !winner) {
            if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D)) {
            paddle.moveRight(dt);     
            if(paddle.getShape().getPosition().x + paddle.getShape().getSize().x / 2.f >= window.getSize().x)
            {
                paddle.setPosition({window.getSize().x - paddle.getShape().getSize().x / 2.f, paddle.getShape().getPosition().y});
            } 
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A)) {
                paddle.moveLeft(dt);
                if(paddle.getShape().getPosition().x - paddle.getShape().getSize().x / 2.f <= 0)
                {
                    paddle.setPosition({0.f + paddle.getShape().getSize().x / 2.f, paddle.getShape().getPosition().y});
                } 
            }
            if(!started) {
                ball.setPosition({paddle.getShape().getPosition().x, paddle.getShape().getPosition().y - 30});
                if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
                    started = true;
                }
            }
        }
        

        if(started) {
             // Colisión con la pala
            if(ball.getGlobalBounds().findIntersection(paddle.getGlobalBounds())) {
                ball.bounceY();
            }

            // Colisión con bricks
            for(auto& brick : bricks) {
                if(brick.isDestroyed()) continue;

                if(ball.getGlobalBounds().findIntersection(brick.getShape().getGlobalBounds())) { 

                if (bt_random(gen) <= 5) {
                    Booster::typeBooster t = static_cast<Booster::typeBooster>(booster_type_random(gen));
                    boosters.emplace_back(brick.getShape().getPosition().x, brick.getShape().getPosition().y, t);
                }

                    brick.destroy(); 
                    bricks.erase(remove_if(bricks.begin(), bricks.end(), [](const Brick& b) { return b.isDestroyed(); }), bricks.end()); ////////////////////////////////////////////

                    auto ballBounds = ball.getGlobalBounds(); 
                    auto brickBounds = brick.getShape().getGlobalBounds(); 

                    float dx = (ballBounds.position.x + ballBounds.size.x / 2) - (brickBounds.position.x + brickBounds.size.x / 2); 
                    float dy = (ballBounds.position.y + ballBounds.size.y / 2) - (brickBounds.position.y + brickBounds.size.y / 2); 

                    if (abs(dx) > abs(dy)) 
                        ball.bounceX(); 
                    else 
                        ball.bounceY(); 
                    break;

                }
            }

            for (auto it = boosters.begin(); it != boosters.end(); ) {
                if (it->getShape().getGlobalBounds().findIntersection(paddle.getGlobalBounds())) {

                    // Efecto según tipo
                    switch (it->getType()) {
                        case Booster::typeBooster::Life:
                            lifes++;
                            break;

                        case Booster::typeBooster::BiggerPaddle:
                            paddle.increaseSize();
                            break;

                        case Booster::typeBooster::FastPaddle:
                            paddle.increaseSpeed();
                            break;
                        case Booster::typeBooster::SlowerPaddle:
                            paddle.decreaseSpeed();
                            break;
                        case Booster::typeBooster::SmallerPaddle:
                            paddle.decreaseSize();
                            break;
                    }
                
                    it = boosters.erase(it);
                } 
                else {
                    it++;
                }
            }

            float top = ball.getPosition().y - ball.getRadius();
            float bottom = ball.getPosition().y + ball.getRadius();

            if (top <= 0.f) {
                ball.bounceY();
            }
            else if( bottom >= window.getSize().y) {
                lifes--;
                started = false;
                paddle.setNormal();

                if(lifes == 0) {
                    loser = true;
                }
            }
            if (ball.getPosition().x - ball.getRadius() <= 0.f || ball.getPosition().x + ball.getRadius() >= window.getSize().x)
            {
                ball.bounceX();
            }

            if(bricks.empty()) {
                winner = true;
            }

        }
       
        if(!loser && !winner) {
            ball.update(dt, window);
            for(auto& booster : boosters) {
                booster.update(dt);
            }

        }
        // Dibujar objetos
        window.clear(Color::Black);
        for(auto& brick : bricks) {
            brick.draw(window);
        }
        ball.draw(window);
        for(auto& booster : boosters) {
                booster.draw(window);
            }

        for(int i = 0; i < lifes; i++) {
            auto heart = createHeart(40 + i * 40, 25);
            window.draw(heart);
        }
        if(loser) {
            window.draw(textLoser);
        }
        if (winner) {
            window.draw(textWinner);
        }

        paddle.draw(window);
        window.display();
    }

    return 0;
}