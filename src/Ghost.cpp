#include "Ghost.h"

void Ghost::initVariables() {
    this->movementSpeed = 1.f;
}

void Ghost::initShapes(float x, float y) {
    this->shape.setFillColor(sf::Color::Magenta);
    this->shape.setSize(sf::Vector2f(24.f, 24.f));
    this->shape.setPosition(sf::Vector2f(x, y));
}

Ghost::Ghost(const sf::RenderWindow& window, float x, float y)
{
    this->initVariables();
    this->initShapes(x, y);
}

Ghost::~Ghost()
{
}

sf::RectangleShape Ghost::getShape()
{
    return this->shape;
}

void Ghost::moveGhost()
{
    this->shape.setPosition(this->shape.getPosition().x + 1, 0.f);
}

void Ghost::update()
{
    this->moveGhost();
}

void Ghost::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}
