#include "./boot_proc.h"

static BOOT_PROC_DATA boot_data;
static void boot_process_check_sum_data(BOOT_PROC_DATA *boot_data);
static uint8_t *boot_process_separate_data_file(uint8_t *data, uint16_t data_len, uint16_t start_idx);


int8_t boot_process_data_handle(uint8_t *data, uint16_t data_len)
{

	return BOOT_PROC_SUCCESS;
}

static void boot_process_check_sum_data(BOOT_PROC_DATA *boot_data)
{
	uint8_t *data;
	uint16_t idx;
	uint16_t check_sum;

	data = (uint8_t *)malloc(boot_data->msg_lenght - BOOT_PROC_MAX_CHECKSUM_LEN);

	data[0] = (uint8_t)(boot_data->add_flash >> 24);
	data[1] = (uint8_t)(boot_data->add_flash >> 16);
	data[2] = (uint8_t)(boot_data->add_flash >> 8);
	data[3] = (uint8_t)(boot_data->add_flash);

	for(idx = 4; idx < (boot_data->msg_lenght - BOOT_PROC_MAX_CHECKSUM_LEN); idx++)
	{
		data[idx] = boot_data->data_flash[idx - 4];
	}

	check_sum = 0;
	for(idx = 0; idx < (boot_data->msg_lenght - BOOT_PROC_MAX_CHECKSUM_LEN); idx++)
	{
		check_sum +=(uint16_t)data[idx];
	}

	boot_data->check_sum = 0x01 + (~check_sum);
}

static uint8_t *boot_process_separate_data_file(uint8_t *data, uint16_t data_len, uint16_t *start_idx)
{
	uint8_t *data;


	return data;
}
