#include "Player.h"

void Player::initVariables()
{
    this->movementSpeed = 10.f;
}

void Player::initShapes()
{
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
    this->shape.setPosition(x, y);

    this->initVariables();
    this->initShapes();
}

Player::~Player()
{

}

void Player::updateInput()
{   
    // Keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Left
    {
        this->shape.move(-this->movementSpeed, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Right
    {
        this->shape.move(this->movementSpeed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Down
    {
        this->shape.move(0.f, this->movementSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Up
    {
        this->shape.move(0.f, -this->movementSpeed);
    }
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
    sf::FloatRect playerBounds = this->shape.getGlobalBounds();
    // // Left / Right collision
    // if (playerBounds.left <= 0.f)
    //     this->shape.setPosition(0.f, playerBounds.left);
    // else if (playerBounds.left + playerBounds.width >= target->getSize().x);
    //     this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
    
    // // Top / Down collision
    // if (playerBounds.top <= 0.f)
    //     this->shape.setPosition(playerBounds.left, 0.f);
    // else if (playerBounds.top + playerBounds.height >= target->getSize().y);
    //     this->shape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);
    if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	//Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	//Top
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	//Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
    this->updateInput();
    
    // Window bounds collision
    this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
