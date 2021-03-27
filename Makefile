CC = g++
	CFLAGS  = -Wall -O2

default: utm

utm:  main.cpp
	$(CC) $(CFLAGS) -o utm main.cpp

clean: 
	$(RM) utm *.o *~
