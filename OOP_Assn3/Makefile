assn3.exe: groupleader.o groupmember.o member.o vote.o menuParser.o main.o
	g++ -o assn3.exe groupleader.o groupmember.o member.o vote.o menuParser.o main.o

groupleader.o: default.h member.h vote.h group.h groupleader.cpp
	g++ -c groupleader.cpp

groupmember.o: default.h member.h vote.h group.h groupmember.cpp
	g++ -c groupmember.cpp

member.o: default.h member.h vote.h group.h member.cpp
	g++ -c member.cpp

vote.o: default.h vote.h member.h group.h vote.cpp
	g++ -c vote.cpp

menuParser.o: default.h member.h vote.h group.h menuParser.cpp
	g++ -c menuParser.cpp

main.o: default.h member.h vote.h group.h main.cpp
	g++ -c main.cpp


