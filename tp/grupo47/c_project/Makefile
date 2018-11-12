CC = gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
CLIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

program: Menu.o Parser.o myStruct.o program.o Artigos.o Pagina.o Revisao.o Colaborador.o Colaboradores.o
	$(CC) $(CFLAGS) -o program Menu.o Parser.o myStruct.o program.o Artigos.o Pagina.o Revisao.o Colaborador.o Colaboradores.o $(CLIBS)

Menu.o:
	$(CC) $(CFLAGS) -c Menu.c $(CLIBS)

Parser.o:
	$(CC) $(CFLAGS) -c Parser.c $(CLIBS)

myStruct.o:
	$(CC) $(CFLAGS) -c myStruct.c $(CLIBS)

program.o:
	$(CC) $(CFLAGS) -c program.c $(CLIBS)

Artigos.o:
	$(CC) $(CFLAGS) -c Artigos.c $(CLIBS)

Pagina.o:
	$(CC) $(CFLAGS) -c Pagina.c $(CLIBS)

Revisao.o:
	$(CC) $(CFLAGS) -c Revisao.c $(CLIBS)

Colaborador.o:
	$(CC) $(CFLAGS) -c Colaborador.c $(CLIBS)

Colaboradores.o:
	$(CC) $(CFLAGS) -c Colaboradores.c $(CLIBS)

remove:
	rm program

clean: remove
	rm *.o