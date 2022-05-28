#include<iostream>
#include "Game.hpp"

void Game::initVariables()
{
    this->window = nullptr;
    //Game logic
    this->points = 0;
    this->diskSpawnTimerMax = 100.f;
    this->diskSpawnTimer = this->diskSpawnTimerMax;
    this->maxDisks = 3;
    this->S = 'S', this->D = 'D', this->A = 'A';
    if (this->maxDisks % 2 == 0)
    {
        this->S = 'S', this->D = 'D', this->A = 'A';
    }
    else
    {
        this->S = 'S', this->D = 'A', this->A = 'D';
    }
    this->text;
    this->font.loadFromFile("assets/fonts/Roboto-Black.ttf");
    this->text.setFont(this->font);
    this->text.setPosition(726.f, 380.f);
    this->text.setFillColor(sf::Color::Black);
    this->text.setScale(sf::Vector2f(1.7f, 1.7f));
    this->text.setString("Click SPACE to start simulation!");
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
    this->initDisks();
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
    std::cout<<"Entered Game::move() :D\n";
    switch (myCase)
    {
        case 15:
        // from Source to Destination
            this->stack.pop();
            this->text.setString("from Source to Destination");
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
            this->stack.pop();
            this->text.setString("from Source to Auxiliary");
            this->fPeg = this->fromPeg;
            this->tPeg = this->auxPeg;
            this->disk = this->fPeg.back();
            std::cout<<"the size of fromPeg is "<<this->fPeg.size()<<"\n";
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
            this->stack.pop();
            this->text.setString("from Destination to Auxiliary");
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
            this->stack.pop();
            this->text.setString("from Auxiliary to Source");
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
            this->stack.pop();
            this->text.setString("from Auxliary to Destination");
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
            this->stack.pop();
            this->text.setString("from Destination to Source");
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
        this->stack.push(S-D);
        return;
    }
    this->TowerLogic(NumberOfDisks-1, S, A, D);
    std::cout<<"Moved from "<<" "<<S<<" to "<<D<<"\n";
    this->stack.push(S-D);
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
            if (this->ev.key.code == sf::Keyboard::Escape)
            {
            this->window->close();
            }
            else if (this->ev.key.code == sf::Keyboard::Space)
            {
            this->move(this->stack.front());
            
            } 
            this->diskSpawnTimer += 1.f;
            this->update();
            break;
        }
    }
}

// UPDATE

void Game::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}
void Game::updateDiskPositions()
{
    this->window->draw(this->disk);
}
void Game::updateDisks()
{
    /**
     * @return void
     * 
     * Update the disk spawn timer and spawn the disks
     * when the total amount of enemies is smaller than the maximum number.
     * -Moves the Disks.
     * -Remove disks from the edige of the window.
     */


    // Updating timer for Disk spawn
    if (this->fromPeg.size() < this->toPeg.size())
    {

        if (this->diskSpawnTimer >= this->diskSpawnTimerMax)
        {
            // spawn the disk and reset timer
            this->diskSpawnTimer += 1.f;
            this->update();
        }
        else
        {
            // towersOfHanoi tower;
            // tower.run(this->fromPeg.size(), 'A', 'C', 'B');
            this->diskSpawnTimer = 0.f;
            this->updateDisks();
        }

        // Move the disks

        // for (auto &e :*this->fromPeg)
        // {
        //     e.move(0.f, 7.f);
        // }

    }
    else{
        std::cout<<"Error at line 260";
    }
}

void Game::update()
{
    this->pollEvents();
    this->updateMousePositions();
    this->updateDiskPositions();

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
    this->window->draw(this->text);
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