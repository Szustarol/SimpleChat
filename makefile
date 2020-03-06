CC=gcc
CFLAGS=-Wall `pkg-config --cflags gtk+-3.0` -g
CLIBS=`pkg-config --libs gtk+-3.0`
BD=build/

simplechat.run: $(BD)main.o
	$(CC) $(CFLAGS) $(BD)*.o -o simplechat.run $(CLIBS)

$(BD)main.o: main.c $(BD)windowsetup.o
	$(CC) $(CFLAGS) -c main.c -o $(BD)main.o

$(BD)windowsetup.o: GUI/windowsetup.c $(BD)programdata.o $(BD)windowhandlers.o
	$(CC) $(CFLAGS) -c GUI/windowsetup.c -o $(BD)windowsetup.o

$(BD)programdata.o: programdata.c
	$(CC) $(CFLAGS) -c programdata.c -o $(BD)programdata.o

$(BD)windowhandlers.o:	GUI/windowhandlers.c
	$(CC) $(CFLAGS) -c GUI/windowhandlers.c -o $(BD)windowhandlers.o

clean:
	rm simplechat.run
	rm $(BD)*.o
