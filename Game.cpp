#include "Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::intWindow()
{
    this->videoMode.width = 1980;
    this->videoMode.height = 1024;
    // this->videoMode.getDesktopMode;
    this->window = new sf::RenderWindow(this->videoMode, "Pac - Man", sf::Style::Titlebar | sf::Style::Close);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->intWindow();
}

Game::~Game()
{
    delete this->window;
}

// Accessors
const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}

// Functions

void Game::pollEvents()
{
    // Event Polling
        while (this->window->pollEvent(this->ev))
        {
            switch(this->ev.type)
            {
                case sf::Event::Closed:
                    this->window->close();
                    break;
                case sf::Event::KeyPressed:
                    if(this->ev.key.code == sf::Keyboard::Escape)
                        this->window->close();
                    break;
            }
        }
}

// Tu się dzieje gra wszystko co nie jest renderowane wszystko co nie widzimy
void Game::update()
{
    this->pollEvents();
}
// Tylko generowanie pikseli
void Game::render()
{
    /*
        @return void

        - clear old frame
        - render objects
        - display frame in window

        Render the game objects.
    */

    this->window->clear(sf::Color(255, 0, 0, 255));

    // Draw game objects

    this->window->display();
}