#include "Game.h"

void Game::initVariables() {
    this->endGame = false;
    this->maxFruits = 10;
    this->points = 0;
}

void Game::initMapTiles()
{
    for(int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            if (sketch[j][i] == 1)
                this->mapTiles.push_back(Map(*this->window, i * cellSize, j * cellSize));
        }
    }
}

void Game::initFruits() {
    for(int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            if (sketch[j][i] == 0)
            this->fruits.push_back(Fruit(*this->window, i * cellSize + 20.f, j * cellSize + 20.f));
        }
    }
}

void Game::initWindow() {
    this->videoMode.width = mapWidth * cellSize;
    this->videoMode.height = mapHeight * cellSize;
    this->window = new sf::RenderWindow(this->videoMode, "Pac-Man", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(165);
}

void Game::manageEndGame()
{
    if(this->fruits.empty()) {
        this->endGame = true;
    }
}

Game::Game() {
    this->initVariables();
    this->initMapTiles();
    this->initFruits();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}

const bool Game::getEndGame() const {
    return this->endGame;
}

const bool Game::executing() const {
    return this->window->isOpen() && this->endGame == false;
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

void Game::updateCollision() {
    for (size_t i = 0; i < this->fruits.size(); i++) {
        if (this->pacman.getShape().getGlobalBounds().intersects(this->fruits[i].getShape().getGlobalBounds())) {
            this->points++;
            this->fruits.erase(this->fruits.begin() + i);
        }
    }
}

void Game::update() {
    this->pollEvents();

    if (this->endGame == false) {
        this->pacman.update(this->window);
        this->updateCollision();
        this->manageEndGame();
    }
}

void Game::render() {
    this->window->clear();

    for (auto i : this->mapTiles) {
        i.render(*this->window);
    }
    for (auto i : this->fruits) {        
        i.render(*this->window);
    }

    this->pacman.render(this->window);

    this->window->display();
}

