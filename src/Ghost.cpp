#include "Ghost.h"

/**
 * Funkcja odpowiadająca za inicjację podstawowych zmiennych potrzebnych
 * do rozpoczęcia działań na obiekcie
 */
void Ghost::initVariables() {
    this->movementSpeed = 20.f;
    this->moveDir = STOP;
    this->effected = false;
    this->indexX = floor(getPlayerOrigin().x / cellSize);
    this->indexY = floor(getPlayerOrigin().y / cellSize);
    this->nextIndexX = this->indexX;
    this->nextIndexY = this->indexY;
    this->offset = this->shape.getSize().x/2;
}

/**
 * Funkcja odpowiadająca za inicjacje wyglądu obiektu, ustawienie
 * pozycji, koloru i wielkości
 * 
 * @param x położenie ducha w osi X
 * @param y położenie ducha w osi Y
 */
void Ghost::initShapes(float x, float y) {
    this->shape.setFillColor(sf::Color::Magenta);
    this->shape.setSize(sf::Vector2f(24.f, 24.f));
    this->shape.setPosition(sf::Vector2f(x, y));
}


/**
 * Konstruktor tworzący klasę ducha
 * 
 * @param window okno na którym będzie tworzony duch
 * @param x położenie ducha w osi X
 * @param y położenie ducha w osi Y
 */
Ghost::Ghost(const sf::RenderWindow& window, float x, float y)
{
    this->initShapes(x, y);
    this->initVariables();
}

/**
 * Destuktor obiektu ducha
 */
Ghost::~Ghost()
{

}

/**
 * Funkcja to getter shape'u obiektu ducha
 * 
 * @return sf::RectangleShape zwracany shape obiektu
 */
sf::RectangleShape Ghost::getShape()
{
    return this->shape;
}

/**
 * Funkcja ta to getter właściwości przerażenia ducha, czyli stanu gdy gracz
 * zje specjalny owoc
 * 
 * @return true duch jest przerażony
 * @return false duch nie jest przerażony
 */
bool Ghost::isEfected()
{
    return this->effected;
}

/**
 * Funkcja oblicza pozycje globalna ducha według środka i zwraca jej wartość
 * 
 * @return sf::Vector2f wektor położenia środka obiektu
*/
sf::Vector2f Ghost::getPlayerOrigin()
{
    float x = this->shape.getPosition().x + cellSize/4;
    float y = this->shape.getPosition().y + cellSize/4;
    sf::Vector2f origin(x, y);
    return origin;
}

/**
 * Funkcja sprawdza kolejną pozycję na gridzie i ustawia ją do zmiennej w
 * celu kolejnych sprawdzeń w logice poruszania sie
 * 
 * @param movDir aktualny kierunek poruszania się
*/
void Ghost::nextPosition(MoveDirection moveDir) {

    switch(moveDir) {
        case LEFT:
            this->nextIndexX = this->indexX;
            this->nextIndexX--;
            this->nextIndexY = this->indexY;
            break;
        case RIGHT:
            this->nextIndexX = this->indexX;
            this->nextIndexX++;
            this->nextIndexY = this->indexY;
            break;
        case TOP:
            this->nextIndexY = this->indexY;
            this->nextIndexY--;
            this->nextIndexX = this->indexX;
            break;
        case BOTTOM:
            this->nextIndexY = this->indexY;
            this->nextIndexY++;
            this->nextIndexX = this->indexX;
            break;
        default:
            this->nextIndexX = this->indexX;
            this->nextIndexY = this->indexY;
            break;
    }
}

/**
 * Funkcja odpowiadająca za zmianę kierunku poruszania się w zależności od 
 * wczytanego inputu z klawiatury
 * 
 * @param left przycisk do poruszania sie w lewo
 * @param right przycisk do poruszania sie w prawo
 * @param down przycisk do poruszania sie w dół
 * @param top przycisk do poruszania sie w gore
 * @param offset przesunięcie postaci
*/

void Ghost::changeDir(sf::Keyboard::Key left, sf::Keyboard::Key right,
                         sf::Keyboard::Key top, sf::Keyboard::Key down, float offset)
{
    if (sf::Keyboard::isKeyPressed(left)) {
        this->shape.setPosition(this->indexX * cellSize + offset, this->indexY * cellSize + offset);
        this->moveDir = LEFT;
    } 
    else if (sf::Keyboard::isKeyPressed(right)) {
        this->shape.setPosition(this->indexX * cellSize + offset, this->indexY * cellSize + offset);
        this->moveDir = RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(top)) {
        this->shape.setPosition(this->indexX * cellSize + offset, this->indexY * cellSize + offset);
        this->moveDir = TOP;
    }
    else if (sf::Keyboard::isKeyPressed(down)) {
        this->shape.setPosition(this->indexX * cellSize + offset, this->indexY * cellSize + offset);
        this->moveDir = BOTTOM;
    }
}

/**
 * Funkcja ta odpowiada za logikę jaką za sobie niesie bycie w stanie przerażenia i 
 * nie wpływa to na na możliwość zniszczenia gracza i prędkość duch
 * 
 * @param isOff parametr wykorzystywany do aktywacji i dezaaktywacji efektu przerażenia
 */
