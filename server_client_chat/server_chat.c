#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h> 
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <string.h> 
#include <pthread.h> 

#define PORT 8080 
#define MAX_NO_OF_CLIENTS				25
#define LENGHT_OF_CLIENTS_NAME  		255
#define MAX_RECV_TRANS_BUFF		  		1024

bool send_all_access_flag;

typedef struct _client_info_
{
	int socket;
	char client_name[LENGHT_OF_CLIENTS_NAME];
}CLIENT_INFO;

typedef struct _client_str_
{
	int client_no;
	CLIENT_INFO client[MAX_NO_OF_CLIENTS];
}CLIENT_STR;

CLIENT_STR client_conn;


bool LOCK_FLAG()
{
	return false;
}

bool UNLOCK_FLAG()
{
	return true;
}

// void handle_device_

void send_to_all_client(char *buff, int lenght_buff)
{
	int client_idx;
	// printf("%d\n", client_conn.client_no);
	for(client_idx = 0; client_idx < client_conn.client_no; client_idx++)
	{
		send(client_conn.client[client_idx].socket, buff, lenght_buff, 0);
	}
}

void client_handle_data_thread(void *vargp)
{
	CLIENT_INFO *client = (CLIENT_INFO *)vargp;
	char raw_buffer[MAX_RECV_TRANS_BUFF] = {0}; 
	char buffer[MAX_RECV_TRANS_BUFF] = {0}; 
	int valread = 0;

	if(recv(client->socket, client->client_name, LENGHT_OF_CLIENTS_NAME, 0) > 0)
	{
		printf("%s join to chatroom\n", client->client_name);
		sprintf(buffer, "%s join to chatroom\n", client->client_name);
		while(send_all_access_flag == false);
		send_all_access_flag = LOCK_FLAG();
		send_to_all_client(buffer, strlen(buffer));
		memset(buffer, 0, 1024);
		send_all_access_flag = UNLOCK_FLAG();
	}

	while(1)
	{
		memset(raw_buffer, 0, 1024);
		valread = 0;
		valread = recv(client->socket , raw_buffer, 1024, 0); 
		if(valread > 0)
		{
			
			if(strlen(raw_buffer) > 0)
			{
				sprintf(buffer, "%s:%s\n", client->client_name, raw_buffer);
				while(send_all_access_flag == false);
				send_all_access_flag = LOCK_FLAG();
				send_to_all_client(buffer, strlen(buffer));
				memset(buffer, 0, 1024);
				send_all_access_flag = UNLOCK_FLAG();	
			}
		}
	}
}

void trans_data_thread(void *vargp)
{
	int sock = 0;
	char buff[1024];

	sock = *(int*)(vargp);

	while(1)
	{
		memset(buff, 0, 1024);
		if(fgets(buff, 1024, stdin) != NULL)
		{
			printf("Server: %s\n\n",buff ); 
			send(sock , buff , strlen(buff) , 0 );
		}
	}
}

int main(int argc, char const *argv[])
{
	int ser_fd, new_sock;

	int ret_val;
	struct sockaddr_in address;
	struct sockaddr_in client_address;
	int opt = 1;
	int add_len = sizeof(client_address);
	int count_client;
	
	// char buffer[1024] = {0}; 
	// int valread;

	pthread_t pth_client_handle_id[MAX_NO_OF_CLIENTS];
    pthread_t pth_trans_id;

	ser_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(ser_fd == 0)
	{
		perror("Fail to creat socket\n\n");
		goto END_PROG;
	}

	ret_val = setsockopt(ser_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT \
						, &opt, sizeof(opt));
	if(ret_val)
	{
		perror("Fail to setting socket\n\n");
		goto END_PROG;
	}

	address.sin_family	= AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port	= htons(PORT);

	if(bind(ser_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("Fail to binding socket\n");
		goto END_PROG;
	}

	if(listen(ser_fd, 3) < 0)
	{
		perror("Fail to listen socket connect\n\n");
		goto END_PROG;
	}
	count_client = 0;
	client_conn.client_no = 0;
	send_all_access_flag = true;
	// pthread_create(&pth_trans_id, NULL, trans_data_thread, (void *)&new_sock);

	while(1)
	{
		if(client_conn.client_no < MAX_NO_OF_CLIENTS)
		{
			new_sock = accept(ser_fd, (struct sockaddr *)&client_address, (socklen_t *)&add_len);
			if(new_sock < 0)
			{
				perror("Fail to accept new value");
				goto END_PROG;
			}

			getpeername(new_sock, (struct sockaddr*) &client_address, (socklen_t*) &add_len);
        	printf("Client %s:%d come in.\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
			
			client_conn.client_no++;
			memset(&(client_conn.client[count_client]), 0, sizeof(CLIENT_INFO));
			client_conn.client[count_client].socket = new_sock;


			if(pthread_create(pth_client_handle_id + count_client, NULL, &client_handle_data_thread, \
				(void *)&(client_conn.client[count_client])) != 0 )
			{
				perror("Fail to Create handle client process");
				goto END_PROG;
			}
			count_client++;
		}

	}

	// pthread_join(pth_recv_id, NULL);
	// pthread_join(pth_trans_id, NULL);

END_PROG:
	return 0;
}