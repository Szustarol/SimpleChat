CC=gcc
CFLAGS=-Wall `pkg-config --cflags gtk+-3.0`
CLIBS=`pkg-config --libs gtk+-3.0`
BD=build/

simplechat.run: $(BD)main.o
	$(CC) $(CFLAGS) $(BD)*.o -o simplechat.run $(CLIBS)

$(BD)main.o: main.c $(BD)windowsetup.o
	$(CC) $(CFLAGS) -c main.c -o $(BD)main.o

$(BD)windowsetup.o: GUI/windowsetup.c
	$(CC) $(CFLAGS) -c GUI/windowsetup.c -o $(BD)windowsetup.o

clean:
	rm simplechat.run
	rm $(BD)*.o
