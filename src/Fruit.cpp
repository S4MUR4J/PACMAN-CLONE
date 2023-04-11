#include "Fruit.h"

/**
 * Funkcja odpowiadająca za inicjację podstawowych parametrów owocu, 
 * takich jak kolor, średnica, oraz pozycja
 * 
 * @param window okno na, którym będzie owoc
 * @param x pozycja w osi X owocu
 * @param y pozycja w osi X owocu
 */
void Fruit::initShape(const sf::RenderWindow& window, float x, float y) {
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(10.f, 10.f));
    this->shape.setPosition(sf::Vector2f(x, y));
}

/**
 * Kontruktor obiektu owoca, wywołujący inicjację podstawowych
 * parametrów obiektu
 * 
 * @param window okno na, którym będzie rysowany owoc
 * @param x pozycja w osi X owocu
 * @param y pozycja w osi X owocu
 */
Fruit::Fruit(const sf::RenderWindow& window, float x, float y) {
    this->initShape(window, x, y);
}

/**
 * Destruktor specjalnego owocu
 */
Fruit::~Fruit() {
}

/**
 * Funkcja to getter shape'u tego obiektu
 * 
 * @return const sf::RectangleShape zwracany shape obiektu
 */
const sf::RectangleShape Fruit::getShape() const {
    return this->shape;
}

/**
 * Funkcja odpowiadająca za rysowanie na ekranie owocu
 * 
 * @param target ekran na którym będzie renderowany owoc
 */
void Fruit::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}
