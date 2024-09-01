#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void error_handling(char *message);

int main(int argc, char* argv[])
{
		int sock;
		int n, in, out;
		struct sockaddr_in serv_addr;
		char message[30];
		int str_len;
		char buf[100];
		
		if(argc!=4){
			printf("Usage : %s <IP> <port> <file>\n", argv[0]);
			exit(1);
		}
		
		if ((in = open(argv[3], O_RDONLY)) < 0){
			perror(argv[1]);
			return 1;
		}
		
		sock=socket(PF_INET, SOCK_STREAM, 0);
		if(sock == -1)
			error_handling("socket() error");

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family=AF_INET;
		serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
		serv_addr.sin_port=htons(atoi(argv[2]));
		
		if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) ==-1)
			error_handling("connect() error!");

		while(1)
		{
			n = read(in, buf, sizeof(buf));
			if(n > 0)
				write(sock, buf , n);
			else if(n == 0){
				write(sock,buf,n);
				close(sock);
				break;
			}
			else
				perror("open");

		}
/*		do
		{
			str_len = read(in, message, sizeof(message));
			if(str_len > 0)
				write(sock, message, str_len);
			else if(str_len == 0)
				break;
			else
			{
				perror("read");
				break;
			}
		}while(1);

		fputs("Done ...",str_len);
*/
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
