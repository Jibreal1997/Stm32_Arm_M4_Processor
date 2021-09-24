/*
 * StackPointers.c
 *  Created on: Sep 21, 2021
 *      Author: 15f14
 */
#include <stdio.h>

// Defining boundries of SRAM,STACK,MSP,PSP
#define SRAM_START		0x20000000
#define SRAM_SIZE		(40 * 1024)
#define SRAM_END		(SRAM_START + SRAM_SIZE)
#define STACK_START		SRAM_END

#define STACK_MSP_START	STACK_START
#define STACK_MSP_END	(STACK_MSP_START + 512)
#define STACK_PSP_START	(STACK_MSP_END)

int fun_add(int a, int b, int c, int d)
{
	return a+b+c+d;
}

// Generating SVC interrupt
void generate_exception(void)
{
	__asm volatile("SVC #0X02");
}

__attribute__((naked)) void change_sp_to_psp(void)
{
	// Initializing the PSP pointer
	__asm volatile(".equ SRAM_END, (0x20000000 + ( 128 * 1024))");
	__asm volatile(".equ STACK_PSP_START, (SRAM_END - 512)");

	__asm volatile("LDR R0, =STACK_PSP_START");
	__asm volatile("MSR PSP, R0");

	//Changing PSP as the Currernt SP via control reg SPSEL bit
	__asm volatile("MOV R0, #0X02");
	__asm volatile("MSR CONTROL, R0");

	// Return to main
	__asm volatile("BX LR");

}
int main(void)
{
	change_sp_to_psp();
	int ret;
	ret = fun_add(1, 2, 3, 4);
	printf("Result = %d", ret);

	generate_exception();

}

//Interrupt handler
void SVC_Handler(void)
{
	printf("In SVC handler");
}
