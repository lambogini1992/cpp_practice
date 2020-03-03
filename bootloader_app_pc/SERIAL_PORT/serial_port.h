#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

#include "common_include.h"

#define SERIAL_PORT_PROC_FAIL						0
#define SERIAL_PORT_PROC_SUCCESS					1

#define SERIAL_PORT_PROC_SPEED						B115200	// 115200

#define SERIAL_PORT_PROC_RECV_MAX					255

#define SERIAL_PORT_CHANGE_PERMISSION				"sudo chmod 777 "


uint8_t serial_port_init(char *port_type);
void serial_port_close(void);
uint8_t serial_port_read(char *rbuff);
uint8_t serial_port_write(char *wbuff, uint16_t buff_len);

#endif
