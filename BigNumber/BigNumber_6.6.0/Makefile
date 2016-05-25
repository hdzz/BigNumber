CC = g++
CFLAGS = -std=c++11 -Wall -O3

obj:main.cpp BigNumber.o
	$(CC) $(CFLAGS) -pthread -o obj main.cpp BigNumber.o

BigNumber.o:BigNumber.cpp
	$(CC) $(CFLAGS) -c BigNumber.cpp

clean:
	rm *.o obj
