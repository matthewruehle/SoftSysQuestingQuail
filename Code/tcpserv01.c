#include	"unp.h"


int main(int argc, char **argv) //why **?: array of strings
{
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
    printf("Listening on port %d\n", servaddr.sin_port);

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
	    str_echo(connfd); //why use this function, why overwrite it instead of standard? its used to do all the parts of the server work
        //so this makes sense for readability plus the builting functionality of str_echo. additionally str_echo contains the protocol for
        // information transfer 
        //in str_echo08?
	    exit(0);
	}
    printf("UnForked\n");
	Close(connfd);
    }
}

