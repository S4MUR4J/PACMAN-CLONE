#include "Headers\Fruit.h"

void Fruit::initShape() {
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setRadius(10.f);
}

Fruit::Fruit(float x, float y) {
    this->shape.setPosition(x, y);
    this->initShape();
}

Fruit::~Fruit() {

}

const sf::CircleShape Fruit::getShape() const {
    return sf::CircleShape();
}

void Fruit::update() {

}

void Fruit::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}
