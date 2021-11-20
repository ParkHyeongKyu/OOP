prob_3.exe: main.o BFS.o makequeue.o
	g++ -o prob_3.exe main.cpp BFS.cpp makequeue.cpp

main.o: main.cpp prob_3.h
	g++ -c main.cpp

BFS.O: BFS.cpp prob_3.h
	g++ -c BFS.cpp

makequeue.o: makequeue.cpp prob_3.h
	g++ -c makequeue.cpp




