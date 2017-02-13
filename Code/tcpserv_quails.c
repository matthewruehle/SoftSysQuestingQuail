#include "unp.h"
#include <sys/stat.h> // O_RDONLY
#include <fcntl.h>    // O_RDONLY
#include <unistd.h>   // fstats
#include <sys/types.h>
#include <stdlib.h>   // EXIT_FAILURE

#define FILE_TO_SEND "server_side.txt"

int process_file_transfer(int connfd) {
    int fd = open(FILE_TO_SEND, O_RDONLY);
    char file_size[256];
    struct stat file_stat;
    int sent_bytes;

    if (fd == -1) {
        fprintf(stderr, "Error opening file --> %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // get file stats
    if (fstat(fd, &file_stat) < 0) {
        fprintf(stderr, "Error fstat --> %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "File Size: \n%d bytes\n", file_stat.st_size);

    socklen_t sock_len = sizeof(struct sockaddr_in); 

    sprintf(file_size, "%d", file_stat.st_size);
    ssize_t len = send(connfd, file_size, sizeof(file_size), 0);
    if (len < 0) {
        fprintf(stderr, "Error on sending greetings --> %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Server sent %d bytes for the size\n", len);

    off_t offset = 0;
    int remain_data = file_stat.st_size;

    // sending file data
    sendfile(connfd, "", &offset, BUFSIZ); // Tries to fix Readline? Does nothing
    while (((sent_bytes = sendfile(connfd, fd, &offset, BUFSIZ)) > 0) && (remain_data > 0)) {
        fprintf(stdout, "1. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
        remain_data -= sent_bytes;
        fprintf(stdout, "2. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
    }
  rewind(fd);
  close(connfd);
  return 0;

}



int main(int argc, char **argv) { //why **?: array of strings
    int	listenfd, connfd;
    pid_t childpid;
    socklen_t clilen; //this structure declaration doesn't have 'struct' but the next one does, why? its an int and it gets declared in the header
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0); //why the wrappers? they put in error checking so the code is neater
    
    bzero(&servaddr, sizeof(servaddr)); // why this instead of memset? no reason, interchangeable
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);
    printf("Listening on port %d (AKA ntohs(%d))\n", ntohs(servaddr.sin_port), servaddr.sin_port);

    for ( ; ; ) { //why instead of "while true {" : no reason, interchangeable
    clilen = sizeof(cliaddr); //why is this set to a variable then dereferenced in the function 
//call and that same thing is not done in the Bind() call?  it might have something to do with needing size declared ahead of time.

    connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
	printf("Accepted\n");

	if ( (childpid = Fork()) == 0) { //this never fires for the server
        //this is because the server "childpid" never returns 0, instead some pos number
        // meanwhile the child will pass this and close the listening file descriptor
        // and the server closes the connection to the client so it can move on to others
	    printf("Forked\n");
	    Close(listenfd);
	    
        process_file_transfer(connfd);

        //str_echo(connfd); //why use this function, why overwrite it instead of standard? its used to do all the parts of the server work
        //so this makes sense for readability plus the builting functionality of str_echo. additionally str_echo contains the protocol for
        // information transfer 
	    exit(0);
	}
	Close(connfd);
    }
}

