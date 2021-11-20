

#manager_debug : $(TARGETS)
#manager_debug : OPTION = -DDEBUG_MODE

game : main.cpp Array.o Manager.o Referee.o
	g++ -o game main.cpp Array.o Manager.o Referee.o

Array.o : Array.h Array.cpp
	g++ -c Array.cpp

Referee.o : Referee.h Referee.cpp default.h Array.h
	g++ -c Referee.cpp

Manager.o : Manager.h Manager.cpp default.h Referee.h
	g++ -c Manager.cpp

clean :
	rm *.o game
