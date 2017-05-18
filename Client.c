#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char ch;
	char str[50]={0};
	int ret = 0;
	if (argc < 3)
	{	// using command line argument
		printf("Usage: %s <serv_ip> <serv_port>\n", argv[0]);
		exit(1);
	}

	int cfd, serv_port;
	serv_port = strtoul(argv[2], NULL, 10);//string to unsigned long
	if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in saddr = {0};
	saddr.sin_family = AF_INET; // set to AF_INET
	saddr.sin_port = htons(serv_port); // Port number
	saddr.sin_addr.s_addr = inet_addr(argv[1]); // IP address eg "192.168.1.1"

 if (connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
	{
		perror("connect");
		close(cfd);
		exit(3);
	}
while(1)
{

		printf("Enter the Text \n");
		scanf("%s",str);
			if (send(cfd, str, strlen(str), 0) < 0)
		{
			perror("send");
			close(cfd);
			exit(4);
		}
			printf("Successfully Sent\n");
			char buf[20] = {0};
			if ((ret = recv(cfd, buf, sizeof(buf), 0)) < 0)
			{
				perror("recv");
				close(cfd);
				exit(5);
			}
					printf("Data received: %s\n", buf);
		}
	close(cfd);
	close(cfd);

	return 0;
}
