CC = g++
	CFLAGS  = -Wall -O2

default: utm

utm:  utm.cpp
	$(CC) $(CFLAGS) -o utm utm.cpp

clean: 
	$(RM) utm *.o *~
