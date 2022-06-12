#ifndef GAME_HPP
#define GAME_HPP
#include<iostream>
#include<ctime>
#include<queue>
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
    /**
     * Set screen Resolution and basic tools necessary for the Game.
     * 
     * -window : The window which will appear when the Game starts.
     * -videoMode : Defines a video mode (width, height, bpp).
     * -background : The background of the window.
     * -logs : Logs that appear in the left top corner.
     * -font : for loading and manipulating character fonts.
     * -ev : Defines a system event and its parameter.
     * 
     */
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Texture background;
        sf::Text logs, guideText, collegeName;
        sf::Font font;
        sf::Event ev;

        //Game objects

        /**
         * -fromPeg, toPeg, auxPeg : As the name suggests they are the main Pegs.
         * -fPeg, tPeg : Temporary pegs to be used within the function [ void move(int myCase) ].
         * -disk : Temporary disk of type vector which takes a Vector as a Parameteer.
         * -S, D, A : Characters to help the function know where to go; A for AUX, S for Source and D for Destination.
         * -holder : Character to help in swaping between S, D, A.
         * 
         */
        std::vector<sf::RectangleShape> fromPeg, toPeg, auxPeg, fPeg, tPeg, emptyPeg;
        sf::RectangleShape disk;
        char S, D, A, holder;
        


        //Game logic
        int points;
        float diskSpawnTimer;
        float diskSpawnTimerMax;
        std::queue<int> queue, emptyQueue;


        // private functions
        void initVariables();
        void initWindow();
        void initDisks();

    public:
        // Public variable to be visible in main.cpp
        int maxDisks, numberOfDisks, totalMoves;
        // Constructors & Destructors
        Game(); // First thing to run in the class
        ~Game(); //Destructor to run last thing 

        // Accessors
        const bool running() const;

        // Functions
        void move(int myCase);
        void pollEvents();
        void update();
        void TowerLogic(int, char, char, char);
        void renderDisks();
        void render();
};
#endif // GAME_HPP