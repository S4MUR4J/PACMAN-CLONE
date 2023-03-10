#include "Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.width = 1980;
    this->videoMode.height = 1024;
    // this->videoMode.getDesktopMode;
    this->window = new sf::RenderWindow(this->videoMode, "Pac - Man", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(165);
}

void Game::initEnemies()
{
    this->enemy.setPosition(500.f, 500.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();
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

    // Aktualizacja pozycji myszy
    // Odnoszące się do ekranu
    std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";
    // Odnoszące się do okna
    std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
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

    this->window->clear();

    // Draw game objects
    this->window->draw(this->enemy);

    this->window->display();
}