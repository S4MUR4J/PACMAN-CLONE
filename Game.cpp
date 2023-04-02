#include "Headers/Game.h"

void Game::initVariables() {
    this->window = nullptr;
    this->endGame = false;
}

void Game::initWindow() {
    this->videoMode.width = 1920;
    this->videoMode.height = 1080;
    this->window = new sf::RenderWindow(this->videoMode,
       "Pac-Man", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(165);
}

Game::Game() {
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}

const bool Game::getWindowIsOpen() const {
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->event))
    {
        switch(this->event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::update() {
    this->pollEvents();
    this->pacman.update(this->window);
    this->fruit.update();
}

void Game::render() {
    this->window->clear();
    this->pacman.render(this->window);
    this->fruit.render(*this->window);
    this->window->display();
}

