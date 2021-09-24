/*
 * This feature is only available for the SRAM region and Peripheral region
 * Formula for bit banding:
 * Alias Address =
 * 		alias_base + (32 * (bit_band_memory_addr - bit_band_base)) + bit * 4
 */
#include<stdint.h>
#define ALIAS_BASE				0x22000000
#define BITBAND_BASE			0x20000000

int main(void)
{
	// Clearing the bit using HGIH LEVEL C method
	uint32_t * ptr = (uint32_t *)0x20000200;		// The memory address
	*ptr = 0xff;									// current holds 1111 1111
	*ptr &= ~(1 << 7);								// Clearing the 7th bit

	// Bit banding method
	*ptr = 0xff;									// Reset the vakue back to FF
	uint8_t * alias_addr = (uint8_t *)( ALIAS_BASE + (32 * (0x20000200 - BITBAND_BASE)) + 7 * 4);
	*alias_addr = 0;								// Clearing bit 7 of 0x20000200
}
