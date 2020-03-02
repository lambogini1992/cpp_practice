#ifndef _FILE_HANDLE_H_
#define _FILE_HANDLE_H_

#include "common_include.h"

#define FILE_HANDLE_TYPE_BIN				0
#define FILE_HANDLE_TYPE_HEX				1
#define FILE_HANDLE_NO_TYPE					2

#define FILE_HANDLE_PROC_SUCCESS			1
#define FILE_HANDLE_PROC_FAIL				-1

typedef struct _file_data_output_
{
	uint8_t *data;
	uint64_t data_len;
}FILE_DATA_OUTPUT;

uint8_t file_handle_check_type(char *file_type);
FILE_DATA_OUTPUT *file_handle_type_bin(char *path_dir_file);
#endif
