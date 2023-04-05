#include "Pacman.h"

void Pacman::initVariables() {
    this->movementSpeed = 4.f;
    this->moveDirection = STOP;
}

void Pacman::initShapes() {
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setRadius(16.f);
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

void Pacman::wallCollision()
{
    this->currentX = static_cast<int>(round((this->shape.getPosition().x + this->shape.getRadius() / 2) / cellSize));
    this->currentY = static_cast<int>(round((this->shape.getPosition().y + this->shape.getRadius() / 2)/ cellSize));

    if(this->map[this->currentX][this->currentY] == 1) {
        this->shape.setPosition(currentX * cellSize + this->shape.getRadius(), currentY * cellSize + this->shape.getRadius());
        this->moveDirection = STOP;
    } 
}

void Pacman::railMoveHelper()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Left
    {
        this->moveDirection = LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Right
    {
        this->moveDirection = RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Down
    {
        this->moveDirection = BOTTOM;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // Up
    {
        this->moveDirection = TOP;
    }
}

void Pacman::updateInput() {
    this->currentX = static_cast<int>(round(this->shape.getPosition().x / cellSize));
    this->currentY = static_cast<int>(round(this->shape.getPosition().y / cellSize));

    if (map[currentY][currentX] == 1)
    {
        this->shape.setPosition(this->lastX * cellSize + this->shape.getRadius()/2, this->lastY * cellSize + this->shape.getRadius()/2);
        this->moveDirection = STOP;
        return;
    }

    this->lastX = this->currentX;
    this->lastY = this->currentY;

    if (this->moveDirection == LEFT && map[currentY][currentX--] != 1) {
        this->shape.move(-(cellSize / 48.f), 0);
    }
    if (this->moveDirection == RIGHT && map[currentY][currentX++] != 1) {
        this->shape.move(cellSize / 48.f, 0);
    }
    if (this->moveDirection == BOTTOM && map[currentY++][currentX] != 1) {
        this->shape.move(0, cellSize / 48.f);
    }
    if (this->moveDirection == TOP && map[currentY--][currentX] != 1) {
        this->shape.move(0, -(cellSize / 48.f));
    }
}

void Pacman::updateTeleportOnEdge(const sf::RenderTarget *target) {
    if (this->shape.getGlobalBounds().left <= 0.f) {   
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top); 
    }
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x + 0.1f) {
        this->shape.setPosition(0.1f, this->shape.getGlobalBounds().top);
    }
}

void Pacman::update(const sf::RenderTarget * target) {
    std::cout << "Pos X: " << this->shape.getPosition().x << "Pos Y: " << this->shape.getPosition().y << std::endl;
    this->railMoveHelper();
    //this->wallCollision();
    this->updateInput();
    this->updateTeleportOnEdge(target);
}

void Pacman::render(sf::RenderTarget * target) {
    target->draw(this->shape);
}
