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
#include "../FILE_HANDLE/file_handle.h"
#include "../BOOT_PROC/boot_proc.h"
#include "../SERIAL_PORT/serial_port.h"

int main(int argc, char **argv)
{

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
		return -1;
	}

	file_data = file_handle_type_bin(argv[3]);
	if(file_data == NULL)
	{
		printf("Application cannot handle this file\n\n");
		return -1;
	}

	if(boot_process_data_handle(file_data->data, file_data->data_len) == BOOT_PROC_FAIL)
	{
		printf("Boot process is fail\n\n");
		return -1;
	}

	free(file_data->data);
	free(file_data);

	return 0;
}
