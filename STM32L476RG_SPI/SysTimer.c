
#include "SysTimer.h"

volatile uint32_t msTicks;


//******************************************************************************************
// Initialize SysTick	
//******************************************************************************************	
void SysTick_Init(void){
	// TODO: generate 1ms interrupt

	SysTick->CTRL = 0; // Disable SysTick IRQ and SysTick Counter

	SysTick->LOAD = 999; // [TODO] - Enter the correct LOAD value that will give us a 1 ms period

	SysTick->VAL = 0;

	NVIC_EnableIRQ(SysTick_IRQn);

	NVIC_SetPriority(SysTick_IRQn, 1); // Set Priority to 1

	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;		

	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  


}

//******************************************************************************************
// SysTick Interrupt Handler
//******************************************************************************************
void SysTick_Handler(void){
	msTicks++;
}
	
//******************************************************************************************
// Delay in ms
//******************************************************************************************
void delay (uint32_t T){
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < T);
	
  msTicks = 0;
}
