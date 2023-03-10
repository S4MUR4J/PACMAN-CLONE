https://www.reddit.com/r/cpp_questions/comments/wo15qf/issue_with_an_sfml_project_cannot_specify_o_with/
Automatic sfml files code to search for

g++ -IC:\SFML-2.5.1\include -c main.cpp -o main.o
g++ -IC:\SFML-2.5.1\include -c Game.cpp -o Game.o
g++ -LC:\SFML-2.5.1\lib .\main.o .\Game.o  -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows