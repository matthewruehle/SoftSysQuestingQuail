#include	"unp.h"

void str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];
	
	FILE *file_p;

	char file_size[8];
	Readline(sockfd, file_size, MAXLINE); // read file size
	int f_size = atoi(file_size);

	int bytes_received = 0;
	int current_bytes = 0;

	//fprintf(stdout, "%i\n", f_size);

	while (bytes_received < f_size) { // (Fgets(sendline, MAXLINE, fp) != NULL) {

		file_p = Fopen("file.txt", "a");

		//Writen(sockfd, sendline, strlen(sendline));
		
		current_bytes = Readline(sockfd, recvline, MAXLINE);
		printf(stdout, current_bytes);

		// if (Readline(sockfd, recvline, MAXLINE) == 0)
		// 	err_quit("str_cli: server terminated prematurely");

		bytes_received = bytes_received + current_bytes;

		//fprintf(stdout, recvline);
		fprintf(file_p, "%s", recvline);
		Fclose(file_p);

	}
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