Komplacja - g++ test.cpp -o app.exe 
Otwarcie - .\app.exe

g++ -IC:\SFML-2.5.1\include -c test.cpp -o test.o
g++ -LC:\SFML-2.5.1\lib .\test.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

system("pause")

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

We can use namespace std and sf or go sf::

// Just some random stuff
    std::cout << "Hello my SFML program works!" << "n";
    system("pause");
    return 0;