/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 */


#include <stdint.h>
#include <stdio.h>

void ChangeAccessLevel_unprev()
{
	//Read the control register
	__asm volatile("MRS R0,CONTROL");

	//Modify
	__asm volatile("ORR R0,R0,#0x01");

	//Write Back
	__asm volatile("MSR CONTROL,R0");
}


// This function generates software interrupts and only executes in Thread Mode.
void generate_interrupt()
{
	uint32_t *pSTIR = (uint32_t*)0xE000EF00;
	uint32_t *pISER0 = (uint32_t*)0xE000E100;

	// Enable the IRQ 3 interrupt
	*pISER0 |= (1 << 3);

	// Generate the Interrupt from software
	*pSTIR = (3 & 0x1FF);
}

// This is the exception handler
void HardFault_Handler(void)
{
	printf("There was a hard fault detected \n");

	//Read the control register
	__asm volatile("MRS R0,CONTROL");

	//Modify
	__asm volatile("AND R0,R0,#0x00");

	//Write Back
	__asm volatile("MSR CONTROL,R0");

	printf("Access Level changed to previliged \n");

}

int main(void)
{
	ChangeAccessLevel_unprev();			// This will change the access level to unpreviliged
	generate_interrupt();			// This will try to change it again, leading to an exception.
}
