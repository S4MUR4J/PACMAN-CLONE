#include<iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

const int width = 1920;
const int height = 1080;

int main()
{
    // Setup game window that is event
    sf::RenderWindow window(sf::VideoMode(width, height), "Pac - Man", sf::Style::Titlebar | sf::Style::Close);
    sf::CircleShape shape(50.0f);
    sf::Event event;

    // Loop in which one game must go on
    while(window.isOpen())
    {
        // Event Polling
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
            }
        }

        // Update

        // Render screen
        window.clear(sf::Color::Green); // Throw old frame to trashbin ||| sf::Color(0, 0 ,0)
        window.draw(shape);
        window.display(); // Draw a new grame 
    } 
    // Close this app forever :O
    return 0;
}