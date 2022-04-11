//
// Created by gavin on 4/10/2022.
//
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

#ifndef PONG_PONG_H
#define PONG_PONG_H

namespace Pong
{
    struct Collider
    {
        Collider(float xL, float yL, float xR, float yR)
        {   x1 = xL;
            y1 = yL;
            x2 = xR;
            y2 = yR;};
        float x1, y1, x2, y2;
        void updateY(float move) {y1 += move; y2 += move;};
        void updateX(float move) {x1 += move; x2 += move;};
    };

    class Paddle
    {
    private:
        float xPos, yPos;
        float width = 20.0f;
        float height = 125.0f;
        sf::Color fillColor;
    public:
        Paddle(float, float, sf::Color);
        ~Paddle();
        void move(float);
        Collider bound;
        sf::RectangleShape paddleBox;

    };

    class Ball
    {
    private:
        float velocityX, velocityY, xPos, yPos;
        float radius = 10.0f;
        sf::Color fillColor;
    public:
        Ball(float, float, sf::Color);
        ~Ball();
        void updateBall(), reverseX(), reverseY();
        Collider bound;
        sf::CircleShape ballCircle;

    };


    class Application
    {
    public:
        Application(int width, int height, std::string title);
        ~Application();
        void mainloop();

    private:
        Paddle rightPaddle, leftPaddle;
        Ball ball;
        int WIDTH, HEIGHT;
        sf::RenderWindow window;
        void eventHandler(), drawHandler(), pollCollisions();

    };
};
#endif //PONG_PONG_H
