/*
 * 007SVC.c
 *
 */
#include <stdio.h>
#include <stdint.h>

int main(void)
{

// Calling the SVC exception
__asm("SVC #8");

// assigning the contents of R0 to data variable
uint32_t data;
__asm volatile("MOV %0,R0":"=r"(data) ::);

printf(" New svc number = %d ", data);

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

	svc_number = svc_number + 4;

	//Storing the value of the svc_number in the r0 register
	pBaseOfStackFrame[0] = svc_number;


}

