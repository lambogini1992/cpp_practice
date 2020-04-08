#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
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
	bool flag_name;
}CLIENT_INFO;

typedef struct _client_str_
{
	int client_no;
	CLIENT_INFO client[MAX_NO_OF_CLIENTS];
}CLIENT_STR;

CLIENT_STR client_conn;


// bool LOCK_FLAG()
// {
// 	return false;
// }

// bool UNLOCK_FLAG()
// {
// 	return true;
// }



void send_to_all_client(char *buff, int lenght_buff)
{
	int client_idx;
	if(client_conn.client_no > 1)
	{
		for(client_idx = 0; client_idx < client_conn.client_no; client_idx++)
		{
			send(client_conn.client[client_idx].socket, buff, lenght_buff, 0);
		}
	}

}

void client_handle_data_thread(CLIENT_INFO *client)
{
	// CLIENT_INFO *client = (CLIENT_INFO *)vargp;
	char raw_buffer[MAX_RECV_TRANS_BUFF] = {0}; 
	char buffer[MAX_RECV_TRANS_BUFF] = {0}; 
	int valread = 0;

	memset(buffer, 0, 1024);
	memset(raw_buffer, 0, 1024);
	valread = 0;
	valread = recv(client->socket , raw_buffer, 1024, 0); 

	if(valread > 0)
	{
		if(strlen(raw_buffer) > 0)
		{
			if(client->flag_name == false)
			{
				client->flag_name = true;
				printf("Set name for new device\n");
				memcpy(client->client_name, raw_buffer, valread);
				printf("%s join to chatroom\n", client->client_name);
				sprintf(buffer, "%s join to chatroom\n", client->client_name);
				send_to_all_client(buffer, strlen(buffer));
			}
			else
			{
				printf("%s\n", raw_buffer);
				sprintf(buffer, "%s:%s\n", client->client_name, raw_buffer);
				printf("%s", buffer);
				send_to_all_client(buffer, strlen(buffer));
			}
		}
	}
}

void add_new_client(int ser_socket)
{
	int client_sock;
	char client_name[LENGHT_OF_CLIENTS_NAME];
	struct sockaddr_in client_address;
	int add_len = sizeof(client_address);

	printf("New Client join\n\n");

	client_sock = accept(ser_socket, (struct sockaddr *)&client_address, (socklen_t *)&add_len);
	if(client_sock < 0)
	{
		perror("Fail to accept new value");
		return;
	}

	getpeername(client_sock, (struct sockaddr*) &client_address, (socklen_t*) &add_len);
	printf("Client %s:%d come in.\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
	
	memset(&(client_conn.client[client_conn.client_no]), 0, sizeof(CLIENT_INFO));
	client_conn.client[client_conn.client_no].socket = client_sock;
	client_conn.client[client_conn.client_no].flag_name = false;
	client_conn.client_no++;
}

void handle_socket_trigger(int ser_socket, fd_set *ser_sock_fd_sel)
{
	int idx;

	if(FD_ISSET(ser_socket, ser_sock_fd_sel))
	{
		add_new_client(ser_socket);
	}

	if(client_conn.client_no > 0)
	{
		// printf("Check Client Socket Send\n\n");
		for(idx = 0; idx < client_conn.client_no; idx++)
		{
			if(FD_ISSET(client_conn.client[idx].socket, ser_sock_fd_sel))
			{
				// printf("Check Client Socket Send\n\n");
				client_handle_data_thread(&client_conn.client[idx]);
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int ser_fd, high_serfd, new_sock;

    fd_set ser_sock_fd_sel;
    struct timeval tv;
    int retval;

	int ret_val;
	struct sockaddr_in address;
	
	int opt = 1;
	int idx;
	
	// char buffer[1024] = {0}; 
	// int valread;

	pthread_t pth_client_handle_id;
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

	if(listen(ser_fd, 10) < 0)
	{
		perror("Fail to listen socket connect\n\n");
		goto END_PROG;
	}

	memset(&client_conn, 0, sizeof(CLIENT_STR));
	client_conn.client_no = 0;
	send_all_access_flag = true;
	// pthread_create(&pth_trans_id, NULL, trans_data_thread, (void *)&new_sock);
	// if(pthread_create(pth_client_handle_id, NULL, &client_handle_data_thread, NULL) != 0)
	// {
	// 	perror("Fail to Create handle client process");
	// 	goto END_PROG;
	// }

	while(1)
	{
		ret_val = 0;
		if(client_conn.client_no < MAX_NO_OF_CLIENTS)
		{
			high_serfd = ser_fd;
			FD_ZERO(&ser_sock_fd_sel);
			FD_SET(ser_fd,&ser_sock_fd_sel);

			if(client_conn.client_no > 0)
			{
				for(idx = 0; idx < client_conn.client_no; idx++)
				{
					FD_SET(client_conn.client[idx].socket,&ser_sock_fd_sel);
					if(client_conn.client[idx].socket > high_serfd)
					{
						high_serfd = client_conn.client[idx].socket;
					}
				}
			}
			
			tv.tv_sec = 0;
			tv.tv_usec = 500;
			// printf("DEBUG\n\n");
			ret_val = select(high_serfd + 1, &ser_sock_fd_sel, (fd_set *) 0, (fd_set *) 0, &tv);
			if(ret_val < 0)
			{
				perror("select");
				goto END_PROG;
			}
			else if(ret_val == 0)
			{
				// printf(".");
			}
			else if(ret_val > 0)
			{
				handle_socket_trigger(ser_fd, &ser_sock_fd_sel);
			}

		}

	}

END_PROG:
	return 0;
}