void Ghost::Effect(bool isOff)
{
    if(!isOff) {
        this->effected = true;
        this->movementSpeed = 0.55f;
    }      
    else {
        this->effected = false;
        this->movementSpeed = 0.1f;
    }

    //std::cout << this->movementSpeed << std::endl;
}

/**
 * Jeśli duch znajdzie się na krawędzi ekranu w osi X zostaje przeniesiony na drugą stronę
 * ekranu
 * 
 * @param target ekran z którego uzyskujemy jego rozmiar
 */
void Ghost::updateTeleportOnEdge(const sf::RenderTarget *target) {
    if (this->nextIndexX < 0 && this->indexX == 0) {   
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top); 
    }
    if (this->nextIndexX > 20 && this->indexX == 20) {
        this->shape.setPosition(0.1f, this->shape.getGlobalBounds().top);
    }
}

/**
 * Funkcja sprawdza sąsiednie pola gridu w celu znalezienia kolizji ze ścianą
 * 
 * @param posX pozycja ducha w osi X
 * @param posY pozycja ducha w osi Y
 * @return true występuje ściana dla podanego kierunku poruszania się
 * @return false nie występuje ściana dla podanego kierunku poruszania się
*/
bool Ghost::collision(float posX, float posY)
{
    bool result = false;

    int gridX = static_cast<int>(floor(posX / cellSize));
    int gridY = static_cast<int>(floor(posY / cellSize));

    switch(this->moveDir) {
        case LEFT:
            if(map[this->nextIndexY][this->nextIndexX] == 1 && 
            abs(this->getPlayerOrigin().x - this->indexX * cellSize - cellSize/2) < 0.5f)
            {
                return true;
            }
            break;
        case RIGHT:
            if(map[this->nextIndexY][this->nextIndexX] == 1 && 
                abs(this->getPlayerOrigin().x - this->indexX * cellSize - cellSize/2) < 0.5f)
            {
                return true;
            }
            break;
        case TOP:
            if(map[this->nextIndexY][this->nextIndexX] == 1 &&
                abs(this->getPlayerOrigin().y - this->indexY * cellSize - cellSize/2) < 0.5f)
            {
                return true;
            }
            break;
        case BOTTOM:
            if(map[this->nextIndexY][this->nextIndexX] == 1 &&
            abs(this->getPlayerOrigin().y - this->indexY * cellSize - cellSize/2) < 0.5f)
            {
                return true;
            }
            break;
    };

    return result;
}

/**
 * Funkcja ta posiada logikę poruszania sie ducha, który porusza się po gridzie, może
 * poruszać się tam gdzie wartość nie wynosi 1.
 * 
 * @param x aktualne położenie gracza w osi X
 * @param y aktualne położenie gracza w osi Y
 */
void Ghost::updateInput(float x, float y)
{
    sf::Vector2f position = this->getPlayerOrigin();
    float ghostX = position.x;
    float ghostY = position.y;
    this->indexX = static_cast<int>(floor((position.x)/ cellSize));
    this->indexY = static_cast<int>(floor((position.y)/ cellSize));

    changeDir(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S, this->offset);
    for (int i = 0; i < 4; i ++) {
        if(i == 0)
            this->collisionTbl[0] = collision(ghostX - movementSpeed, ghostY); // Left
        if(i == 1)
            this->collisionTbl[1] = collision(ghostX + movementSpeed, ghostY); // Right
        if(i == 2)
            this->collisionTbl[2] = collision(ghostX, ghostY - movementSpeed); // Top
        if(i == 3)
            this->collisionTbl[3] = collision(ghostX, ghostY + movementSpeed); // Bottom
    }

    if (!this->effected) {
        return;
    }

    if (this->moveDir == LEFT && this->collisionTbl[0] != true) {
        this->shape.move(-this->movementSpeed, 0.f);
    } 
    else if (this->moveDir == RIGHT && this->collisionTbl[1] != true) {
        this->shape.move(this->movementSpeed, 0.f);
    }
    else if (this->moveDir == TOP && this->collisionTbl[2] != true) {
        this->shape.move(0.f, -this->movementSpeed);
    }
    else if (this->moveDir == BOTTOM && this->collisionTbl[3] != true) {
        this->shape.move(0.f, this->movementSpeed);
    } 
    else {
        this->shape.setPosition(this->indexX * cellSize + 12.f, this->indexY * cellSize + 12.f);
    }
}

/**
 * Funkcja do wywoływania logiki ducha w silniku gry
 * 
 * @param target ekran na którym znajduje się duch
 * @param x aktualne położenie ducha na osi X
 * @param y aktualne położenie ducha na osi Y
 */
void Ghost::update(const sf::RenderTarget * target, float x, float y)
{
    this->updateTeleportOnEdge(target);
    this->nextPosition(this->moveDir);
    this->updateInput(x, y);
}

/**
 * Funkcja odpowiadająca za rysowanie ducha na ekranie
 * 
 * @param target ekran na którym rysowany jest obiekt ducha
 */
void Ghost::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}
