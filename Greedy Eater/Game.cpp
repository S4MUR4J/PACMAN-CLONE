#include "Game.h"

void Game::initVariables()
{
    this->endGame = false;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode(1920, 1080);
    // this->videoMode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(this->videoMode, "Greedy Eater", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

// Constructors and Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    // Most important thing cause memory leak
    delete this->window;
}

// Functions

const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->sfmlEvent))
    {
        switch (this->sfmlEvent.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }        
    }
}

void Game::update()
{
    this->pollEvents();

    this->player.update(this->window);
}

void Game::render()
{
    this->window->clear();

    // Render stuff
    this->player.render(this->window);

    this->window->display();
}