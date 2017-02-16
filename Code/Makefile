CC = gcc
CFLAGS = -g -Wall

WRAPPERS = wraplib.o wrapstdio.c wrapsock.o wrapunix.o \
error.o writen.c readline.c

%.o: %.c
	$(CC) $(CFLAGS) -c $<

tcpclient: tcpclient.o ${WRAPPERS}
	${CC} ${CFLAGS} -o $@ tcpclient.o ${WRAPPERS}

tcpserv_quails: tcpserv_quails.o ${WRAPPERS}
	${CC} ${CFLAGS} -o $@ tcpserv_quails.o ${WRAPPERS}

clean:
	rm *.o *~ tcpclient tcpserv_quails

reset:
	make clean; make tcpclient tcpserv_quails

insanity:
	make clean; make tcpclient tcpserv_quails