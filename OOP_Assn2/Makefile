assn2.exe: member.o vote.o menuParser.o main.o
	g++ -o assn2.exe member.o vote.o menuParser.o main.o

member.o: default.h member.h member.cpp
	g++ -c member.cpp

vote.o: default.h vote.h vote.cpp
	g++ -c vote.cpp

menuParser.o: default.h member.h vote.h menuParser.o
	g++ -c menuParser.cpp

main.o: default.h member.h vote.h main.o
	g++ -c main.cpp


