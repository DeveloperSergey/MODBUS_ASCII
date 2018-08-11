#include "modbus_ascii.h"

// return len data in "toBuffer"
uint8_t writeMsg(uint8_t* fromMsg, uint8_t len_msg, uint8_t* toBuffer){
	
	uint8_t cnt = 0;
	uint8_t cnt2 = 1; // [0] = ':'
	uint8_t lrc = 0;
	
	// add ':'
	toBuffer[0] = ':';
	
	// add data
	for(; cnt < len_msg; cnt++){
		lrc += fromMsg[cnt];
		convertUint8_tToHex(fromMsg[cnt], &toBuffer[cnt2], &toBuffer[cnt2+1]);
		cnt2 += 2;
	}
	
	// add lrc
	lrc = 255 - lrc + 1;
	convertUint8_tToHex(lrc, &toBuffer[cnt2], &toBuffer[cnt2+1]);
		
	// add "\r\n"
	cnt2 += 2;
	toBuffer[cnt2] = 13;
	toBuffer[cnt2+1] = 10;
	return cnt2 + 2;
}

// Make this method !!!!
void convertUint8_tToHex(uint8_t data, uint8_t* symbol_MSB, uint8_t* symbol_LSB){
	
	*symbol_MSB = (uint8_t)(data / 16); // старший
	if (*symbol_MSB < 10)
		*symbol_MSB += 48;
	else
		*symbol_MSB = *symbol_MSB - 10 + 65;
		
	*symbol_LSB = data % 16; // младший
	if (*symbol_LSB < 10)
		*symbol_LSB += 48;
	else
		*symbol_LSB = *symbol_LSB - 10 + 65;
}

// return len of "toMsg"
uint8_t readMsg(uint8_t* fromBuff, uint8_t len_buff, uint8_t* toMsg){
		
	uint8_t cnt = 0;
	uint8_t cnt2 = 0;
	uint8_t flagMsg = 0;
	uint8_t lrc = 0;
	
	while (cnt < len_buff){
	
		if (fromBuff[cnt++] == ':'){
			for (cnt2=0; cnt < len_buff; cnt++){
				
				// if end of msg
				if (fromBuff[cnt] == 13){
					flagMsg = 1;
					break;
				}
				else{
					toMsg[cnt2++] = fromBuff[cnt];
				}
			}
			
			//if msg is true
			if (flagMsg == 1){
				//printf ("%s\n", msg);
				for(cnt=0; cnt < cnt2;){
					lrc += convertModbusASCIItoDec(toMsg[cnt], toMsg[cnt+1]);
					cnt += 2;
				}
				if (lrc != 0)
					flagMsg = 0;
			}
		}	
	}
	return cnt2;
}

// return cnt = len of msg
uint8_t parserMsg(uint8_t* fromMsg, uint8_t len_msg, uint8_t* toBuffer){
	
	uint8_t cnt = 0;
	uint8_t cnt2 = 0;

	
	while (cnt < len_msg){
		
		if ((fromMsg[cnt] == 0) || (fromMsg[cnt] == 13) || (fromMsg[cnt] == 10))
			break;
		
		toBuffer[cnt2++] = convertModbusASCIItoDec(fromMsg[cnt], fromMsg[cnt+1]);
		cnt += 2;
	}
	return cnt2;
}

// good
uint8_t convertModbusASCIItoDec(uint8_t symbol_1, uint8_t symbol_2){
	if (symbol_1 >= '0' && symbol_1 <= '9')
		symbol_1 = symbol_1 - '0';
	if (symbol_1 >= 'A' && symbol_1 <= 'F')
		symbol_1 = 10 + symbol_1 - 'A';
		
	if (symbol_2 >= '0' && symbol_2 <= '9')
		symbol_2 = symbol_2 - '0';
	if (symbol_2 >= 'A' && symbol_2 <= 'F')
		symbol_2 = 10 + symbol_2 - 'A';
		
	return (symbol_1 << 4) | symbol_2;	
}
