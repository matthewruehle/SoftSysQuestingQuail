/* Rudimentary HTTP server implementation for a course project.
 * Olin College, Software Systems (Spring 2017)
 * Sends files to client (see associated github).
 *
 * Freg Butterick, Bonnie Ishiguro, Matt Ruehle, and Joe Sutker
 */

#include "unp.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int process_file_transfer(int connfd) {
    /* 
     * connfd: int socket file descriptor
     * Reads from the socket; responds to a request predicated by GET with
     * the requested file and size data, if it exists. Else, fails with 404.
     */
    char recvline[MAXLINE]; // Most CONSTANT values are defined in unp.h
    int bytes_received = 0;
    while(1) {
        bytes_received = Readline(connfd, recvline, MAXLINE);
        if (bytes_received > 0) {
            char req_type[3];
            memcpy(req_type,&recvline[0],3);

            if(strcmp("GET",req_type)==0) {
                char FILE_TO_SEND[strlen(recvline)-4];
                memcpy(FILE_TO_SEND,&recvline[4],strlen(recvline)-5);
                FILE_TO_SEND[strlen(recvline)-5] = '\0';


                int fd = open(FILE_TO_SEND, O_RDONLY); 
                // Note: insecure. Clients could request pretty much any file.
                char file_size[256];
                struct stat file_stat;
                int sent_bytes;
                char e404[] = "Error 404: File Not Found\n"
                

                if (fd == -1) {
                    fprintf(stderr, "Error opening file --> %s\n", 
                        strerror(errno));
                    Writen(connfd, e404, 
                        strlen(e404));
                    exit(EXIT_FAILURE);
                }

                // Getting file stats and sending the size to the client.
                if (fstat(fd, &file_stat) < 0) {
                    fprintf(stderr, "Error fstat --> %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                fprintf(stdout, "File Size: \n%d bytes\n", file_stat.st_size);

                socklen_t sock_len = sizeof(struct sockaddr_in); 

                sprintf(file_size, "%d\n", file_stat.st_size);

                ssize_t len = send(connfd, file_size, strlen(file_size), 0);
                if (len < 0) {
                    fprintf(stderr, "Error on sending greetings --> %s\n", 
                        strerror(errno));
                    exit(EXIT_FAILURE);
                }

                fprintf(stdout, "Server sent %d bytes for the size\n", len);

                off_t offset = 0;
                int remain_data = file_stat.st_size;

                // Loop sends data until it's sent the whole file (file_size).
                while (((sent_bytes = sendfile(connfd, fd, &offset, BUFSIZ)) > 0)
                 && (remain_data > 0)) {
                    fprintf(stdout, "1. Server sent %d bytes from file's data, \
                        offset is now : %d and remaining data = %d\n", 
                        sent_bytes, offset, remain_data);
                    remain_data -= sent_bytes;
                    fprintf(stdout, "2. Server sent %d bytes from file's data, \
                        offset is now : %d and remaining data = %d\n", 
                        sent_bytes, offset, remain_data);
                }
                // Cleaning up the file; closing the connection.
                offset = 0;
                Writen(connfd, "\n", strlen("\n"));

                close(connfd);
                return 0;
            }
        }
    }
}



int main(int argc, char **argv) {
    /*
     * No additional parameters, at present.
     * Creates and opens sockets; passes connections to child forks.
     */

    int	listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    // Socket, Listen, etc.: wrappers from unp.h
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);
    printf("Listening on port %d (AKA ntohs(%d))\n", 
        ntohs(servaddr.sin_port), servaddr.sin_port);

    while (1) { // Main loop.
    clilen = sizeof(cliaddr);
    connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
	printf("Accepted\n");

	if ( (childpid = Fork()) == 0) {
        // Enters loop when this process is the child - "splitting" the parent.
	    printf("Forked\n");
	    Close(listenfd); // Lets the parent keep listening, though!
        process_file_transfer(connfd);
	    exit(0);
	}
	Close(connfd);
    }
}

