#include<iostream>
#include"Game.hpp"

 int main()
{
    // Init Game Engine
    Game game;
    // Screen loop
    std::cout<<"Simulation has been started \n";

    while (game.running())
    {
        // Update
        game.update();

        // Render
        game.render();

    }

}