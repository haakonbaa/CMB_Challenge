output: main.o
	g++ -std=c++11 -Wall main.o -o output
	./output

main.o: main.cpp randomengine.h
	g++ -c -Wall -I. main.cpp -o main.o

clean:
	rm *.o output