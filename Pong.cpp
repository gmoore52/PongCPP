//
// Created by gavin on 4/10/2022.
//
#include "Pong.h"

namespace Pong
{
    Paddle::Paddle(float initX, float initY, sf::Color color) : bound(initX, initY, initX+Paddle::width, initY+Paddle::height)
    {
        fillColor = color;
        paddleBox.setSize(sf::Vector2f(Paddle::width, Paddle::height));
        paddleBox.setFillColor(fillColor);
        paddleBox.setPosition(initX, initY);
    }

    Paddle::~Paddle()
    {

    }

    void Paddle::move(float deltaY)
    {
        bound.updateY(deltaY);
        paddleBox.move(0.0f, deltaY);
    }

    void Paddle::setPos(float xPos, float yPos)
    {
        bound.setPosition(xPos, yPos);
        paddleBox.setPosition(xPos, yPos);
    }

    Ball::Ball(float initX, float initY, sf::Color color) : bound(initX, initY, initX + (radius * 2), initY + (radius * 2))
    {
        fillColor = color;
        velocityX = 0.1f; velocityY = 0.1f;
        ballCircle.setRadius(radius);
        ballCircle.setFillColor(fillColor);
        ballCircle.setPosition(initX, initY);
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
        ballCircle.move(velocityX, velocityY);
        bound.updateY(velocityY);
        bound.updateX(velocityX);
    }

    void Ball::setPos(float xPos, float yPos)
    {
        bound.setPosition(xPos, yPos);
        ballCircle.setPosition(xPos, yPos);
    }

    Game::Game(int width, int height) : leftPaddle(0.0f, height/2, sf::Color::Blue), rightPaddle(width-20.0f, height/2, sf::Color::Red),
                                        ball(20.0f, 20.0f, sf::Color::Green)
    {
        WIDTH = width; HEIGHT = height;
        scoreLeft = 0; scoreRight = 0;
        font.loadFromFile("../arial.ttf");

        updateLabels();
        labelLeft.setFont(font);
        labelLeft.setCharacterSize(24);
        labelLeft.setFillColor(sf::Color::Red);
        labelLeft.setPosition(0.0f, 0.0f);

        labelRight.setFont(font);
        labelRight.setCharacterSize(24);
        labelRight.setFillColor(sf::Color::Blue);
        labelRight.setPosition(WIDTH-160, 0.0f);
    }

    Game::~Game()
    {

    }

    void Game::updateLabels()
    {
        int offset;
        if(scoreRight == 0)
        {
            offset = 0;
        }
        else
        {
            offset = 13*int (log10(scoreRight));
        }
        textLeft  = "Score Left: "  + std::to_string(scoreLeft);
        textRight = "Score Right: " + std::to_string(scoreRight);
        labelRight.setPosition(WIDTH-160-offset, 0.0f);
        labelLeft.setString(textLeft); labelRight.setString(textRight);
    }

    void Game::resetGame()
    {
        scoreLeft = 0; scoreRight = 0;
        leftPaddle.setPos(0.0f, HEIGHT/2);
        rightPaddle.setPos(WIDTH-20.0f, HEIGHT/2);
        ball.setPos(20.0f, 20.0f);
    }

