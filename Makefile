prog: main.o
	g++ main.o functions.o -g -Wall -lboost_system -lcrypto -lssl -lcpprest -pthread -lsfml-graphics -lsfml-window -lsfml-system -o my_game
main.o: main.cpp button.h functions.h functions.cpp
	g++ -c main.cpp
functions.o: functions.h functions.cpp
	g++ -c functions.cpp
clean:
	-rm *.o
run:
	@./my_game