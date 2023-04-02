#include "Headers/Game.h"

void Game::initVariables() {
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxFruits = 10;
    this->points = 0;
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

void Game::spawnFruits() {
    if (this->spawnTimer < this->maxFruits) {
        this->spawnTimer += 1.f;
    }
    else
    {
        if (this->fruits.size() < this->maxFruits)
        {
            this->fruits.push_back(Fruit(*this->window));
            this->spawnTimer = 0.f;
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
        this->spawnFruits();
        this->pacman.update(this->window);
        this->updateCollision();
    }
}

void Game::render() {
    this->window->clear();  

    std::array<std::string, mapHeight> mapBuilder = {
        " ################### ",
        " #........#........# ",
        " #o##.###.#.###.##o# ",
        " #.................# ",
        " #.##.#.#####.#.##.# ",
        " #....#...#...#....# ",
        " ####.### # ###.#### ",
        "    #.#   0   #.#    ",
        "#####.# ##=## #.#####",
        "     .  #123#  .     ",
        "#####.# ##### #.#####",
        "    #.#       #.#    ",
        " ####.# ##### #.#### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #o.#.....P.....#.o# ",
        " ##.#.#.#####.#.#.## ",
        " #....#...#...#....# ",
        " #.######.#.######.# ",
        " #.................# ",
        " ################### "
    };

    std::array<std::array<Cell, mapHeight>, mapWidth> map = convert_sketch(mapBuilder);
    draw_map(map, *this->window);

    this->pacman.render(this->window);

    for (auto i : this->fruits) {        
        i.render(*this->window);
    }

    this->window->display();
}

