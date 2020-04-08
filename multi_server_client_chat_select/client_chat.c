#include <stdio.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>


#define PORT 8080 

char *client_name;

void *recv_data_thread(void *vargp)
{
	int sock = 0;
	char buffer[1024] = {0}; 
	int valread;

	sock = *(int*)(vargp);

	while(1)
	{
		bzero(buffer, 1024);
		valread = 0;
		valread = recv( sock , buffer, 1024, 0); 
		if(valread > 0)
		{
			printf("%s\n\n",buffer ); 
		}
	}
}

void *trans_data_thread(void *vargp)
{
	int sock = 0;
	char buff[1000];
	char trans_buff[1024];

	sock = *(int*)(vargp);

	while(1)
	{
		memset(buff, 0, 1000);
		memset(trans_buff, 0, 1024);
		if(fgets(buff, 1000, stdin) != NULL)
		{
			sprintf(trans_buff, "%s: %s\n\n", client_name, buff ); 
			send(sock , buff , strlen(buff) , 0 );
		}
	}
}

int main(int argc, char const *argv[])
{
	struct sockaddr_in address; 
	int ret_val;
    int sock = 0; 
    struct sockaddr_in serv_addr; 
    pthread_t pth_recv_id;
    pthread_t pth_trans_id;

	if(argc < 3)
	{
		perror("Please input ipv4 address of server and client name\n\n");
		goto END_PROG;	
	}

	// client_name = malloc(strlen(argv[2]));
	// memcpy(client_name, argv[2], strlen(argv[2]));

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
    	perror("Fail to creat socket\n\n");
		goto END_PROG;
    }

    ret_val = inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
    if (ret_val <= 0)
    {
    	perror("Fail to get sin_addr element with ipv4\n\n");
		goto END_PROG;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port	= htons(PORT);
    
    ret_val = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(ret_val < 0)
	{
		perror("Fail to connect socket\n\n");
		goto END_PROG;
	}

	printf("You connect to chatroom with ip %s\n", argv[1]);

	send(sock, argv[2], strlen(argv[2]), 0);

	pthread_create(&pth_trans_id, NULL, trans_data_thread, (void *)&sock);
	pthread_create(&pth_recv_id, NULL, recv_data_thread, (void *)&sock);

	while(1);
END_PROG:
	return 0;
}