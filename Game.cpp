#include "Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;

    // Game logic
    this->points = 0;
    this->enemySpawnTimerMax = 165.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
}

void Game::initWindow()
{
    this->videoMode.width = 1920;
    this->videoMode.height = 1080;
    // this->videoMode.getDesktopMode;
    this->window = new sf::RenderWindow(this->videoMode, "Click - me!", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(165);
}

void Game::initEnemies()
{
    this->enemy.setPosition(500.f, 500.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    // this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(1.f);
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

void Game::spawnEnemy()
{
    /**
     * @return void
     * 
     * Spawns enemies and sets their colors and positions
     * - Sets a random position.
     * - Sets a random color.
     * - Adds enemy to the vector
    */

   this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y - 1080))
   );

   this->enemy.setFillColor(sf::Color::Green);

   // Spawn the enemy
    this->enemies.push_back(this->enemy);
}

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

void Game::updateMousePositions()
{
    /*
    @return void

        Updates the mouse positions:
        - Mouse position relative to window (Vector2i)
    */

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
   this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
    /**
     * @return void
     * 
     * Updated the enemy spawn timer and spawns enemies
     * when the total amount of enemies is smaller than maximum.
     * Moves the enemies downwards.
     * Removes the enemies at the edge of the screen
    */

    // Updating the timer for enemy spawning
    if(this->enemies.size() < this->maxEnemies)
    {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // Spawn enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    // Move the enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 3.f);

        // Check if clicked upon
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
            {
                deleted = true;

                // Gain points
                this->points += 10.f;
            }
        }

        // If the enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            deleted = true;
        }

        // Final delete
        if(deleted)
            this->enemies.erase(this->enemies.begin() + i);
    }
}

// Tu się dzieje gra wszystko co nie jest renderowane wszystko co nie widzimy
void Game::update()
{
    this->pollEvents();

    this->updateMousePositions();

    this->updateEnemies();

    // // Aktualizacja pozycji myszy
    // // Odnoszące się do ekranu
    // std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";
    // // Odnoszące się do okna
    // std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
}

void Game::renderEnemies()
{
    for (auto &e : this->enemies)
    {
        // Render all the enemies
        this->window->draw(e);
    }
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
    this->renderEnemies();

    this->window->display();
}