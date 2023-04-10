#include "Pacman.h"

void Pacman::initVariables() {
    this->movementSpeed = 1.f;
    this->moveDirection = STOP;
    this->boosted = false;
    this->prevDir = STOP;
    this->nextPosX = static_cast<int>(round(this->shape.getPosition().x / cellSize));
    this->nextPosY = static_cast<int>(round(this->shape.getPosition().y / cellSize));
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

bool Pacman::isBoosted()
{
    return this->boosted;
}

bool Pacman::canChangeDir()
{
    if(abs(this->shape.getPosition().x / cellSize - round(this->shape.getPosition().x / cellSize)) < 0.1f &&
        abs(this->shape.getPosition().y / cellSize - round(this->shape.getPosition().y / cellSize)) < 0.1f) {
        return true;
    }
    return false;
}

void Pacman::railMoveHelper()
{
    bool changed = 0;
    MoveDirection prevDirection = this->moveDirection;

    if(!this->canChangeDir()) {
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Left
    {
        this->moveDirection = LEFT;
        changed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Right
    {
        this->moveDirection = RIGHT;
        changed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Down
    {
        this->moveDirection = BOTTOM;
        changed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // Up
    {
        this->moveDirection = TOP;
        changed = true;
    }

    if (changed) {
        changed = false;
        this->prevDir = prevDirection;
    }
}

void Pacman::updateInput() {

    if (this->moveDirection == RIGHT || moveDirection == BOTTOM) {
        this->currentX = static_cast<int>((this->shape.getPosition().x - this->shape.getRadius()/2) / cellSize);
        this->currentY = static_cast<int>((this->shape.getPosition().y - this->shape.getRadius()/2) / cellSize);
    } else {
        this->currentX = static_cast<int>((this->shape.getPosition().x + this->shape.getRadius()*2) / cellSize);
        this->currentY = static_cast<int>((this->shape.getPosition().y + this->shape.getRadius()*2) / cellSize); 
    }

    this->nextPosX = this->currentX;
    this->nextPosY = this->currentY;

    if (this->moveDirection == LEFT) { 
        this->nextPosX = this->currentX -1;
        if(map[nextPosY][nextPosX] != 1) {
            this->shape.move(-this->movementSpeed, 0);
        }
        else
            this->moveDirection = this->prevDir;
    }
    if (this->moveDirection == RIGHT) {
        this->nextPosX = this->currentX + 1;
        if(map[nextPosY][nextPosX] != 1) {
            this->shape.move(this->movementSpeed, 0);
        }
        else
            this->moveDirection = this->prevDir;
    }
    if (this->moveDirection == BOTTOM) {
        this->nextPosY = this->currentY + 1;
        if(map[nextPosY][nextPosX] != 1) 
        {
            this->shape.move(0, this->movementSpeed);
        }
        else
            this->moveDirection = this->prevDir;
    }
    if (this->moveDirection == TOP) {
        this->nextPosY = this->currentY - 1;
        if(map[nextPosY][nextPosX] != 1) {
            this->shape.move(0, -this->movementSpeed);
        } 
        else
            this->moveDirection = this->prevDir;
    }   
    
}

void Pacman::boostTimer()
{
    if(this->timer > 0) {
        this->timer--;
    } else 
        boost(false);
}

void Pacman::boost(bool active)
{
    if (active) {
        this->timer = static_cast<unsigned>(1000.f);
        this->boosted = true;
        this->movementSpeed = 2.f;
    }
    else {
        this->boosted = false;
        this->movementSpeed = 1.f;
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
    //std::cout << "Pos X: " << this->shape.getPosition().x << "Pos Y: " << this->shape.getPosition().y << std::endl;
    this->boostTimer();
    this->railMoveHelper();
    this->updateInput();
    this->updateTeleportOnEdge(target);
}

void Pacman::render(sf::RenderTarget * target) {
    target->draw(this->shape);
}
