#include "Ghost.h"

void Ghost::initVariables() {
    this->movementSpeed = 1.f;
    this->feared = false;
}

void Ghost::initShapes(float x, float y) {
    this->shape.setFillColor(sf::Color::Magenta);
    this->shape.setSize(sf::Vector2f(24.f, 24.f));
    this->shape.setPosition(sf::Vector2f(x, y));
}

Ghost::Ghost(const sf::RenderWindow& window, float x, float y)
{
    this->initShapes(x, y);
    this->initVariables();
}

Ghost::~Ghost()
{
}

sf::RectangleShape Ghost::getShape()
{
    return this->shape;
}

bool Ghost::isFeared()
{
    return this->feared;
}

void Ghost::Fear(bool isOff)
{
    if(!isOff) {
        this->feared = true;
        this->movementSpeed = 0.1f;
    }      
    else {
        this->feared = false;
        this->movementSpeed = 1.f;
    }
}

void Ghost::updateTeleportOnEdge(const sf::RenderTarget *target) {
    if (this->shape.getGlobalBounds().left <= 0.f) {   
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top); 
    }
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x + 0.1f) {
        this->shape.setPosition(0.1f, this->shape.getGlobalBounds().top);
    }
}

void Ghost::moveGhost()
{
    this->shape.move(this->movementSpeed, 0.f);
}

void Ghost::update(const sf::RenderTarget * target)
{
    this->updateTeleportOnEdge(target);
    this->moveGhost();
}

void Ghost::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}
