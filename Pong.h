//
// Created by gavin on 4/10/2022.
//
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
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
        void setPosition(float x, float y){float diffX = x2-x1, diffY = y2-y1;
                                            x1 = x; x2 = x+diffX; y1 = y; y2 = y+diffY;};
    };

    class Paddle
    {
    private:
        float width = 20.0f;
        float height = 125.0f;
        sf::Color fillColor;
    public:
        Paddle(float, float, sf::Color);
        ~Paddle();
        void move(float), setPos(float, float);
        Collider bound;
        sf::RectangleShape paddleBox;

    };

    class Ball
    {
    private:
        float velocityX, velocityY;
        float radius = 10.0f;
        sf::Color fillColor;
    public:
        Ball(float, float, sf::Color);
        ~Ball();
        void updateBall(), reverseX(), reverseY(), setPos(float, float);
        Collider bound;
        sf::CircleShape ballCircle;

    };

    class Game
    {
    public:
        Game(int, int);
        ~Game();
        void pollEvents(sf::RenderWindow&, std::string&), pollCollisions(), drawGame(sf::RenderWindow&);

    private:
        Paddle rightPaddle, leftPaddle;
        Ball ball;
        int WIDTH, HEIGHT, scoreRight, scoreLeft;
        sf::Font font;
        sf::Text labelLeft, labelRight;
        std::string textLeft, textRight;
        void updateLabels(), resetGame();

    };

    struct Button
    {
    Button(float, float, float, float, std::string);
    sf::RectangleShape buttonFace;
    sf::Text displayLabel;
    sf::Font fontType;
    sf::Vector2f buttonPos;
    Collider bound;
    std::string label;
    bool isClicked(sf::Event&);
    };

    class MainMenu
    {
    private:
        Button button1, button2;
        sf::Text mainLabel;
        sf::Font fontType;
        float buttonWidth = 200.0f, buttonHeight = 50.0f;
    public:
        MainMenu(int, int, float, float);
        ~MainMenu();
        void pollEvents(sf::RenderWindow&, std::string&), drawMenu(sf::RenderWindow&);
    };


    class Application
    {
    public:
        Application(int width, int height, std::string title);
        ~Application();
        void mainloop();
    private:
        Game pongGame;
        MainMenu mainMenu;
        sf::RenderWindow window;
        std::string appState;
        void drawWindow();
    };
};
#endif //PONG_PONG_H
