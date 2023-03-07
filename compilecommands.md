Komplacja - g++ test.cpp -o app.exe 
Otwarcie - .\app.exe

g++ -IC:\SFML-2.5.1\include -c test.cpp -o test.o
g++ -LC:\SFML-2.5.1\lib .\test.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows