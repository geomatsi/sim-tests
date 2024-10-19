#include <stdint.h>

volatile uint64_t tohost;
volatile uint64_t fromhost;

void trap_handler(void) __attribute__((interrupt("machine")));

void trap_handler(void)
{
	while (1) {
		__asm__ volatile ("nop");
		__asm__ volatile ("nop");
		__asm__ volatile ("wfi");
	}
}

int main(void)
{
	volatile int c = 1, d = 1;

	while (c++) {
		tohost = c;
		d = fromhost;
	}

	return (int)d;
}
