all: server.out client.out

server.out: server.o main.o Data.o KNN.o Calculator.o 
	g++ -std=c++11 main.o Data.o KNN.o Calculator.o server.o -o server.out

client.out: client.o
	g++ -std=c++11 client.o -o client.out

main.o: main.cpp header.h Data.h
	g++ -std=c++11 -c main.cpp

Data.o: Data.cpp Data.h header.h
	g++ -std=c++11 -c Data.cpp

KNN.o: KNN.cpp header.h
	g++ -std=c++11 -c KNN.cpp

Calculator.o: Calculator.cpp header.h
	g++ -std=c++11 -c Calculator.cpp

server.o: server.cpp header.h
	g++ -std=c++11 -c server.cpp

client.o: client.cpp
	g++ -std=c++11 -c client.cpp
	
clean:
	rm *.o
