#include "Ghost.h"

/**
 * Funkcja odpowiadająca za inicjację podstawowych zmiennych potrzebnych
 * do rozpoczęcia działań na obiekcie
 */
void Ghost::initVariables() {
    this->movementSpeed = 1.f;
    this->moveDir = STOP;
    this->feared = false;
}

/**
 * Funkcja odpowiadająca za inicjacje wyglądu obiektu, ustawienie
 * pozycji, koloru i wielkości
 * 
 * @param x - położenie ducha w osi X
 * @param y - położenie ducha w osi Y
 */
void Ghost::initShapes(float x, float y) {
    this->shape.setFillColor(sf::Color::Magenta);
    this->shape.setSize(sf::Vector2f(24.f, 24.f));
    this->shape.setPosition(sf::Vector2f(x, y));
}


/**
 * Konstruktor tworzący klasę ducha
 * 
 * @param window - okno na którym będzie tworzony duch
 * @param x - położenie ducha w osi X
 * @param y - położenie ducha w osi Y
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
 * @return sf::RectangleShape - zwracany shape obiektu
 */
sf::RectangleShape Ghost::getShape()
{
    return this->shape;
}

/**
 * Funkcja ta to getter właściwości przerażenia ducha, czyli stanu gdy gracz
 * zje specjalny owoc
 * 
 * @return true - duch jest przerażony
 * @return false - duch nie jest przerażony
 */
bool Ghost::isFeared()
{
    return this->feared;
}

sf::Vector2f Ghost::getPlayerOrigin()
{
    float x = this->shape.getPosition().x + this->shape.getSize().x/2;
    float y = this->shape.getPosition().y + this->shape.getSize().y/2;
    sf::Vector2f origin(x, y);
    return origin;
}

sf::Vector2f Ghost::setPlayerOrigin()
{
    sf::Vector2f origin = getPlayerOrigin();
    if (this->moveDir == LEFT && this->collisionTbl[0] != 1) {
        origin.x = (floor(origin.x/cellSize) - 1) * cellSize + this->shape.getSize().x/2;
        origin.y = floor(origin.y/cellSize) * cellSize + this->shape.getSize().y/2;
    }
    if (this->moveDir == RIGHT && this->collisionTbl[1] != 1) {
        origin.x = (floor(origin.x/cellSize) + 1) * cellSize + this->shape.getSize().x/2;
        origin.y = floor(origin.y/cellSize) * cellSize + this->shape.getSize().y/2;
    }
    if (this->moveDir == TOP && this->collisionTbl[2] != 1) {
        origin.x = floor(origin.x/cellSize) * cellSize + this->shape.getSize().x/2;
        origin.y = (floor(origin.y/cellSize) - 1) * cellSize + this->shape.getSize().y/2;
    }
    if (this->moveDir == BOTTOM && this->collisionTbl[3] != 1) {
        origin.x = floor(origin.x/cellSize) * cellSize + this->shape.getSize().x/2;
        origin.y = (floor(origin.y/cellSize) + 1) * cellSize + this->shape.getSize().y/2;
    }
    
    this->shape.setPosition(origin);
}

void Ghost::changeDir()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->moveDir = LEFT;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->moveDir = RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->moveDir = TOP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->moveDir = BOTTOM;
    }
}

/**
 * Funkcja ta odpowiada za logikę jaką za sobie niesie bycie w stanie przerażenia i 
 * nie wpływa to na na możliwość zniszczenia gracza i prędkość duch
 * 
 * @param isOff - parametr wykorzystywany do aktywacji i dezaaktywacji efektu przerażenia
 */
void Ghost::Fear(bool isOff)
{
    if(!isOff) {
        this->feared = true;
        this->movementSpeed = 0.55f;
    }      
    else {
        this->feared = false;
        this->movementSpeed = 0.1f;
    }

    //std::cout << this->movementSpeed << std::endl;
}

/**
 * Jeśli duch znajdzie się na krawędzi ekranu w osi X zostaje przeniesiony na drugą stronę
 * ekranu
 * 
 * @param target - ekran z którego uzyskujemy jego rozmiar
 */
void Ghost::updateTeleportOnEdge(const sf::RenderTarget *target) {
    if (this->shape.getGlobalBounds().left <= 0.f) {   
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top); 
    }
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x + 0.1f) {
        this->shape.setPosition(0.1f, this->shape.getGlobalBounds().top);
    }
}


bool Ghost::collision(float posX, float posY)
{
    bool result = false;

    int gridX = static_cast<int>(floor(posX / cellSize));
    int gridY = static_cast<int>(floor(posY / cellSize));

    switch(this->moveDir) {
        case LEFT:
            if(map[gridY][gridX--] == 1) {
                return true;
            }
            break;
        case RIGHT:
            if(map[gridY][gridX++] == 1) {
                return true;
            }
            break;
        case TOP:
            if(map[gridY--][gridX] == 1) {
                return true;
            }
            break;
        case BOTTOM:
            if(map[gridY++][gridX] == 1) {
                return true;
            }
            break;
    }

    // std::cout << gridX << " " << gridY << std::endl;

    return result;
}

/**
 * Funkcja ta posiada logikę poruszania sie ducha, który śledzi naszego gracza.
 * 
 * @param x - aktualne położenie gracza w osi X
 * @param y - aktualne położenie gracza w osi Y
 */
void Ghost::moveGhost(float x, float y)
{
    sf::Vector2f position = getPlayerOrigin();
    float ghostX = position.x;
    float ghostY = position.y;

    // std::cout << ghostX << " " << ghostY << std::endl;
    changeDir();
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
    for (int i = 0; i < 4; i++) {
        //std::cout << collisionTbl[i] << " ";
    }
    //std::cout << "\n";

    if (!this->feared) {
        this->shape.move(-this->movementSpeed, -this->movementSpeed);
        return;
    }

    // if(this->moveDir != STOP)
    //     setPlayerOrigin();
    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && collisionTbl[0] != true) {
        this->shape.move(-this->movementSpeed, 0.f);
        this->moveDir = LEFT;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && collisionTbl[1] != true) {
        this->shape.move(this->movementSpeed, 0.f);
        this->moveDir = RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && collisionTbl[2] != true) {
        this->shape.move(0.f, -this->movementSpeed);
        this->moveDir = TOP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && collisionTbl[3] != true) {
        this->shape.move(0.f, this->movementSpeed);
        this->moveDir = BOTTOM;
    }
        
}

/**
 * Funkcja do wywoływania logiki ducha w silniku gry
 * 
 * @param target - ekran na którym znajduje się duch
 * @param x - aktualne położenie ducha na osi X
 * @param y - aktualne położenie ducha na osi Y
 */
void Ghost::update(const sf::RenderTarget * target, float x, float y)
{
    this->updateTeleportOnEdge(target);
    this->moveGhost(x, y);
}

/**
 * Funkcja odpowiadająca za rysowanie ducha na ekranie
 * 
 * @param target - ekran na którym rysowany jest obiekt ducha
 */
void Ghost::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}
