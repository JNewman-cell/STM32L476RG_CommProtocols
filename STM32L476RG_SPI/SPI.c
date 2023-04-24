#include "SPI.h"

// Note: When the data frame size is 8 bit, "SPIx->DR = byte_data;" works incorrectly. 
// It mistakenly send two bytes out because SPIx->DR has 16 bits. To solve the program,
// we should use "*((volatile uint8_t*)&SPIx->DR) = byte_data";
void SPI1_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	GPIOB->MODER &= ~GPIO_MODER_MODE3;
	GPIOB->MODER &= ~GPIO_MODER_MODE4;
	GPIOB->MODER &= ~GPIO_MODER_MODE5;
	GPIOB->MODER |= (GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1);
	
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL3;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL4;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL5;
	GPIOB->AFR[0] |= (GPIO_AFRL_AFSEL3_2 | GPIO_AFRL_AFSEL3_0);
	GPIOB->AFR[0] |= (GPIO_AFRL_AFSEL4_2 | GPIO_AFRL_AFSEL4_0);
	GPIOB->AFR[0] |= (GPIO_AFRL_AFSEL5_2 | GPIO_AFRL_AFSEL5_0);
	
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT3;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT4;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT5;
	
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR3;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR4;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5;
	GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR4 | GPIO_OSPEEDER_OSPEEDR5);
	
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;
}

void SPI2_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	GPIOB->MODER &= ~GPIO_MODER_MODE13;
	GPIOB->MODER &= ~GPIO_MODER_MODE14;
	GPIOB->MODER &= ~GPIO_MODER_MODE15;
	GPIOB->MODER |= (GPIO_MODER_MODE13_1 | GPIO_MODER_MODE14_1 | GPIO_MODER_MODE15_1);
	
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL13;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL14;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL15;
	GPIOB->AFR[1] |= (GPIO_AFRH_AFSEL13_2 | GPIO_AFRH_AFSEL13_0);
	GPIOB->AFR[1] |= (GPIO_AFRH_AFSEL14_2 | GPIO_AFRH_AFSEL14_0);
	GPIOB->AFR[1] |= (GPIO_AFRH_AFSEL15_2 | GPIO_AFRH_AFSEL15_0);
	
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT13;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT14;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT15;
	
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR13;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR14;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR15;
	GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR13 | GPIO_OSPEEDER_OSPEEDR14 | GPIO_OSPEEDER_OSPEEDR15);
	
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD14;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD15;
}

void SPI2_Init(void){
	//(a) Enable the SPI clock.
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
	
	//(b) Set the RCC SPI reset bit, then clear it to reset the SPI1 or SPI2 peripheral.
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_SPI2RST;
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_SPI2RST;

	//(c) Disable the SPI enable bit. The peripheral must be configured while it is disabled.
	SPI2->CR1 &= ~SPI_CR1_SPE;

	//(d) Configure the peripheral for full-duplex communication.
	SPI2->CR1 &= ~SPI_CR1_RXONLY;

	//(e) Configure the peripheral for 2-line unidirectional data mode.
	SPI2->CR1 &= ~SPI_CR1_BIDIMODE;
	
	//(f) Disable output in bidirectional mode.
	SPI2->CR1 &= ~SPI_CR1_BIDIOE;

	//(g) Configure the frame format as MSB first.
	SPI2->CR1 &= ~SPI_CR1_LSBFIRST;

	//(h) Configure the frame format to 8-bit mode.
	SPI2->CR2 &= ~SPI_CR2_DS;
	SPI2->CR2 |= (SPI_CR2_DS_0 | SPI_CR2_DS_1 |SPI_CR2_DS_2);

	//(i) Use Motorola SPI mode.
	SPI2->CR2 &= ~SPI_CR2_FRF;

	//(j) Configure the clock to low polarity.
	SPI2->CR1 &= ~SPI_CR1_CPOL;

	//(k) Configure the clock to first clock transition.
	SPI2->CR1 &= ~SPI_CR1_CPHA;

	//(l) Set the baud rate prescaler to 16.
	SPI2->CR1 &= ~SPI_CR1_BR;
	SPI2->CR1 |= (SPI_CR1_BR_0 | SPI_CR1_BR_1);

	//(m) Disable hardware CRC calculation.
	SPI2->CR1 &= ~SPI_CR1_CRCEN;

	//set to slave mode
	SPI2->CR1 &= ~SPI_CR1_MSTR;

	//(o) Enable software SSM.
	SPI2->CR1 |= SPI_CR1_SSM;

	//(p) Enable NSS pulse generation.
	SPI2->CR2 |= SPI_CR2_NSSP;
	
	//configure internal slave select bit to 0
	SPI2->CR1 &= ~SPI_CR1_SSI;

	//(r) Set the FIFO threshold to 1/4 (required for 8-bit mode).
	SPI2->CR2 |= SPI_CR2_FRXTH;

	//(s) Enable the SPI peripheral.
	SPI2->CR1 |= SPI_CR1_SPE;
	
}

