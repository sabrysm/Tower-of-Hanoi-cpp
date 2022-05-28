#include<iostream>
#include "Game.hpp"

void Game::initVariables()
{
    this->window = nullptr;
    //Game logic
    this->points = 0;
    this->diskSpawnTimerMax = 100.f;
    this->diskSpawnTimer = this->diskSpawnTimerMax;
    this->font.loadFromFile("assets/fonts/Roboto-Black.ttf");
    this->logs.setFont(this->font);
    this->logs.setPosition(45.f, 60.f);
    this->logs.setFillColor(sf::Color::Black);
    this->logs.setScale(sf::Vector2f(1.2f, 1.2f));
    this->guideText.setFont(this->font);
    this->guideText.setPosition(745.f, 345.f);
    this->guideText.setScale(sf::Vector2f(2.f, 2.f));
    this->guideText.setFillColor(sf::Color::Black);
    this->guideText.setString("Choose any number of Disks!\n\t\t\t\tbetween 3 to 9");
    this->queue = this->emptyQueue; // Empty the queue to start counting properly.
}
void Game::initWindow()
{
    this->videoMode.width = 2400;
    this->videoMode.height = 1500;
    this->window = new sf::RenderWindow(this->videoMode, "Tower Of Hanoi", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
    this->background.loadFromFile("assets/background/TOHbg3.png");
}
void Game::initDisks()
{
    this->S = 'S', this->D = 'D', this->A = 'A';
    if (this->maxDisks % 2 == 0)
    {
        this->S = 'S', this->D = 'D', this->A = 'A';
    }
    else
    {
        this->S = 'S', this->D = 'A', this->A = 'D';
    }
    this->queue = this->emptyQueue; // Empty the queue to start counting properly.
    for (int i = 0; i < this->maxDisks; i++)
    {
    this->disk.setSize(sf::Vector2(500.f-0.1f*500*i, 40.f));
    this->disk.setPosition(sf::Vector2(557.f-0.5f*this->disk.getSize().x, 1307.f-40*i));
    this->disk.setFillColor(sf::Color::Green);
    this->disk.setOutlineColor(sf::Color::Cyan);
    this->disk.setOutlineThickness(1.f);
    this->fromPeg.push_back(this->disk);
    std::cout<<this->disk.getSize().x<<"\n";
    }
    std::cout<<this->fromPeg.size();
}

// Constructors

Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

// Accessors

const bool Game::running() const
{
    return this->window->isOpen();
}

// Functions 

void Game::move(int myCase)
{
    switch (myCase)
    {
        case 15:
        // from Source to Destination
            this->queue.pop();
            this->logs.setString("from Source to Destination");
            this->fPeg = this->fromPeg;
            this->tPeg = this->toPeg;
            this->disk = this->fPeg.back();
            this->window->clear();
            this->disk.setPosition(sf::Vector2(1957.f-0.5f*this->disk.getSize().x, 1307.f-40*this->tPeg.size()));
            this->window->draw(this->disk);
            this->tPeg.push_back(this->disk);
            this->fPeg.pop_back();
            this->fromPeg = this->fPeg;
            this->toPeg = this->tPeg;
            this->update();
            this->render();
            break;
            
        case 18:
        // from Source to Auxiliary
            this->queue.pop();
            this->logs.setString("from Source to Auxiliary");
            this->fPeg = this->fromPeg;
            this->tPeg = this->auxPeg;
            this->disk = this->fPeg.back();
            this->disk.setPosition(sf::Vector2(1257.f-0.5f*this->disk.getSize().x , 1307.f-40*this->tPeg.size()));
            this->window->draw(this->disk);
            this->tPeg.push_back(this->disk);
            this->fPeg.pop_back();
            this->fromPeg = this->fPeg;
            this->auxPeg = this->tPeg;
            this->update();
            this->render();
            break;
            
        case 3:
        // from Destination to Auxiliary
            this->queue.pop();
            this->logs.setString("from Destination to Auxiliary");
            this->fPeg = this->toPeg;
            this->tPeg = this->auxPeg;
            this->disk = this->fPeg.back();
            this->disk.setPosition(sf::Vector2(1257.f-0.5f*this->disk.getSize().x , 1307.f-40*this->tPeg.size()));
            this->window->draw(this->disk);
            this->tPeg.push_back(this->disk);
            this->fPeg.pop_back();
            this->toPeg = this->fPeg;
            this->auxPeg = this->tPeg;
            this->update();
            this->render();
            break;
            
        case -18:
        // from Auxiliary to Source
            this->queue.pop();
            this->logs.setString("from Auxiliary to Source");
            this->fPeg = this->auxPeg;
            this->tPeg = this->fromPeg;
            this->disk = this->fPeg.back();
            this->disk.setPosition(sf::Vector2(557.f-0.5f*this->disk.getSize().x , 1307.f-40*this->tPeg.size()));
            this->window->draw(this->disk);
            this->tPeg.push_back(this->disk);
            this->fPeg.pop_back();
            this->auxPeg = this->fPeg;
            this->fromPeg = this->tPeg;
            this->update();
            this->render();
            break;
            
        case -3:
        // from Auxiliary to Destination
            this->queue.pop();
            this->logs.setString("from Auxliary to Destination");
            this->fPeg = this->auxPeg;
            this->tPeg = this->toPeg;
            this->disk = this->fPeg.back();
            this->disk.setPosition(sf::Vector2(1957.f-0.5f*this->disk.getSize().x , 1307.f-40*this->tPeg.size()));
            this->window->draw(this->disk);
            this->tPeg.push_back(this->disk);
            this->fPeg.pop_back();
            this->auxPeg = this->fPeg;
            this->toPeg = this->tPeg;
            this->update();
            this->render();
            break;
            
        case -15:
        // from Destination to Source
            this->queue.pop();
            this->logs.setString("from Destination to Source");
            this->fPeg = this->toPeg;
            this->tPeg = this->fromPeg;
            this->disk = this->fPeg.back();
            this->disk.setPosition(sf::Vector2(557.f-0.5f*this->disk.getSize().x , 1307.f-40*this->tPeg.size()));
            this->window->draw(this->disk);
            this->tPeg.push_back(this->disk);
            this->fPeg.pop_back();
            this->toPeg = this->fPeg;
            this->fromPeg = this->tPeg;
            this->update();
            this->render();
            break;
            
        default:
            std::cout<<"Error occured";
            break;
    }
}
void Game::TowerLogic(int NumberOfDisks, char S, char D, char A)
{
    if (NumberOfDisks == 1)
    {
        std::cout<<"Moved from "<<" "<<S<<" to "<<D<<"\n";
        this->queue.push(S-D);
        return;
    }
    this->TowerLogic(NumberOfDisks-1, S, A, D);
    std::cout<<"Moved from "<<" "<<S<<" to "<<D<<"\n";
    this->queue.push(S-D);
    this->TowerLogic(NumberOfDisks-1, A, D, S);
}

void Game::run(int n, char fromA, char auxC, char toB, int value)
{
    if (n==1)
    {
        this->move(value);
        std::cout<<"Move from rod "<<fromA<<" to rod "<<toB<<" \n";
        return;
    }
    switch (value)
    {
        case 15: // from Source to Destination
            std::cout<<"Move from rod "<<fromA<<" to rod "<<toB<<" \n";
            this->numberOfDisks--;
            this->pollEvents();
            this->move(value);
            this->S = fromA, this->D = auxC, this->A = toB; // Here where we decide where to go
            break;
        case 18: // from Source to Auxiliary
            std::cout<<"Move from rod "<<fromA<<" to rod "<<toB<<" \n";
            this->move(this->S - this->A);
            this->numberOfDisks--;
            this->S = fromA, this->D = toB, this->A = auxC; // Here where we decide where to go
            break;
        case -15: // from Destination to Auxiliary
            std::cout<<"Move from rod "<<fromA<<" to rod "<<toB<<" \n";
            this->numberOfDisks--;
            this->move(value);
            this->S = fromA, this->D = toB, this->A = auxC; // Here where we decide where to go
            break;
        case -18: // from Auxiliary to Source
            std::cout<<"Move from rod "<<fromA<<" to rod "<<toB<<" \n";
            this->numberOfDisks--;
            this->move(value);
            this->S = fromA, this->D = toB, this->A = auxC; // Here where we decide where to go
            break;
        case 3: // from Destination to Auxiliary
            std::cout<<"Move from rod "<<fromA<<" to rod "<<toB<<" \n";
            this->numberOfDisks--;
            this->move(value);
            this->S = fromA, this->D = toB, this->A = auxC; // Here where we decide where to go
            break;
        case -3: // from Auxiliary to Destination
            std::cout<<"Move from rod "<<fromA<<" to rod "<<toB<<" \n";
            this->numberOfDisks--;
            this->move(value);
            this->S = fromA, this->D = toB, this->A = auxC; // Here where we decide where to go
            break;
        default:
            break;
    }
}



void Game::pollEvents()
{
        // Event Polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
        
            if (this->ev.key.code == sf::Keyboard::Num5)
            {
                this->maxDisks = 5;
                this->queue = this->emptyQueue; // Empty the queue to start counting properly.
                this->initDisks();
                this->TowerLogic(this->maxDisks, 'S', 'D', 'A');
                this->guideText.setString("Now click SPACE to start simulation.");
            }
            else if (this->ev.key.code == sf::Keyboard::Num9)
            {
                this->maxDisks = 9;
                this->queue = this->emptyQueue; // Empty the queue to start counting properly.
                this->initDisks();
                this->TowerLogic(this->maxDisks, 'S', 'D', 'A');
                this->guideText.setString("Now click SPACE to start simulation.");
            }
            else if (this->ev.key.code == sf::Keyboard::Num8)
            {
                this->maxDisks = 8;
                this->queue = this->emptyQueue; // Empty the queue to start counting properly.
                this->initDisks();
                this->TowerLogic(this->maxDisks, 'S', 'D', 'A');
                this->guideText.setString("Now click SPACE to start simulation.");
            }
            else if (this->ev.key.code == sf::Keyboard::Num7)
            {
                this->maxDisks = 7;
                this->queue = this->emptyQueue; // Empty the queue to start counting properly.
                this->initDisks();
                this->TowerLogic(this->maxDisks, 'S', 'D', 'A');
                this->guideText.setString("Now click SPACE to start simulation.");
            }
            else if (this->ev.key.code == sf::Keyboard::Num6)
            {
                this->maxDisks = 6;
                this->queue = this->emptyQueue; // Empty the queue to start counting properly.
                this->initDisks();
                this->TowerLogic(this->maxDisks, 'S', 'D', 'A');
                this->guideText.setString("Now click SPACE to start simulation.");
            }
            else if (this->ev.key.code == sf::Keyboard::Num4)
            {
                this->maxDisks = 4;
                this->queue = this->emptyQueue; // Empty the queue to start counting properly.
                this->initDisks();
                this->TowerLogic(this->maxDisks, 'S', 'D', 'A');
                this->guideText.setString("Now click SPACE to start simulation.");
            }
            else if (this->ev.key.code == sf::Keyboard::Num3)
            {
                this->maxDisks = 3;
                this->queue = this->emptyQueue; // Empty the queue to start counting properly.
                this->initDisks();
                this->TowerLogic(this->maxDisks, 'S', 'D', 'A');
                this->guideText.setString("Now click SPACE to start simulation.");
            }
            else if (this->ev.key.code == sf::Keyboard::Escape)
            {
            this->window->close();
            }
            else if (this->ev.key.code == sf::Keyboard::Space)
            {
                this->move(this->queue.front());
                this->guideText.setString("");
            }
            this->diskSpawnTimer += 1.f;
            this->update();
            break;
        }
    }
}

// UPDATE

void Game::update()
{
    this->pollEvents();

}
void Game::renderDisks()
{
    // Render all Disks
    this->window->draw(this->disk);
}
void Game::render() // Playing the Pixels on the window
{
    /*
    @return void
    - clear window
    - render objects
    - display frame in window

    Render the Game objects.
    */
    this->window->clear();

    // Draw game object
    
    this->window->draw(static_cast<sf::Sprite>(this->background));
    this->window->draw(this->logs);
    this->window->draw(this->guideText);
    for (auto& t : this->fromPeg)
    {
        this->window->draw(t);
    }
    for (auto& e : this->toPeg)
    {
        this->window->draw(e);
    }
    for (auto& m : this->auxPeg)
    {
        this->window->draw(m);
    }
    this->renderDisks();
    this->window->display();
    
}