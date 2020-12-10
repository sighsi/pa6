prog: main.o
	g++ main.o -g -Wall -lboost_system -lcrypto -lssl -lcpprest -pthread -lsfml-graphics -lsfml-window -lsfml-system -o my_game
main.o: main.cpp
	g++ -c main.cpp

clean:
	-rm *.o
run:
	@./my_game
