//
// Created by gavin on 4/10/2022.
//
#include "Pong.h"

namespace Pong
{
    Paddle::Paddle(float initX, float initY, sf::Color color) : bound(initX, initY, initX+Paddle::width, initY+Paddle::height)
    {
//        Paddle::width = 100.0f; Paddle::height = 200.0f;
        fillColor = color;
        paddleBox.setSize(sf::Vector2f(Paddle::width, Paddle::height));
        paddleBox.setFillColor(fillColor);
        paddleBox.setPosition(initX, initY);
        xPos = initX; yPos = initY;
    }

    Paddle::~Paddle()
    {

    }

    void Paddle::move(float deltaY)
    {
        bound.updateY(deltaY);
        paddleBox.move(0.0f, deltaY);
    }

    Ball::Ball(float initX, float initY, sf::Color color) : bound(initX, initY, initX + (radius * 2), initY + (radius * 2))
    {
        xPos = initX; yPos = initY;
        fillColor = color;
        velocityX = 0.1f; velocityY = 0.1f;
        ballCircle.setRadius(radius);
        ballCircle.setFillColor(fillColor);
        ballCircle.setPosition(xPos, yPos);
    }

    Ball::~Ball()
    {

    }

    void Ball::reverseX()
    {
        velocityX *= -1;
    }

    void Ball::reverseY()
    {
        velocityY *= -1;
    }

    void Ball::updateBall()
    {
        xPos += velocityX; yPos += velocityY;
        ballCircle.move(velocityX, velocityY);
        bound.updateY(velocityY);
        bound.updateX(velocityX);
    }

    Application::Application(int width, int height, std::string title) : window(sf::VideoMode(width, height), title),
                                                                         leftPaddle(0.0f, height/2, sf::Color::Blue), rightPaddle(width-20.0f, height/2, sf::Color::Red),
                                                                         ball(20.0f, 20.0f, sf::Color::Green)
    {
        WIDTH = width; HEIGHT = height;


    }

    Application::~Application()
    {

    }

    void Application::eventHandler()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            float dy = 7.5f;
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                if (leftPaddle.bound.y1 > 0)
                {
                    leftPaddle.move(-dy);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                if (leftPaddle.bound.y1 < HEIGHT)
                {
                    leftPaddle.move(dy);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            {
                if (rightPaddle.bound.y1 > 0)
                {
                    rightPaddle.move(-dy);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            {
                if (rightPaddle.bound.y1 < HEIGHT)
                {
                    rightPaddle.move(dy);
                }
            }

        }
    }

    void Application::pollCollisions()
    {
        // Check if ball hits side walls
        if(ball.bound.x2 > WIDTH || ball.bound.x1 < 0)
        {
            ball.reverseX();
        }
        // Check collisions with right paddle
        if(ball.bound.x2 > rightPaddle.bound.x1 && (ball.bound.y1 < rightPaddle.bound.y2 && ball.bound.y2 > rightPaddle.bound.y1))
        {
            ball.reverseX();
            std::cout << "Right paddle" << std::endl;
        }
//        if(rightPaddle.bound.x1 < ball.bound.x2 && ball.bound.x2 < rightPaddle.bound.x2 && ((ball.bound.y2 < rightPaddle.bound.y1) || ball.bound.y1 > rightPaddle.bound.y2))
//        {
//            ball.reverseX();
//            std::cout << ball.bound.y2 << " " << rightPaddle.bound.y1 << " " << rightPaddle.bound.y2 << std::endl;
//            ball.reverseY();
//        }
        // Check collisions with left paddle
        if(ball.bound.x1 < leftPaddle.bound.x2 && (ball.bound.y1 < leftPaddle.bound.y2 && ball.bound.y2 > leftPaddle.bound.y1))
        {
            ball.reverseX();
        }
        // Check if ball hits top or bottom walls
        if(ball.bound.y2 > HEIGHT || ball.bound.y1 < 0)
        {
            ball.reverseY();
        }
    }

    void Application::drawHandler()
    {
        window.draw(leftPaddle.paddleBox);
        window.draw(rightPaddle.paddleBox);
        window.draw(ball.ballCircle);
    }

    void Application::mainloop() {
        while (window.isOpen())
        {
            eventHandler();


            window.clear();
            // draw stuff
            ball.updateBall();
            pollCollisions();
            drawHandler();
            window.display();
        }
    }
}