/* Rudimentary HTTP client implementation for a course project.
 * Olin College, Software Systems (Spring 2017)
 * Requests files from server (see associated github).
 *
 * Gabe Butterick, Bonnie Ishiguro, Mat Ruehle, and Joe Sutker
 */

#include	"unp.h"

void process_response(char *filename, int sockfd)
{
	/* 
     * filename: file to request
     * sockfd: socket file descriptor
     * Writes a GET message to the server; reads the filesize response and
     * then writes to file to file.txt
     */

	char	sendline[MAXLINE], recvline[MAXLINE];
	FILE *file_p;

	char file_size[256];
	char test[256];
	sprintf(test, "GET %s\n", filename);
	int bytes_received = 0;
	int current_bytes = 0;
	
	Writen(sockfd, test, strlen(test));

	bytes_received = Readline(sockfd, file_size, MAXLINE); // Sets file size
	fprintf(stdout, "bytes_received: %i\n", bytes_received);
	fprintf(stdout, "file_size: %s\n", file_size);

	int f_size = atoi(file_size);
	fprintf(stdout, "f_size: %i\n", f_size);

	file_p = Fopen("file.txt", "w");

	fprintf(stdout, "bytes_received: %i\n", bytes_received);
	fprintf(stdout, "f_size: %i\n", f_size);

	bytes_received = 0;


	while (1) {
		// Loops until the whole file (based on f_size) has been received.
		if (bytes_received < f_size) {
			current_bytes = Readline(sockfd, recvline, MAXLINE);

			if((current_bytes != 0) && (recvline != "")) {
				fprintf(stdout, "curr_bytes: %i\n", current_bytes);
				fprintf(stdout, "line: %s\n", recvline);
			}

			fprintf(file_p, "%s", recvline);

			bytes_received = bytes_received + current_bytes;
		}
		else {
			fprintf(stdout,"%s\n","read finished");
			break;
		}
	}
	current_bytes = 0;
	Fclose(file_p);
}


int main(int argc, char **argv)
{
	/*
	 * Sends a GET request for <filename> to <IPaddress> of server.
	 * Port is a constant from the header unp.h
	 * Writes to file.txt, and exits.
	 */
	int	sockfd;
	struct sockaddr_in servaddr;

	if (argc != 3)
		err_quit("usage: tcpcli <IPaddress> <filename>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	process_response(argv[2], sockfd);

	exit(0);
	}
