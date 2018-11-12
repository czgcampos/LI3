CC = gcc
CFLAGS = -Wall


#dois targets diferentes por modulo

program_out: stdout.o program.o
	$(CC) $(CFLAGS) -o program stdout.o program.o

program_log: logger.o program.o
	$(CC) $(CFLAGS) -o program logger.o program.o

#-------------------------------------------------------
PUM: list_stack.o program2.o
	$(CC) $(CFLAGS) -o program2 list_stack.o program2.o

list_stack.o:
	$(CC) $(CFLAGS) -c list_stack.c

program2.o:
	$(CC) $(CFLAGS) -c program2.c
#-------------------------------------------------------

#-------------------------------------------------------
HELLO: array_stack.o program2.o
	$(CC) $(CFLAGS) -o program2 array_stack.o program2.o

array_stack.o:
	$(CC) $(CFLAGS) -c array_stack.c

program2.o:
	$(CC) $(CFLAGS) -c program2.c
#-------------------------------------------------------

#modulo stdout

stdout.o:
	$(CC) $(CFLAGS) -c stdout.c

#modulo logger

logger.o:
	$(CC) $(CFLAGS) -c logger.c

program.o:
	$(CC) $(CFLAGS) -c program.c

clean:
	rm *.o log program
