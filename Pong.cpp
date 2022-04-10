//
// Created by gavin on 4/10/2022.
//
#include "Pong.h"

namespace Pong
{
    Paddle::Paddle(float initX, float initY) : bound(initX, initY, initX+Paddle::width, initY+Paddle::height)
    {
//        Paddle::width = 100.0f; Paddle::height = 200.0f;
        paddleBox.setSize(sf::Vector2f(Paddle::width, Paddle::height));
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


    Application::Application(int width, int height, std::string title) : window(sf::VideoMode(width, height), title),
                                                                         rightPaddle(width-20.0f, 20.0f), leftPaddle(0.0f, 30.0f)
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
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

        }
    }

    void Application::drawHandler()
    {
        window.draw(leftPaddle.paddleBox);
        window.draw(rightPaddle.paddleBox);
    }

    void Application::mainloop() {
        while (window.isOpen())
        {
            eventHandler();


            window.clear();
            // draw stuff
//            window.draw(circle);
            drawHandler();
            window.display();
        }
    }
}