    void Game::pollEvents(sf::RenderWindow &renderer, std::string &stateString)
    {
        sf::Event event;
        while (renderer.pollEvent(event)) {
            float dy = 7.5f;
            switch (event.type) {
                case sf::Event::Closed:
                    renderer.close();
                    break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if (leftPaddle.bound.y1 > 0) {
                    leftPaddle.move(-dy);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (leftPaddle.bound.y2 < HEIGHT) {
                    leftPaddle.move(dy);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                if (rightPaddle.bound.y1 > 0) {
                    rightPaddle.move(-dy);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                if (rightPaddle.bound.y2 < HEIGHT) {
                    rightPaddle.move(dy);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                resetGame();
                stateString = "Main";
            }
        }
    }

    void Game::pollCollisions()
    {
        if(ball.bound.x2 > WIDTH)// || ball.bound.x1 < 0)
        {
            scoreLeft++;
            ball.reverseX();
        }
        if(ball.bound.x1 < 0)
        {
            scoreRight++;
            ball.reverseX();
        }
        // Check collisions with right paddle
        if(ball.bound.x2 > rightPaddle.bound.x1 && (ball.bound.y1 < rightPaddle.bound.y2 && ball.bound.y2 > rightPaddle.bound.y1))
        {
            ball.reverseX();
        }
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

    void Game::drawGame(sf::RenderWindow& renderer)
    {
        ball.updateBall();
        updateLabels();
        renderer.draw(leftPaddle.paddleBox);
        renderer.draw(rightPaddle.paddleBox);
        renderer.draw(ball.ballCircle);
        renderer.draw(labelLeft);
        renderer.draw(labelRight);
    }

    Button::Button(float xPos, float yPos, float width, float height, std::string buttonLabel) : buttonPos(xPos, yPos),
                                                                                                 bound(xPos, yPos, xPos+width, yPos+height)
    {
        float labelX, labelY, strLength;
        strLength = 4*int(buttonLabel.length());
        labelX = xPos+(width/2); labelY = yPos+(height/2)-10;
        labelX = labelX-strLength;// labelY = labelY-strLength;
        fontType.loadFromFile("../arial.ttf");
        buttonFace.setSize(sf::Vector2f(width, height));
        buttonFace.setPosition(xPos, yPos);
        buttonFace.setFillColor(sf::Color::Black);
        buttonFace.setOutlineColor(sf::Color::White);
        buttonFace.setOutlineThickness(1.0f);
        label = buttonLabel;
        displayLabel.setFont(fontType);
        displayLabel.setCharacterSize(16);
        displayLabel.setFillColor(sf::Color::White);
        displayLabel.setString(label);
        displayLabel.setPosition(labelX, labelY);
    }

    bool Button::isClicked(sf::Event& event)
    {
        bool retBool;
        switch (event.type) {
            case sf::Event::MouseButtonPressed:
                retBool = (bound.x1 < event.mouseButton.x && event.mouseButton.x < bound.x2)
                       && (bound.y1 < event.mouseButton.y && event.mouseButton.y < bound.y2);
                break;
        }
        return retBool;
    }

    MainMenu::MainMenu(int width, int height, float bWidth, float bHeight) : button1(width/2-bWidth/2, 200.0f, bWidth, bHeight, "Play"),
                                                                             button2(width/2-bWidth/2, 265.0f, bWidth, bHeight, "Quit")
    {
        buttonWidth = bWidth; buttonHeight = bHeight;
        fontType.loadFromFile("../arial.ttf");

        mainLabel.setFont(fontType);
        mainLabel.setFillColor(sf::Color::White);
        mainLabel.setString("Pong");
        mainLabel.setCharacterSize(26);
        mainLabel.setPosition(width/2-35, 150.0f);

    }

    MainMenu::~MainMenu()
    {

    }

    void MainMenu::pollEvents(sf::RenderWindow &renderer, std::string& stateString)
    {
        sf::Event event;
        while (renderer.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    renderer.close();
                    break;
            }
            if(button1.isClicked(event))
            {
                stateString = "Game";
            }
            if(button2.isClicked(event))
            {
                renderer.close();
            }

        }
    }


    void MainMenu::drawMenu(sf::RenderWindow &renderer)
    {
        renderer.draw(mainLabel);
        renderer.draw(button1.buttonFace);
        renderer.draw(button2.buttonFace);
        renderer.draw(button1.displayLabel);
        renderer.draw(button2.displayLabel);
    }


    Application::Application(int width, int height, std::string title) : window(sf::VideoMode(width, height), title),
                                                                         pongGame(width, height),
                                                                         mainMenu(width, height, 200.0f, 50.0f)
    {
        appState = "Main";
    }

    Application::~Application()
    {

    }

    void Application::drawWindow()
    {
        if(appState == "Game")
        {
            pongGame.pollEvents(window, appState);
            pongGame.pollCollisions();
            pongGame.drawGame(window);
        }
        else if(appState == "Main")
        {
            mainMenu.pollEvents(window, appState);
            mainMenu.drawMenu(window);
        }
    }

    void Application::mainloop() {
        while (window.isOpen())
        {
            window.clear();
            drawWindow();
            window.display();
        }
    }
}