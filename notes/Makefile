prog: main.o
	g++ main.o funcs.o -g -Wall -lsfml-graphics -lsfml-window -lsfml-system -o my_game
main.o: main.cpp button.h funcs.h funcs.cpp
	g++ -c main.cpp
funcs.o: funcs.h funcs.cpp
	g++ -c funcs.cpp
clean:
	-rm *.o
run:
	@./my_game