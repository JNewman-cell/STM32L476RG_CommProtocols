/*
 * JACKSON NEWMAN
 */


#include "stm32l476xx.h"
#include "LED.h"
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
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	
	// Initialize UART -- change the argument depending on the part you are working on
	Init_USARTx(1);
	
	char rxByte;
	printf("Y = LED ON, N = LED OFF\n");
	while(1) {
		// [TODO]
		printf("Y = LED ON, N = LED OFF\n");
		scanf("%c",&rxByte);
		if (rxByte=='Y' || rxByte=='y'){
			printf("LED turned on\n");
			Green_LED_On();
		}
		else if(rxByte=='N' || rxByte=='n'){
			printf("LED turned off\n");
			Green_LED_Off();
		}
		else{
			printf("Input is invalid\n");
		}
	Init_USARTx(1);
	}
}
