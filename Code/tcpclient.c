#include	"unp.h"

void str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];
	FILE *file_p;

	char file_size[256];
	char test[] = "GET server_side.txt\n";
	// char test[] = "GET server_text_three.txt\n"; //Bad request to test 404
	int bytes_received = 0;
	int current_bytes = 0;
	
	Writen(sockfd, test, strlen(test));

	bytes_received = Readline(sockfd, file_size, MAXLINE); // read file size
	fprintf(stdout, "bytes_received: %i\n", bytes_received);
	fprintf(stdout, "file_size: %s\n", file_size);

	int f_size = atoi(file_size);
	fprintf(stdout, "f_size: %i\n", f_size);

	file_p = Fopen("file.txt", "w");

	fprintf(stdout, "this is bytes_received: %i\n", bytes_received);
	fprintf(stdout, "this is f_size: %i\n", f_size);

	bytes_received = 0;

	

	while (1) {
		

		if (bytes_received < f_size) {
		// while (Fgets(sendline, MAXLINE, fp) != NULL) {
		// while (current_bytes = Readline(sockfd, recvline, MAXLINE) != 0) {
			
			// Writen(sockfd, sendline, strlen(sendline));
				
			current_bytes = Readline(sockfd, recvline, MAXLINE);

			if((current_bytes != 0) && (recvline != "")) {
				fprintf(stdout, "curr_bytes: %i\n", current_bytes);
				fprintf(stdout, "line: %s\n", recvline);
			} //else {
			// 	fprintf(stdout, "%s\n", "DONE");
			// 	// break;
			// }

			fprintf(file_p, "%s", recvline);

			bytes_received = bytes_received + current_bytes;
		}
		else {
			fprintf(stdout,"%s\n","read finished");
			// Writen(sockfd, test, strlen(test));
			// fprintf(stdout,"%s\n","write finished");
			break;
		}
	}
	current_bytes = 0;
	Fclose(file_p);
	fprintf(stdout, "%s\n", "We're done here.");
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