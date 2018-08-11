#include <iostream>
#include "modbus_ascii.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	// data
	uint8_t usb_buff_rx[] = "0000:3C00C4\r\n0000";
	uint8_t usb_buff_tx[255] = {0};
	
	uint8_t data[] = {60, 1}; // a data for transmit
	uint8_t modbus_msg[255] = {0}; // cut the modbus msg from usb_buffer_rx

	// reading
	printf("rx: %s\n", usb_buff_rx);
	uint8_t res = readMsg(usb_buff_rx, sizeof(usb_buff_rx), modbus_msg);
	printf("val=%d read: %s\n", res, modbus_msg);
	
	// parsing
	uint8_t receive_buff[127] = {0};
	res = parserMsg(modbus_msg,  sizeof(modbus_msg), receive_buff);
	for (int i=0; i<res; i++)
		printf("%d ", receive_buff[i]); 
	printf("\n");

	
	// writing
	printf ("write data: ");
	printf("%d %d\n", data[0], data[1]);
	res = writeMsg(data, sizeof(data), usb_buff_tx);
	printf("val=%d write: %s\n", res, usb_buff_tx);
	
	return 0;
}
