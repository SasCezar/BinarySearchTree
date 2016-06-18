main.exe: main.o
	g++ main.o -o main.out

main.o: main.cpp bst.h
	g++ -c main.cpp -o main.o