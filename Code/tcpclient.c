#include	"unp.h"

void str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];
	// recvline[MAXLINE] = '\0';
	FILE *file_p;

	char file_size[256];
	int bytes_received = 0;
	int current_bytes = 0;
	// file_size[255] = '\0';
	// Writen(sockfd, "hello\0", strlen("hello\0"));
	
	bytes_received = Readline(sockfd, file_size, MAXLINE); // read file size
	fprintf(stdout, "bytes_received: %i\n", bytes_received);
	fprintf(stdout, "file_size: %s\n", file_size);

	int f_size = atoi(file_size);

	

	// fprintf(stdout, "%i\n", f_size);
	// fprintf(stdout, file_size);
	file_p = Fopen("file.txt", "a");

	bytes_received = Readline(sockfd, recvline, MAXLINE);
	fprintf(stdout, "bytes_received: %i\n", bytes_received);
	fprintf(stdout, "recvline: %s\n",recvline); //this shouldnt be populating the first time
	// Readline(sockfd, recvline, MAXLINE);
	// fprintf(stdout, recvline);
	exit(1);
	fprintf(stdout, "this is bytes_received: %i\n", bytes_received);
	fprintf(stdout, "this is f_size: %i\n", f_size);
	while (bytes_received < f_size) { // (Fgets(sendline, MAXLINE, fp) != NULL) {

		

		//Writen(sockfd, sendline, strlen(sendline));
		
		current_bytes = Readline(sockfd, recvline, MAXLINE);
		// printf(stdout, current_bytes);
		// fprintf(stdout, "%i\n",Readline(sockfd, recvline, MAXLINE));
		if(current_bytes != 0) {
			fprintf(stdout, "%i\n", current_bytes);
			fprintf(stdout, "%s\n", recvline);
		}
		// if (Readline(sockfd, recvline, MAXLINE) == 0)
		// 	err_quit("str_cli: server terminated prematurely");

		bytes_received = bytes_received + current_bytes;

		//fprintf(stdout, recvline);
		fprintf(file_p, "%s", recvline);
		fprintf(stdout, "%s", recvline);
		

	}
	Fclose(file_p);
}


int main(int argc, char **argv)
{
    int	sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
	err_quit("usage: tcpcli <IPaddress>");

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);		/* do it all */

    exit(0);
}