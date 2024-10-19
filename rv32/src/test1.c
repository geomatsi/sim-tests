#include <stdint.h>

#include "htif.h"

void trap_handler(void) __attribute__((interrupt("machine")));

void trap_handler(void)
{
	while (1) {
		__asm__ volatile ("wfi");
	}
}

static void print(const char *s)
{
	while (*s)
		htif_putc(*s++);
}

int main(void)
{
	print("hello world\n");
	htif_exit(10);
}
