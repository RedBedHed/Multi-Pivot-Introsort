CC = g++
CFLAGS = -O3 -flto -pipe -DNDEBUG -Wall -march=native  
O = main.o sort.o

erg: $(O)
	$(CC) $(CFLAGS) -o $@ $(O)
main.o: main.cpp sort.h
	$(CC) $(CFLAGS) -c main.cpp
sort.o: sort.cpp sort.h
	$(CC) $(CFLAGS) -c sort.cpp