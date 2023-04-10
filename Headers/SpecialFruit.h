#pragma once
#include "Fruit.h"

/**
 * @class SpecialFruit
 * 
 * Klasa przechowyjąca informacje na temat specjalnych owoców. Odpowiada za ustawienie
 * parametów tego obiektu, aktualizacje ich oraz rysowanie na ekranie.
 */
class SpecialFruit : public Fruit {
private:
    sf::CircleShape shape;
    
    void initShape(const sf::RenderWindow& window, float x, float y);
public:
    SpecialFruit(const sf::RenderWindow& window, float x, float y);
    virtual ~SpecialFruit();

    const sf::CircleShape getShape() const;

    void render(sf::RenderTarget& target) override;
};