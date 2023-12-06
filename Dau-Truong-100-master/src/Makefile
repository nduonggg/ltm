CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: client server 

server: server.o protocol.o tool.o valid.o account.o question.o gameplay.o
	${CC} protocol.o tool.o valid.o account.o server.o question.o gameplay.o -o server

server.o: server.c
	${CC} ${CFLAGS} server.c

client: client.o protocol.o tool.o valid.o gameplay.o
	${CC} protocol.o tool.o valid.o client.o gameplay.o -o client

client.o: client.c 
	${CC} ${CFLAGS} client.c

question.o: question.c
	${CC} ${CFLAGS} question.c

protocol.o: protocol.c
	${CC} ${CFLAGS} protocol.c

tool.o: tool.c
	${CC} ${CFLAGS} tool.c

gameplay.o: gameplay.c
	${CC} ${CFLAGS} gameplay.c

account.o: account.c
	${CC} ${CFLAGS} account.c

valid.o: valid.c
	${CC} ${CFLAGS} valid.c
clean:
	rm -f *.o *~