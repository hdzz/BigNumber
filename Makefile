CC = g++
CFLAGS = -std=c++11 -Wall -O3 -pthread

obj:main.cpp BigNumber.o
	$(CC) $(CFLAGS) -o obj main.cpp BigNumber.o

BigNumber.o:BigNumber.cpp
	$(CC) $(CFLAGS) -c BigNumber.cpp

clean:
	rm obj *.o