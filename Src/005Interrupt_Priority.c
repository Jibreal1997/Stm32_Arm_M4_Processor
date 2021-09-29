#include <stdio.h>
#include <stdint.h>

// Define the various addresses
uint32_t * NVIC_ISER0 = (uint32_t *)0xE000E100;
uint32_t * NVIC_ISPR0 = (uint32_t *)0xE000E200;
uint32_t * NVIC_IPR_BASEADDR = (uint32_t *) 0xE000E400;

// IRQ Numbers
#define TIM2_IRQ_NO		28
#define TIM3_IRQ_NO		29

void SetPriority(uint32_t IRQ_Number, uint32_t PriorityValue)
{
	uint32_t regNum = IRQ_Number / 4;
	uint32_t * NVIC_IPRX_ADDRESS = NVIC_IPR_BASEADDR + regNum;
	uint16_t Position = ((IRQ_Number % 4) * 8) + 4;

	// Configuring the priority
	*NVIC_IPRX_ADDRESS &= ~(0XFF << Position);
	*NVIC_IPRX_ADDRESS |= (PriorityValue << Position);

}

int main()
{
	SetPriority(TIM2_IRQ_NO, 0X2);			// TIM2 has lower priority
	SetPriority(TIM3_IRQ_NO, 0X1);			// TIM3 has higher priority

	// Set the pending for TIM2
	*NVIC_ISPR0 |= (1 << TIM2_IRQ_NO);

	// Enable the interrupts of both TIM2 and TIM3
	*NVIC_ISER0 |= (1 << TIM3_IRQ_NO);
	*NVIC_ISER0 |= (1 << TIM2_IRQ_NO);


}

void TIM2_IRQHandler(void)
{
	printf("This is the TIM2 Handler \n");
	*NVIC_ISPR0 |= (1 << TIM3_IRQ_NO);
	while(1);
}

void TIM3_IRQHandler(void)
{
	printf("This is the TIM3 Handler \n");
	while(1);
}
