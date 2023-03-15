g++ -IC:\SFML-2.5.1\include -c main.cpp -o main.o
g++ -IC:\SFML-2.5.1\include -c Game.cpp -o Game.o
g++ -IC:\SFML-2.5.1\include -c Player.cpp -o Player.o
g++ -LC:\SFML-2.5.1\lib .\main.o .\Game.o .\Player.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows
.\app.exe