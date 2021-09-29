/*
 * 004SimpleInterrupt.c
 * Creating an interrupt for a peripheral via software (setting its ISER and ISPR in the NVIC side)
 */

#include <stdio.h>
#include <stdint.h>

#define  TIM4_IRQ_NO	30

int main(void)
{

	//Setting the NVIC IPER
	uint32_t * NVIC_ISPR0 = (uint32_t *)0xE000E200;
	*NVIC_ISPR0 |= (1 << TIM4_IRQ_NO);

	// Setting the NVIC ISER1
	uint32_t * NVIC_ISER0 = (uint32_t * )0xE000E100;
	*NVIC_ISER0 |= (1 << TIM4_IRQ_NO);

	for(;;);

}

// ISR Handler
void TIM4_IRQHandler(void)
{
	printf("This is the TIM4 interrupt Handler \n");
}

