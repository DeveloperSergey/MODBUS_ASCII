#include <iostream>
#include "modbus_ascii.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	uint8_t usb_buff_rx[] = "0000:3C00C4\r\n0000";
	uint8_t usb_buff_tx[255] = {0};
	
	uint8_t data[] = {60, 1}; // a data for transmit
	uint8_t modbus_msg[255] = {0}; // cut the modbus msg from usb_buffer_rx


	printf("rx: %s\n", usb_buff_rx);
	uint8_t res = readMsg(usb_buff_rx, sizeof(usb_buff_rx), modbus_msg);
	printf("read: %s\n", modbus_msg);
	
	printf("%d %d\n", data[0], data[1]);
	res = writeMsg(data, sizeof(data), usb_buff_tx);
	printf("write: %s\n", usb_buff_tx);

	return 0;
}
