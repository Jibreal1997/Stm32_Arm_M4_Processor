/*
 * 008SVC_Operators.c
 *
 * So in this program we are actually using supervisor calls (SVC) exceptions in order to provide
 * the software with some processor hardware values such as register content.
 */

#include <stdio.h>
#include <stdint.h>

void SVC_Handler_c(uint32_t * pBaseOfStackFrame);

int32_t add_numbers(int32_t x, int32_t y)
{
	int32_t res;

	// Calling a SVC exception, that will return with value into the R0 register
	__asm volatile("SVC #36");

	// Reading that R0 register and storing its value into res.
	__asm volatile("MOV %0,R0":"=r"(res) ::);

	// Returning the res value back to the main function.
	return res;
}

int32_t sub_numbers(int32_t x, int32_t y)
{
	int32_t res;

	// Calling a SVC exception, that will return with value into the R0 register
	__asm volatile("SVC #37");

	// Reading that R0 register and storing its value into res.
	__asm volatile("MOV %0,R0":"=r"(res) ::);

	// Returning the res value back to the main function.
	return res;

}

int32_t mul_numbers(int32_t x, int32_t y)
{
	int32_t res;

	// Calling a SVC exception, that will return with value into the R0 register
	__asm volatile("SVC #38");

	// Reading that R0 register and storing its value into res.
	__asm volatile("MOV %0,R0":"=r"(res) ::);

	// Returning the res value back to the main function.
	return res;

}


int32_t div_numbers(int32_t x, int32_t y)
{
	int32_t res;

	// Calling a SVC exception, that will return with value into the R0 register
	__asm volatile("SVC #39");

	// Reading that R0 register and storing its value into res.
	__asm volatile("MOV %0,R0":"=r"(res) ::);

	// Returning the res value back to the main function.
	return res;

}

int main(void)
{

	int32_t res;

	// Call the functions which will later call the SVC exceptions
	res = add_numbers(40, -90);
	printf("The result = %ld \n", res);

	res = sub_numbers(25, 150);
	printf("The result = %ld \n", res);

	res = add_numbers(394, 890);
	printf("The result = %ld \n", res);

	res = add_numbers(67, -3);
	printf("The result = %ld \n", res);


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

	int32_t arg0, arg1, res;
	uint8_t * pReturn_addr = (uint8_t *)pBaseOfStackFrame[6];

	//2. Decrement the return address by 2 to point to the
	//opcode of the SVC instruction in the program memory
	pReturn_addr -= 2;

	// Extract the SVC number
	uint8_t svc_number = *pReturn_addr;

	printf("The SVC number is = %d \n", svc_number);

	arg0 = pBaseOfStackFrame[0];
	arg1 = pBaseOfStackFrame[1];

	switch(svc_number)
	{
	case 36:
		res = arg0 + arg1;
		break;

	case 37:
		res = arg0 - arg1;
		break;

	case 38:
		res = arg0 * arg1;
		break;

	case 39:
		res = arg0 / arg1;
		break;

	default:
		printf("Invalid SVC code. \n");
	}

	pBaseOfStackFrame[0] = res;

}
