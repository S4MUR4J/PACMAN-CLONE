#include "Fruit.h"

void Fruit::initShape(const sf::RenderWindow& window, float x, float y) {
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOutlineThickness(0.5f);
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setRadius(8.f);
    this->shape.setPosition(sf::Vector2f(x, y));
}

Fruit::Fruit(const sf::RenderWindow& window, float x, float y) {
    this->initShape(window, x, y);
}

Fruit::~Fruit() {

}

const sf::CircleShape Fruit::getShape() const {
    return this->shape;
}

void Fruit::update() {

}

void Fruit::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}
