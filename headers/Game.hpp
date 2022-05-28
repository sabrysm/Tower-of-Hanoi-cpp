#ifndef GAME_HPP
#define GAME_HPP
#include<iostream>
#include<ctime>
#include<vector>
#include<math.h>
#include<bits/stdc++.h>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Network.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
using std::string;

class Game
{
    private:
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Texture background;
        sf::Text text;
        sf::Font font;
        sf::Event ev;


        // Mouse Position
        sf::Vector2i mousePosWindow;

        
        //Game objects
        std::vector<sf::RectangleShape> fromPeg, toPeg, auxPeg, fPeg, tPeg;
        sf::RectangleShape disk;
        char A, B, C, holder;


        //Game logic
        int points;
        float diskSpawnTimer;
        float diskSpawnTimerMax;
        int maxDisks, numberOfDisks, totalMoves;


        // private functions
        void initVariables();
        void initWindow();
        void initDisks();

    public:
        // Constructors & Destructors
        Game();
        ~Game();

        // Accessors
        const bool running() const;

        // Functions
        void TOH(int n);
        void run(int n, char fromA, char auxC, char toB, int value);
        void move(int myCase);
        void move(char from, char to);
        void pollEvents();
        void updateDiskPositions();
        void updateMousePositions();
        void updateDisks();
        void update();
        void GrayCodeAlgorithms(int current);
        void calcPosition(int numberOfDisks, char A, char B, char C);
        void renderDisks();
        void render();
};
#endif // GAME_HPP