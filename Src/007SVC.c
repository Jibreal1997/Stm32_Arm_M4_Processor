/*
 * 007SVC.c
 *
 */
#include <stdio.h>
#include <stdint.h>

int main(void)
{

__asm("SVC #8");		// Calling the SVC exception
for(;;);

}

__attribute__((naked)) void SVC_Handler(void)
{

	//1. Get the value of the MSP from the handler
	__asm("MRS R0, MSP");
	__asm("B SVC_Handler_c");	// r0 will be sent as argument by default
}

void SVC_Handler_c(uint32_t * pBaseOfStackFrame)
{
	printf("Inside SVC_ Handler \n");
	uint8_t * pReturn_addr = (uint8_t *)pBaseOfStackFrame[6];

	//2. Decrement the return address by 2 to point to the
	//opcode of the SVC instruction in the program memory
	pReturn_addr -= 2;

	// Extract the SVC number
	uint8_t svc_number = *pReturn_addr;

	printf("The SVC number is = %d \n", svc_number);


}

