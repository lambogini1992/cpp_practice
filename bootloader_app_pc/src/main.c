/*
 ============================================================================
 Name        : bootloader_app_pc.c
 Author      : Pham Tuan Anh
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "common_include.h"
#include "file_handle.h"
#include "boot_proc.h"
#include "serial_port.h"

extern int file_desc;
int main(int argc, char **argv)
{


#ifndef DEBUG
	FILE_DATA_OUTPUT *file_data;
	if(argc < 3)
	{
		printf("Not enough data input: USB_PORT TYPE_FILE FILE_DIR\n\n");
		return -1;
	}
	serial_port_init(argv[1]);
	if(file_handle_check_type(argv[2]) == -1)
	{
		printf("This type file is not support\n\n");
	}

	file_data = file_handle_type_bin(argv[3]);
	if(file_data == NULL)
	{
		printf("Application cannot handle this file\n\n");
	}

	if(boot_process_data_handle(file_data->data, file_data->data_len) == BOOT_PROC_FAIL)
	{
		printf("Boot process is fail\n\n");
	}

	free(file_data->data);
	free(file_data);
	serial_port_close();
#else
//	uint16_t idx;
//	uint8_t len_rdata;
//	if(argc < 1)
//	{
//		printf("Not enough data input: FILE_DIR\n\n");
//		return -1;
//	}
//
//	file_data = file_handle_type_bin(argv[1]);
//	if(file_data == NULL)
//	{
//		printf("Application cannot handle this file\n\n");
//	}
//	else
//	{
//		if(boot_process_data_handle(file_data->data, file_data->data_len) == BOOT_PROC_FAIL)
//		{
//			printf("Boot process is fail\n\n");
//		}
//	}
//
//	free(file_data->data);
//	free(file_data);
//	char *s;

	if(argc < 2)
	{
		printf("Not enough data input: USB_PORT DATA_WRITE\n\n");
		return -1;
	}

	if(serial_port_init(argv[1]) == SERIAL_PORT_PROC_FAIL)
	{
		return -1;
	}

//	s = malloc(50);


	serial_port_write(argv[2], strlen(argv[2]));

	tcflush(file_desc, TCIFLUSH);   /* Discards old data in the rx buffer            */

	char read_buffer[32];   /* Buffer to store the data received              */
	int  bytes_read = 0;    /* Number of bytes read by the read() system call */
	int i = 0;

	memset(read_buffer, 0, 32);

	while(bytes_read > 0)
	{
		bytes_read = read(file_desc,&read_buffer,4);
	}

	printf("\n\n  Bytes Rxed - %d", bytes_read); /* Print the number of bytes read */
	printf("\n\n  ");

	for(i=0;i<bytes_read;i++)	 /*printing only the received characters*/
	    printf("%c",read_buffer[i]);

	printf("\n +----------------------------------+\n\n\n");

	serial_port_close();


#endif
	return 0;
}


