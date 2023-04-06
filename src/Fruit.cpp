#include "Fruit.h"

void Fruit::initShape(const sf::RenderWindow& window, float x, float y) {
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(10.f, 10.f));
    this->shape.setPosition(sf::Vector2f(x, y));
}

Fruit::Fruit(const sf::RenderWindow& window, float x, float y) {
    this->initShape(window, x, y);
}

Fruit::~Fruit() {

}

const sf::RectangleShape Fruit::getShape() const {
    return this->shape;
}

void Fruit::update() {

}

void Fruit::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}
