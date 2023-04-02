#include "Pacman.h"

void Pacman::initVariables() {
    this->movementSpeed = 10.f;
    this->moveDirection = STOP;
}

void Pacman::initShapes() {
    this->shape.setFillColor(sf::Color::Cyan);
    this->shape.setOutlineThickness(0.1f);
    this->shape.setOutlineColor(sf::Color::Green);
    this->shape.setRadius(35.f);
}

Pacman::Pacman(float x, float y) {
    this->shape.setPosition(x, y);
    this->initVariables();
    this->initShapes();
}

Pacman::~Pacman() {
    
}

const sf::CircleShape & Pacman::getShape() const {
    return this->shape;
}

void Pacman::railMoveHelper() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Left
    {
        this->moveDirection = LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Right
    {
        this->moveDirection = RIGHT;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Down
    {
        this->moveDirection = BOTTOM;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Up
    {
        this->moveDirection = TOP;
    }
}

void Pacman::updateInput() {
    if (this->moveDirection == STOP) {
        std::cout << "STOP" << std::endl;
        return;
    }
    if (this->moveDirection == LEFT) {
        this->shape.move(-this->movementSpeed, 0.f);
    }
    if (this->moveDirection == RIGHT) {
        this->shape.move(this->movementSpeed, 0.f);
    }
    if (this->moveDirection == BOTTOM) {
        this->shape.move(0.f, this->movementSpeed);
    }
    if (this->moveDirection == TOP) {
        this->shape.move(0.f, -this->movementSpeed);
    }
}

void Pacman::updateWindowBoundsCollision(const sf::RenderTarget *target) {
    //Left
    if (this->shape.getGlobalBounds().left <= 0.f) {
        this->shape.setPosition(0.1f, this->shape.getGlobalBounds().top);
        this->moveDirection = STOP;
    }
    //Right
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x + 0.1f) {
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
        this->moveDirection = STOP;
    }
    //Top
    if (this->shape.getGlobalBounds().top <= 0.f) {
        this->shape.setPosition(this->shape.getGlobalBounds().left, 0.1f);
        this->moveDirection = STOP;
    }
    //Bottom
    if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y) {
        this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
        this->moveDirection = STOP;
    }
}

void Pacman::update(const sf::RenderTarget * target) {
    this->railMoveHelper();
    this->updateInput();
    this->updateWindowBoundsCollision(target);
}

void Pacman::render(sf::RenderTarget * target) {
    target->draw(this->shape);
}
