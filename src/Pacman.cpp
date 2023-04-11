#include "Pacman.h"

/**
 * W funkcji następuje inicjacja podstawowych zmiennych potrzebnych do rozpoczęcia 
 * działań na obiekcie
 */
void Pacman::initVariables() {
    this->movementSpeed = 1.f;
    this->moveDirection = STOP;
    this->boosted = false;
    this->prevDir = STOP;
    this->nextPosX = static_cast<int>(round(this->shape.getPosition().x / cellSize));
    this->nextPosY = static_cast<int>(round(this->shape.getPosition().y / cellSize));
}

/**
 * Inicjacja wyglądu obiektu klasy, ustawienie koloru i średnicy
 */
void Pacman::initShapes() {
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setRadius(16.f);
}

/**
 * Konstruktor tworzący obiekt gracza
 * 
 * @param x pozycja startowa gracza na osi X 
 * @param y pozycja startowa gracza na osi X 
 */
Pacman::Pacman(float x, float y) {
    this->shape.setPosition(x, y);
    this->initVariables();
    this->initShapes();
}

/**
 * Destuktor obiektu
 */
Pacman::~Pacman() {
    
}

/**
 * Funkcja jest getter'em Shape'u pacmana wykorzystywana do logiki w silniku 
 *
 * 
 * @return const sf::CircleShape& - zwracany shape obiektu
 */
const sf::CircleShape & Pacman::getShape() const {
    return this->shape;
}

/**
 * Funkcja jest getter'em informacji o interakcji z specjalnym owocem
 * 
 * @return true nasz gracz ma boost spowodowanego zjedzeniem specjalnego owocu
 * @return false nasz gracz nie ma boost'u czyli nie zjadł specjalnego owacu
 */
bool Pacman::isBoosted()
{
    return this->boosted;
}

/**
 * Funkcja daje nam informacje na temat możliwości zmiany kierunku spowodowana
 * miejscem położenia na gridzie. Jeśli nasz gracz znajduje się blisko zakrętu
 * 
 * @return true gracz moze zmienić kierunek
 * @return false gracz nie może zmienić kierunku
 */
bool Pacman::canChangeDir()
{
    if(abs(this->shape.getPosition().x / cellSize - round(this->shape.getPosition().x / cellSize)) < 0.1f &&
        abs(this->shape.getPosition().y / cellSize - round(this->shape.getPosition().y / cellSize)) < 0.1f) {
        return true;
    }
    return false;
}

/**
 * Funkcja ta zbiera informacje z klawiatury na temat wyboru użytkownika programu
 * w, którą stronę decyduje się iść. Tak samo ma zmienna changed, która pomaga nam w
 * przypadku gdy nie możemy skręcić wtedy postać wraca do poprzedniego kierunku. Ściśle 
 * powiązana z funkcją updateInput().
 */
void Pacman::railMoveHelper()
{
    bool changed = 0;
    MoveDirection prevDirection = this->moveDirection;

    if(!this->canChangeDir()) {
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Left
    {
        this->moveDirection = LEFT;
        changed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Right
    {
        this->moveDirection = RIGHT;
        changed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Down
    {
        this->moveDirection = BOTTOM;
        changed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // Up
    {
        this->moveDirection = TOP;
        changed = true;
    }

    if (changed) {
        changed = false;
        this->prevDir = prevDirection;
    }
}

/**
 * W tej funkcji zgodnie z wybranym kierunkiem jest poruszany gracz po mapie, w
 * zależności od kierunku jego pozycję zbieramy w inny sposób do currentX, ze wględu
 * na działanie samego sfml'a. Jeśli naprzeciw kierunku gracza jest ściana ten się zatrzymuje.
 */
void Pacman::updateInput() {

    if (this->moveDirection == RIGHT || moveDirection == BOTTOM) {
        this->currentX = static_cast<int>((this->shape.getPosition().x - this->shape.getRadius()/2) / cellSize);
        this->currentY = static_cast<int>((this->shape.getPosition().y - this->shape.getRadius()/2) / cellSize);
    } else {
        this->currentX = static_cast<int>((this->shape.getPosition().x + this->shape.getRadius()*2) / cellSize);
        this->currentY = static_cast<int>((this->shape.getPosition().y + this->shape.getRadius()*2) / cellSize); 
    }

    this->nextPosX = this->currentX;
    this->nextPosY = this->currentY;

    if (this->moveDirection == LEFT) { 
        this->nextPosX = this->currentX -1;
        if(map[nextPosY][nextPosX] != 1) {
            this->shape.move(-this->movementSpeed, 0);
        }
        else
            this->moveDirection = this->prevDir;
    }
    if (this->moveDirection == RIGHT) {
        this->nextPosX = this->currentX + 1;
        if(map[nextPosY][nextPosX] != 1) {
            this->shape.move(this->movementSpeed, 0);
        }
        else
            this->moveDirection = this->prevDir;
    }
    if (this->moveDirection == BOTTOM) {
        this->nextPosY = this->currentY + 1;
        if(map[nextPosY][nextPosX] != 1) 
        {
            this->shape.move(0, this->movementSpeed);
        }
        else
            this->moveDirection = this->prevDir;
    }
    if (this->moveDirection == TOP) {
        this->nextPosY = this->currentY - 1;
        if(map[nextPosY][nextPosX] != 1) {
            this->shape.move(0, -this->movementSpeed);
        } 
        else
            this->moveDirection = this->prevDir;
    }   
    
}

/**
 * Funkcja ta to timer zgodnie z jego ustawieniem zmniejszamy czas aż dojdziemy do zera.
 * Ściśle związana z funkcja boost, którą wywołuje po upłynięciu czasu wyłączając boost
 */
void Pacman::boostTimer()
{
    if(this->timer > 0) {
        this->timer--;
    } else 
        boost(false);
}

/**
 * Funkcja ta przetrzymuje logikę aktywowania, dezaktywowania boost'u w zależności
 * od parametru. Tak samo ustawia timer jego działania
 * 
 * @param active tu przy wywołaniu przekazujemy czy wyłączamy (false) czy włączamy boost (true)
 */
void Pacman::boost(bool active)
{
    if (active) {
        this->timer = static_cast<unsigned>(1000.f);
        this->boosted = true;
        this->movementSpeed = 2.f;
    }
    else {
        this->boosted = false;
        this->movementSpeed = 1.f;
    }   
}

/**
 * Funkcja ta jeśli znajdujemy się na krawędzi mapy na osi X (mamy dwa takie tunele)
 * przenosi nas na druga stronę tunelu.
 * 
 * @param target ekran po po którym porusza się obiekt
 */
void Pacman::updateTeleportOnEdge(const sf::RenderTarget *target) {
    if (this->shape.getGlobalBounds().left <= 0.f) {   
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top); 
    }
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x + 0.1f) {
        this->shape.setPosition(0.1f, this->shape.getGlobalBounds().top);
    }
}

/**
 * Aktualizacja całej logiki wywoływania funkcji w pętli programu
 * 
 * @param target parametr potrzebny nam do zdobycia wielkości ekranu
 */
void Pacman::update(const sf::RenderTarget * target) {
    //std::cout << "Pos X: " << this->shape.getPosition().x << "Pos Y: " << this->shape.getPosition().y << std::endl;
    this->boostTimer();
    this->railMoveHelper();
    this->updateInput();
    this->updateTeleportOnEdge(target);
}

/**
 * Funkcja drukuje nam obiekt tej klasy na ekranie
 * 
 * @param target ekran na, którym drukujemy
 */
void Pacman::render(sf::RenderTarget * target) {
    target->draw(this->shape);
}
