#include "Ghost.h"

/**
 * Funkcja odpowiadająca za inicjację podstawowych zmiennych potrzebnych
 * do rozpoczęcia działań na obiekcie
 */
void Ghost::initVariables() {
    this->movementSpeed = 1.f;
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

/**
 * Funkcja ta posiada logikę poruszania sie ducha, który śledzi naszego gracza.
 * 
 * @param x - aktualne położenie gracza w osi X
 * @param y - aktualne położenie gracza w osi Y
 */
void Ghost::moveGhost(float x, float y)
{
    float ghostX = this->shape.getPosition().x;
    float ghostY = this->shape.getPosition().y;

    if (!this->feared) {
        this->shape.move(-this->movementSpeed, -this->movementSpeed);
        return;
    }

    if (ghostX > x)
        this->shape.move(-this->movementSpeed, 0.f);
    if (ghostX < x)
        this->shape.move(this->movementSpeed, 0.f);
    if (ghostY > y)
        this->shape.move(0.f, -this->movementSpeed);
    if (ghostY < y)
        this->shape.move(0.f, this->movementSpeed);
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
