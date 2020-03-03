/*
 ============================================================================
 Name        : bootloader_app_pc.c
 Author      : Pham Tuan Anh
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "file_handle.h"
#include "boot_proc.h"
#include "serial_port.h"

int main(int argc, char **argv) {


	if(argc < 3)
	{
		printf("Not enough data input: USB_PORT TYPE_FILE FILE_DIR\n\n");
		return -1;
	}

	return 0;
}
