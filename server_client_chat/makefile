CC=gcc
CFLAGS= -I
LIBS= -lpthread
CCFLAGS= -Wall

server: 
	$(CC) $(CFLAGS) $(CCFLAGS) server_chat.c -o server_chat.o $(LIBS)

client: 
	$(CC) $(CFLAGS) $(CCFLAGS) client_chat.c -o client_chat.o $(LIBS)

all:
	$(CC) $(CFLAGS) $(CCFLAGS) server_chat.c -o server_chat.o $(LIBS)
	$(CC) $(CFLAGS) $(CCFLAGS) client_chat.c -o client_chat.o $(LIBS)

clean:
	rm -f *.o			