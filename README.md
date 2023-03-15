###### Mucha Maciej - Doom dla opornych

https://www.reddit.com/r/cpp_questions/comments/wo15qf/issue_with_an_sfml_project_cannot_specify_o_with/
Automatic sfml files code to search for

g++ -IC:\SFML-2.5.1\include -c main.cpp -o main.o
g++ -IC:\SFML-2.5.1\include -c Game.cpp -o Game.o
g++ -LC:\SFML-2.5.1\lib .\main.o .\Game.o  -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

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