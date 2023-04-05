#include "Fruit.h"

void Fruit::initShape(const sf::RenderWindow& window) {
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOutlineThickness(0.5f);
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setRadius(8.f);
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
