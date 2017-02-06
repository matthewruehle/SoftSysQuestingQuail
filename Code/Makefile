CC = gcc
CFLAGS = -g -Wall

WRAPPERS = wraplib.o wrapstdio.c wrapsock.o wrapunix.o \
error.o writen.c readline.c

%.o: %.c
	$(CC) $(CFLAGS) -c $<

tcpcli_quails: tcpcli_quails.o ${WRAPPERS}
	${CC} ${CFLAGS} -o $@ tcpcli_quails.o ${WRAPPERS}

tcpserv_quails: tcpserv_quails.o ${WRAPPERS}
	${CC} ${CFLAGS} -o $@ tcpserv_quails.o ${WRAPPERS}

clean:
	rm *.o *~ tcpcli_quails tcpserv_quails
