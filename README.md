# Mucha Maciej - Doom dla opornych

### Zarządzanie aplikacją

- ESC - Wyłączenie okna

### Sterowanie duchem

- W - poruszanie się do góry
- S - poruszanie się do dołu
- A - poruszanie się w lewo
- D - poruszanie się w prawo

### Sterowanie graczem

- Strzałka do góry - poruszanie się do góry
- Strzałka do dołu - poruszanie się do dołu
- Strzałka w lewo - poruszanie się w lewo
- Strzałka w prawo - poruszanie się w prawo

### Kompilacja

- g++ -IC:\SFML-2.5.1\include -c src/main.cpp -o Main.o
- g++ -IC:\SFML-2.5.1\include -c src/Fruit.cpp -o Fruit.o
- g++ -IC:\SFML-2.5.1\include -c src/SpecialFruit.cpp -o SpecialFruit.o
- g++ -IC:\SFML-2.5.1\include -c src/Ghost.cpp -o Ghost.o
- g++ -IC:\SFML-2.5.1\include -c src/Pacman.cpp -o Pacman.o
- g++ -IC:\SFML-2.5.1\include -c src/Game.cpp -o Game.o
- g++ -IC:\SFML-2.5.1\include -c src/Map.cpp -o map.o
- g++ -LC:\SFML-2.5.1\lib Main.o Fruit.o SpecialFruit.o Ghost.o Pacman.o Game.o map.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows