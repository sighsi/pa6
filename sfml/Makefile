prog: main.o funcs.o
	g++ main.o funcs.o -g -Wall -lsfml-graphics -lsfml-window -lsfml-system -o my_game
main.o: main.cpp button.h textbox.h
	g++ -c main.cpp
funcs.o: funcs.cpp funcs.h strings.h
	g++ -c funcs.cpp
clean:
	-rm *.o
run:
	@./my_game