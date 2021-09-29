/*
* Configurable faults
*  Enable faults via system control block via the System Handler Control and State Register
 */
#include <stdint.h>
#include <stdio.h>

uint32_t * pSHCSR =  (uint32_t *)0xE000ED24;

int main(void)
{
	// Enabling the various faults
	*pSHCSR = (0X7 << 16);

	// Forcing the processor to execute invalid instruction
	uint32_t * pSRAM = (uint32_t * ) 0x20001000;
	*pSRAM = 0xFFFFFFFF;	// Storing some invalid opcode in this location
	void (*some_address) (void);	// Creating a function pointer
	some_address = (void*)0x20001001;	// Making it point to our invalid opcode

	some_address();					// Calling the function pointer

	for(;;);
}

void HardFault_Handler(void)
{
	while(1);

}

void MemManage_Handler(void)
{
	while(1);

}

void BusFault_Handler(void)
{
	while(1);

}

__attribute__((naked)) void UsageFault_Handler(void)
{
	// Here we exwtracted the value of the MSP which is also the base address of the
	// stack frame and got saved during the exception entry from thread mode to handler mode.

	__asm("MRS r0, MSP");
	__asm("B UsageFault_Handler_c");		// The argument r0 will be automatically passed to the Calle function

}

void UsageFault_Handler_c(uint32_t * pBaseStackFrame)
{
	printf("Base stack frame = %p \n", pBaseStackFrame);
	printf("R0 = %lx \n", pBaseStackFrame[0]);
	printf("R1 = %lx \n", pBaseStackFrame[1]);
	printf("R2 = %lx \n", pBaseStackFrame[2]);
	printf("R3 = %lx \n", pBaseStackFrame[3]);
	printf("R12 = %lx \n", pBaseStackFrame[4]);
	printf("LR = %lx \n", pBaseStackFrame[5]);
	printf("PC = %lx \n", pBaseStackFrame[6]);
	printf("XPSR = %lx \n", pBaseStackFrame[7]);

	while(1);
}

