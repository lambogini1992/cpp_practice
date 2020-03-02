#include <sys/stat.h>
#include "./file_handle.h"

static const char *file_type_str[]=
{
		"bin",
		"hex",
		0
};

static int8_t file_handle_convet_str_hex(char *data_str, uint64_t *data_len);
static FILE_DATA_OUTPUT *file_handle_remove_unnecessary_char(char *file_name);

int8_t file_handle_check_type(char *file_type)
{
	int8_t idx;

	for(idx = 0; idx < FILE_HANDLE_NO_TYPE; idx++)
	{
		if(strcmp(file_type, file_type_str[idx]) == 0)
		{
			return idx;
		}
	}

	return -1;
}

FILE_DATA_OUTPUT *file_handle_type_bin(char *path_dir_file)
{
	FILE_DATA_OUTPUT *file_handle;

	file_handle = file_handle_remove_unnecessary_char(path_dir_file);

	return file_handle;
}

static FILE_DATA_OUTPUT *file_handle_remove_unnecessary_char(char *file_name)
{
	FILE_DATA_OUTPUT *file_handle;
	struct stat st_file;
	uint64_t fsiz = 0;
	uint64_t tmp_fsiz = 0;
	FILE *fhandle;
	char *rdata;
	char *wdata;
	uint8_t idx;

	if(0 == stat((const char *)file_name, &st_file))
	{
		tmp_fsiz = (uint64_t)st_file.st_size;
		if(tmp_fsiz == 0)
		{
			return NULL;
		}
	}

	rdata = malloc(tmp_fsiz);
	memset(rdata, 0, tmp_fsiz);

	fhandle = fopen(file_name, "r+");
	if(fhandle == NULL)
	{
		printf("file is not handled\n\n");
		return NULL;
	}

	while(fgets(rdata, tmp_fsiz, fhandle) != NULL);

	fclose(fhandle);

	wdata = malloc(tmp_fsiz);
	memset(wdata, 0, tmp_fsiz);

	for(idx = 0; idx < tmp_fsiz; idx++)
	{
		if(rdata[idx] != ' ')
		{
			if(rdata[idx] != '\n')
			{
				wdata[idx] = rdata[idx];
				fsiz++;
			}
		}
	}

	free(rdata);

#ifdef DEBUG
	printf("DATA file after remove \"\n\" and \" \" character:\n");
	for(idx = 0; idx < fsiz; idx++)
	{
		printf("%.2x", wdata[idx]);
	}
	printf("\n\n");
#endif

	if(file_handle_convet_str_hex(wdata, &fsiz) == FILE_HANDLE_PROC_FAIL)
	{
		printf("\nFile data is invalid\n");
		return NULL;
	}

	fhandle = fopen(file_name, "w+");
	if(fhandle == NULL)
	{
		printf("file is not handled\n\n");
		return NULL;
	}

	for(idx = 0; idx < fsiz; idx++)
	{
		fputc(wdata[idx], fhandle);
	}

	fclose(fhandle);

	file_handle = malloc(sizeof(FILE_DATA_OUTPUT));

	file_handle->data_len = fsiz;
	file_handle->data 	  = (uint8_t *)malloc(fsiz);
	for(idx = 0; idx < fsiz; idx++)
	{
		file_handle->data[idx] = wdata[idx];
	}


	free(wdata);
	return file_handle;
}

static int8_t file_handle_convet_str_hex(char *data_str, uint64_t *data_len)
{
	uint8_t *data_hex;
	uint64_t idx;
	if((*data_len % 2) != 0)
	{
		printf("Length data file is invalid\n\n");
		return FILE_HANDLE_PROC_FAIL;
	}

	int i;
	char buff[200];

	for(i = 0; i < *data_len; i++)
	{
		switch(data_str[i])
		{
			case '0':
				data_str[i] = 0x00;
				break;
			case '1':
				data_str[i] = 0x01;
				break;
			case '2':
				data_str[i] = 0x02;
				break;
			case '3':
				data_str[i] = 0x03;
				break;
			case '4':
				data_str[i] = 0x04;
				break;
			case '5':
				data_str[i] = 0x05;
				break;
			case '6':
				data_str[i] = 0x06;
				break;
			case '7':
				data_str[i] = 0x07;
				break;
			case '8':
				data_str[i] = 0x08;
				break;
			case '9':
				data_str[i] = 0x09;
				break;
			case 'a':
				data_str[i] = 0x0A;
				break;
			case 'A':
				data_str[i] = 0x0A;
				break;
			case 'b':
				data_str[i] = 0x0B;
				break;
			case 'B':
				data_str[i] = 0x0B;
				break;
			case 'c':
				data_str[i] = 0x0C;
				break;
			case 'C':
				data_str[i] = 0x0C;
				break;
			case 'd':
				buff[i] = 0x0D;
				break;
			case 'D':
				data_str[i] = 0x0D;
				break;
			case 'e':
				data_str[i] = 0x0E;
				break;
			case 'E':
				data_str[i] = 0x0E;
				break;
			case 'f':
				data_str[i] = 0x0F;
				break;
			case 'F':
				data_str[i] = 0x0F;
				break;
			default:
				printf("Character of data file is invalid\n\n");
				return FILE_HANDLE_PROC_FAIL;
		}
	}

	*data_len = (*data_len)/2;

	data_hex = (uint8_t *)malloc((*data_len));

	for(i = 0; i < (*data_len); i++)
	{
		data_hex[i] = (uint8_t)((data_str[i*2] << 4) & 0xF0) | (uint8_t)(data_str[i*2 + 1] & 0x0F);
	}

	free(data_str);
	data_str = (uint8_t *)malloc((*data_len));

	memset(data_str, 0xFF, *data_len);

	memcpy(data_str, data_hex, *data_len);

	free(data_hex);

#ifdef DEBUG
	printf("\nData String after convert:\n");
	for(i = 0; i < (*data_len); i++)
	{
		printf("%.2x ", data_str[i]);
	}
	printf("\n\n");
#endif

	return FILE_HANDLE_PROC_SUCCESS;
}