void SPI1_Init(void){
	// TODO: initialize SPI1 peripheral as master
	//(a) Enable the SPI clock.

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	//(b) Set the RCC SPI reset bit, then clear it to reset the SPI1 or SPI2 peripheral.

	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
	//(c) Disable the SPI enable bit. The peripheral must be configured while it is disabled.

	SPI1->CR1 &= ~SPI_CR1_SPE;
	//(d) Configure the peripheral for full-duplex communication.

	SPI1->CR1 &= ~SPI_CR1_RXONLY;
	//(e) Configure the peripheral for 2-line unidirectional data mode.

	SPI1->CR1 &= ~SPI_CR1_BIDIMODE;
	//(f) Disable output in bidirectional mode.

	SPI1->CR1 &= ~SPI_CR1_BIDIOE;
	//(g) Configure the frame format as MSB first.

	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;
	//(h) Configure the frame format to 8-bit mode.

	SPI1->CR2 &= ~SPI_CR2_DS;
	SPI1->CR2 |= (SPI_CR2_DS_0 | SPI_CR2_DS_1 |SPI_CR2_DS_2);
	//(i) Use Motorola SPI mode.

	SPI1->CR2 &= ~SPI_CR2_FRF;
	//(j) Configure the clock to low polarity.

	SPI1->CR1 &= ~SPI_CR1_CPOL;
	//(k) Configure the clock to first clock transition.

	SPI1->CR1 &= ~SPI_CR1_CPHA;
	//(l) Set the baud rate prescaler to 16.

	SPI1->CR1 &= ~SPI_CR1_BR;
	SPI1->CR1 |= (SPI_CR1_BR_0 | SPI_CR1_BR_1);
	//(m) Disable hardware CRC calculation.

	SPI1->CR1 &= ~SPI_CR1_CRCEN;
	//set to master mode

	SPI1->CR1 |= SPI_CR1_MSTR;
	//(o) Enable software SSM.

	SPI1->CR1 |= SPI_CR1_SSM;
	//(p) Enable NSS pulse generation.

	SPI1->CR2 |= SPI_CR2_NSSP;
	//(r) Set the FIFO threshold to 1/4 (required for 8-bit mode).

	SPI1->CR2 |= SPI_CR2_FRXTH;
	
	//configure internal slave select bit to 0
	
	SPI1->CR1 |= SPI_CR1_SSI;
	//(s) Enable the SPI peripheral.

	SPI1->CR1 |= SPI_CR1_SPE;
}
 
void SPI_Send_Byte(SPI_TypeDef* SPIx, uint8_t write_data) {
	// TODO: send data from SPI1
	while((SPIx->SR & SPI_SR_TXE ) != SPI_SR_TXE );
	
	*((volatile uint8_t*)&SPIx->DR) = write_data;
	
	while( (SPIx->SR & SPI_SR_BSY) == SPI_SR_BSY );
}

void SPI_Receive_Byte(SPI_TypeDef* SPIx, uint8_t* read_data) {
	// TODO: receive data from SPI2
	while( (SPIx->SR & SPI_SR_RXNE ) != SPI_SR_RXNE );
	
	*read_data = *((volatile uint8_t*)&SPIx->DR);
}
