#ifndef MODBUSASCII_H
#define MODBUSASCII_H

#include <stdint.h>

// external metods
uint8_t readMsg(uint8_t* fromBuff, uint8_t len_buff, uint8_t* toMsg);
uint8_t writeMsg(uint8_t* fromMsg, uint8_t len_msg, uint8_t* toBuffer);

// inner methods
uint8_t lookForMsg(uint8_t* buff, uint8_t len, uint8_t* msg);
uint8_t convertModbusASCIItoDec(uint8_t symbol_1, uint8_t symbol_2);
void convertUint8_tToHex(uint8_t data, uint8_t* symbol_MSB, uint8_t* symbol_LSB);

#endif
