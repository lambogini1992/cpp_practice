#ifndef _BOOT_PROC_H_
#define _BOOT_PROC_H_

#include "common_include.h"
#include "serial_port.h"

#define BOOT_PROC_START_ADD_DATA			0
#define BOOT_PROC_MAX_ADD_DATA				0x7FFF

#define BOOT_PROC_SUCCESS					1
#define BOOT_PROC_FAIL						-1

#define BOOT_PROC_MAX_DATA_LEN_FILE			0xFF
#define BOOT_PROC_MAX_MSG_LEN_TRANSFER		0x106
#define BOOT_PROC_MAX_CHECKSUM_LEN			0x02

#define BOOT_PROC_ADD_POS					0x00
#define BOOT_PROC_DATA_POS					0x04

#define BOOT_PROC_DATA_TRANS_SUCCESS		"OK"
#define BOOT_PROC_DATA_TRANS_FAIL			"FAIL"
#define BOOT_PROC_FLASH_MEM_ERROR			"ERROR"

#define BOOT_PROC_DATA_TRANS_FAIL_MAX_COUNT	5

int8_t boot_process_data_handle(uint8_t *data, uint64_t data_len);


#endif
