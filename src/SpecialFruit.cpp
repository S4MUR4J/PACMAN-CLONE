#include "SpecialFruit.h"

void SpecialFruit::initShape(const sf::RenderWindow &window, float x, float y)
{
    this->shape.setFillColor(sf::Color::White);
    this->shape.setRadius(8.f);
    this->shape.setPosition(sf::Vector2f(x - this->shape.getRadius()/2, y - this->shape.getRadius()/2));
}

SpecialFruit::SpecialFruit(const sf::RenderWindow &window, float x, float y)
{
    this->initShape(window, x, y);
}

SpecialFruit::~SpecialFruit()
{
}

const sf::CircleShape SpecialFruit::getShape() const
{
    return this->shape;
}

void SpecialFruit::update()
{
}

void SpecialFruit::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}
