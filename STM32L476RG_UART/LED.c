#include "LED.h"

void LED_Init(void) {
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN);
	GPIOA->MODER &= ~(3UL<<10);
	GPIOA->MODER |= 1UL<<10;
	GPIOA->OTYPER &= ~(1UL<<5);
	GPIOA->PUPDR &= ~(3UL<<10);
}


void Green_LED_Off(void) {
	GPIOA->ODR &= ~1UL<<5;
}


void Green_LED_On(void) {
	GPIOA->ODR |= 1UL<<5;
}


void Green_LED_Toggle(void) {
	GPIOA->ODR ^= 1UL<<5;
}

