CC      = g++
CFLAGS  = -std=c++98 -g -c -Wall
CCHECK  = cppcheck
CHKFLAG = --enable=all

all : CollateRecords.o
	$(CC) -o CollateRecords CollateRecords.o
	
CollateRecords.o : CollateRecords.cpp
	$(CCHECK) $(CHKFLAG) CollateRecords.cpp
	$(CC) $(CFLAGS) CollateRecords.cpp
	
clean :
	rm CollateRecords.o

run :
	./CollateRecords
	
debug :
	gdb CollateRecords
