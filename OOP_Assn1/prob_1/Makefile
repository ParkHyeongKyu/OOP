prob_1.exe: main.o compare.o
	g++ -o prob_1.exe main.cpp compare.cpp

main.o: main.cpp prob_1.h
	g++ -c main.cpp

compare.o: compare.cpp prob_1.h
	g++ -c compare.cpp


