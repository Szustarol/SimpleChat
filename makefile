CC=gcc
CFLAGS=-Wall `pkg-config --cflags gtk+-3.0` -g
CLIBS=`pkg-config --libs gtk+-3.0` -lX11 -lpthread
BD=build/

simplechat.run: $(BD)main.o
	$(CC) $(CFLAGS) $(BD)*.o -o simplechat.run $(CLIBS)

$(BD)main.o: main.c $(BD)windowsetup.o $(BD)serverloop.o $(BD)clientloop.o $(BD)programdata.o
	$(CC) $(CFLAGS) -c main.c -o $(BD)main.o

$(BD)serverloop.o: SERVER/serverloop.c $(BD)programdata.o
	$(CC) $(CFLAGS) -c SERVER/serverloop.c -o $(BD)serverloop.o

$(BD)clientloop.o: CLIENT/clientloop.c $(BD)programdata.o $(BD)contentupdate.o
	$(CC) $(CFLAGS) -c CLIENT/clientloop.c -o $(BD)clientloop.o

$(BD)windowsetup.o: GUI/windowsetup.c $(BD)programdata.o $(BD)windowhandlers.o
	$(CC) $(CFLAGS) -c GUI/windowsetup.c -o $(BD)windowsetup.o

$(BD)contentupdate.o: GUI/contentupdate.c $(BD)programdata.o
	$(CC) $(CFLAGS) -c GUI/contentupdate.c -o $(BD)contentupdate.o

$(BD)windowhandlers.o:	GUI/windowhandlers.c $(BD)programdata.o
	$(CC) $(CFLAGS) -c GUI/windowhandlers.c -o $(BD)windowhandlers.o

$(BD)programdata.o: programdata.c
	$(CC) $(CFLAGS) -c programdata.c -o $(BD)programdata.o

clean:
	rm simplechat.run
	rm $(BD)*.o
