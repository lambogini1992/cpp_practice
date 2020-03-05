#include "serial_port.h"

static struct termios tty_ser;;
//static int file_desc;
int file_desc;

uint8_t serial_port_init(char *port_type)
{
	char sys_com[50] = {0x00};

	sprintf(sys_com, "%s%s", SERIAL_PORT_CHANGE_PERMISSION, port_type);
	system(sys_com);

	file_desc = open(port_type, O_RDWR | O_NOCTTY | O_NDELAY);
	if(file_desc == -1)
	{
		printf("Fail to open port type\n\n");
		return SERIAL_PORT_PROC_FAIL;
	}

	cfsetospeed(&tty_ser, SERIAL_PORT_PROC_SPEED);
	cfsetispeed(&tty_ser, SERIAL_PORT_PROC_SPEED);

	tty_ser.c_cflag &= ~PARENB;
	tty_ser.c_cflag &= ~CSTOPB;
	tty_ser.c_cflag &= ~CSIZE;
	tty_ser.c_cflag |= CS8;

	tty_ser.c_cflag &= ~CRTSCTS;
	tty_ser.c_cflag |= CREAD | CLOCAL;

	tty_ser.c_iflag &= ~(IXON | IXOFF | IXANY);
	tty_ser.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	tty_ser.c_oflag &= ~OPOST;

	tty_ser.c_cc[VMIN] = 10;
	tty_ser.c_cc[VTIME] = 0;

	if(tcsetattr(file_desc, TCSANOW, &tty_ser) != 0)
	{
		printf("SERIAL PROCESS:Fail to setting attribute of serial port!\n\n");
		return SERIAL_PORT_PROC_FAIL;
	}
	else
	{
		printf("SERIAL PROCESS:Success to setting attribute of serial port with:\n");
		printf("	BAUD RATE:115200		Stop Bit: 1		Parity: None\n\n");
	}

	return SERIAL_PORT_PROC_SUCCESS;
}

void serial_port_close(void)
{
	close(file_desc);
}

uint8_t serial_port_read(char *rbuff)
{
	uint8_t len_rdata = 0;

//	memset(rbuff, 0, SERIAL_PORT_PROC_RECV_MAX);
	fcntl(file_desc, F_SETFL, 0);
	tcflush(file_desc, TCIFLUSH);

	while(len_rdata == 0)
	{
		len_rdata = (uint8_t)read(file_desc, rbuff, 4);
	}

	return len_rdata;
}

uint8_t serial_port_write(char *wbuff, uint16_t buff_len)
{
	write(file_desc, wbuff, buff_len);
	return SERIAL_PORT_PROC_SUCCESS;
}
