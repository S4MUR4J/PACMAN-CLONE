#include "SpecialFruit.h"
/**
 * Funkcja odpowiadająca za inicjację podstawowych parametrów specjalnego
 * owocu, takich jak kolor, średnica, oraz pozycja
 * 
 * @param window okno na, którym będzie specjalny owoc
 * @param x pozycja w osi X specjalnego owocu
 * @param y pozycja w osi X specjalnego owocu
 */
void SpecialFruit::initShape(const sf::RenderWindow &window, float x, float y)
{
    this->shape.setFillColor(sf::Color::White);
    this->shape.setRadius(12.f);
    this->shape.setPosition(sf::Vector2f(x - this->shape.getRadius()/2, y - this->shape.getRadius()/2));
    
}

/**
 * Kontruktor obiektu specjalnego owoca, wywołujący inicjację podstawowych
 * parametrów obiektu
 * 
 * @param window okno na, którym będzie rysowany specjalny owoc
 * @param x pozycja w osi X specjalnego owocu
 * @param y pozycja w osi X specjalnego owocu
 */
SpecialFruit::SpecialFruit(const sf::RenderWindow &window, float x, float y) : Fruit(window, x, y)
{
    this->initShape(window, x, y);
}

/**
 * Destruktor specjalnego owocu
 */
SpecialFruit::~SpecialFruit()
{
}

/**
 * Funkcja to getter shape'u tego obiektu
 * 
 * @return const sf::CircleShape zwracany shape obiektu
 */
const sf::CircleShape SpecialFruit::getShape() const
{
    sf::CircleShape result = getShapeTemplate<sf::CircleShape>(this->shape);
    return result;
}

/**
 * Funkcja odpowiadająca za rysowanie na ekranie specjalnego owocu
 * 
 * @param target ekran na którym będzie renderowany specjalny owoc
 */
void SpecialFruit::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}