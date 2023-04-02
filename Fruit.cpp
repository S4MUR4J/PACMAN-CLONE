#include "Headers\Fruit.h"

void Fruit::initShape(const sf::RenderWindow& window) {
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setOutlineThickness(0.1f);
    this->shape.setOutlineColor(sf::Color::Green);
    this->shape.setRadius(10.f);
    this->shape.setPosition(
        sf::Vector2f(
            static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width), 
			static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
        )
    );
}

Fruit::Fruit(const sf::RenderWindow& window) {
    this->initShape(window);
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
