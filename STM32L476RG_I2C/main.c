/*
 * ECE 153B - Winter 2023
 *
 * Name(s):JACKSON NEWMAN MICHELLE LY
 * Section:W
 * Lab: 4B
 */

#include "stm32l476xx.h"
#include "I2C.h"
#include "SysClock.h"
#include "UART.h"
#include <string.h>
#include <stdio.h>

// Initializes USARTx
// USART2: UART Communication with Termite
// USART1: Bluetooth Communication with Phone
void Init_USARTx(int x) {
	if(x == 1) {
		UART1_Init();
		UART1_GPIO_Init();
		USART_Init(USART1);
	} else if(x == 2) {
		UART2_Init();
		UART2_GPIO_Init();
		USART_Init(USART2);
	} else {
		// Do nothing...
	}
}

int main(void) {
	System_Clock_Init(); // System Clock = 80 MHz
	
	// Initialize I2C
	I2C_GPIO_Init();
	I2C_Initialization();

	// Initialize UART -- change the argument depending on the part you are working on
	Init_USARTx(2);
	
	int i;
	uint8_t SlaveAddress;
	uint8_t Data_Receive;
	uint8_t Data_Send;
	// Determine Slave Address
	//
	// Note the "<< 1" must be present because bit 0 is treated as a don't care in 7-bit addressing mode
	SlaveAddress = 0b1001000 << 1; // STUB - Fill in correct address 
	while(1) {	
		//printf("WORKING \n");
		Data_Send=0;
		// [TODO] - Get Temperature
		// 
		// First, send a command to the sensor for reading the temperature
		// Next, get the measurement
		I2C_SendData(I2C1, SlaveAddress, &Data_Send, 1);
		I2C_ReceiveData(I2C1, SlaveAddress, &Data_Receive, 1);
		
		printf("Temp: %dC\n",Data_Receive);
		// Some delay
		for(i = 0; i < 50000; ++i); 
	}
}
