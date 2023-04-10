#include "Game.h"

/**
 * Inicjacja podstawowych zmiennych gry takich jak stan gry i punktacja
 */
void Game::initVariables() {
    this->endGame = false;
    this->points = 0;
}

/**
 * Funkcja unicjująca tablicę przechowującej wszystkie bloki mapy, na podstawie szkicu mapu
 */
void Game::initMapTiles()
{
    for(int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            if (sketch[j][i] == 1)
                this->mapTiles.push_back(Map(*this->window, i * cellSize, j * cellSize));
        }
    }
}

/**
 * Funkcja unicjująca tablicę przechowującej wszystkie owoce i owoce specjalne,
 *  na podstawie szkicu mapu
 */
void Game::initFruits() {
    for(int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            if (sketch[j][i] == 0)
                this->fruits.push_back(Fruit(*this->window, i * cellSize + 20.f, j * cellSize + 20.f));
            if (sketch[j][i] == 3)
                this->specialFruits.push_back(SpecialFruit(*this->window, i * cellSize + 20.f, j * cellSize + 20.f));
            if(sketch[j][i] == 7)
                this->ghosts.push_back(Ghost(*this->window, i * cellSize + 14.f, j * cellSize + 14.f));
        }
    }
}

/**
 * Inicjacja okna gry, ustawianie jego wielkości, limitu klatek na sekundę i jego
 * przycisków takich jak minimalizacja zamknięcie.
 */
void Game::initWindow() {
    this->videoMode.width = mapWidth * cellSize;
    this->videoMode.height = mapHeight * cellSize;
    this->window = new sf::RenderWindow(this->videoMode, "Pac-Man", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(165);
}

/**
 * Funkcja ta przechowuje logikę kończenia gry dzieję się to gdy zjemy wszystkie owoce
 * i wszystkie owoce specjalne uznajemy wtedy to za wygraną grę
 */
void Game::manageEndGame()
{
    if(this->fruits.empty() && this->specialFruits.empty()) {
        this->endGame = true;
    }
    for (size_t i = 0; i < this->ghosts.size(); i++) {
        if (this->pacman.getShape().getGlobalBounds().intersects(this->ghosts[i].getShape().getGlobalBounds())) {
            if (!this->pacman.isBoosted())
                this->endGame = true;
        }
    }
}

/**
 * Konstruktor klasy silnika gry inicjuje zmienne, budowę mapy, ustawienie owoców i okna
 */
Game::Game() {
    this->initVariables();
    this->initMapTiles();
    this->initFruits();
    this->initWindow();
}

/**
 * Destruktor klasy silnika gry usuwa okno i zamyka aplikacje
 */
Game::~Game() {
    delete this->window;
}

/**
 * Funkcja ta to getter infromacji o ostanie gry
 * 
 * @return true - gra została skończona
 * @return false - gra nie została skończona
 */
const bool Game::getEndGame() const {
    return this->endGame;
}

/**
 * Funkcja przekazuje informacje na temat stanu gry, czy jest w trakcie działania 
 * czy została właśnie ukończona przez przegranie lub zamknięcie okna
 * 
 * @return true - gra się toczy
 * @return false - gra została skończona
 */
const bool Game::executing() const {
    return this->window->isOpen() && this->endGame == false;
}

/**
 * Funkcja sprawdzająca eventy, w celu zamknięcia okna. Jeśli klikniemy ESC lub
 * gra zostanie ukończona zamykamy działanie programu i okno.
 */
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

/**
 * W tej funkcji sprawdzamy kolizję między obiektami gry, takimi jak owoce, 
 * specjalne owoce i gracz. W przypadku owoców pozwala nam na ich podniesienia
 * i zwiększenie punktacji.
 */

void Game::updateCollision() {
    for (size_t i = 0; i < this->fruits.size(); i++) {
        if (this->pacman.getShape().getGlobalBounds().intersects(this->fruits[i].getShape().getGlobalBounds())) {
            this->points++;
            this->fruits.erase(this->fruits.begin() + i);
        }
    }
    for (size_t i = 0; i < this->specialFruits.size(); i++) {
        if (this->pacman.getShape().getGlobalBounds().intersects(this->specialFruits[i].getShape().getGlobalBounds())) {
            this->pacman.boost(true);
            this->points++;
            this->specialFruits.erase(this->specialFruits.begin() + i);
        }
    }
}

/**
 * Aktualizacja wszystkich obiektów i eventów naszego programu, aktualnie również zmieniająca
 * stan przerażenia ducha Wywołujemy to również całą logikę silnika.
 */
void Game::update() {
    this->pollEvents();

    if (this->endGame == false) {
        this->pacman.update(this->window);
        for(size_t i = 0; i < this->ghosts.size(); i++) {
            this->ghosts[i].update(this->window, 
                                this->ghosts[i].getShape().getPosition().x + ghosts[i].getShape().getSize().x/2,
                                this->ghosts[i].getShape().getPosition().y + ghosts[i].getShape().getSize().y/2);
            if(this->pacman.isBoosted())
                this->ghosts[i].Fear(true);
            if(!this->pacman.isBoosted())
                this->ghosts[i].Fear(false);
        }
        this->updateCollision();
        this->manageEndGame();
    }
}

/**
 * Funkcja w, której rysujemy wszystkie obiekty klasy na ekranie. Na początku czyścimy ekran 
 * drukujemy zawartość i czyścimy ekran. Dzieję się to co klatkę.
 */
void Game::render() {
    this->window->clear();

    for (auto i : this->mapTiles) {
        i.render(*this->window);
    }
    for (auto i : this->fruits) {        
        i.render(*this->window);
    }

    for (auto i : this->specialFruits) {        
        i.render(*this->window);
    }

    for (auto i : this->ghosts) {        
        i.render(this->window);
    }
    
    this->pacman.render(this->window);

    this->window->display();
}

