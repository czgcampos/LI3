CC = gcc
CFLAGS = -Wall -g

#programa principal

program: person
	$(CC) $(CFLAGS) program.c -o program person.o

#modulo person
person:
	$(CC) $(CFLAGS) -c person.c 

clean:
	rm program person.o

