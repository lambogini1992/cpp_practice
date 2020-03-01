#include <sys/stat.h>
#include "./file_handle.h"

static const char *file_type_str[]=
{
		"bin",
		"hex",
		0
};

static uint8_t *file_handle_convet_str_hex(char *data_str);
static uint64_t file_handle_remove_unnecessary_char(char *file_name);

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
	char *data;

	file_handle = malloc(sizeof(FILE_DATA_OUTPUT));

	file_handle->data_len = file_handle_remove_unnecessary_char(path_dir_file);

	data = malloc(file_handle->data_len);



	return file_handle;
}

static uint64_t file_handle_remove_unnecessary_char(char *file_name)
{
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
			return 0;
		}
	}

	rdata = malloc(tmp_fsiz);
	memset(rdata, 0, tmp_fsiz);

	fhandle = fopen(file_name, "r+");
	if(fhandle == NULL)
	{
		printf("file is not handled\n\n");
		return 0;
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

	printf("DATA file after remove \"\n\" and \" \" character:\n");
	for(idx = 0; idx < fsiz; idx++)
	{
		printf("%c", wdata[idx]);
	}
	printf("\n\n");

	fhandle = fopen(file_name, "w+");
	if(fhandle == NULL)
	{
		printf("file is not handled\n\n");
		return 0;
	}

	fputs(wdata, fhandle);
	fputc('\n', fhandle);

	fclose(fhandle);

	return fsiz;
}
