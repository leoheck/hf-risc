#include <hf-risc.h>
#include "assoc.h"

int main(void) {

	uint32_t steps, i;
	steps = 16;

	for (i = 0; i < steps; i++) {
		printf("DE configuration: %d\n", i);
		DE_PAUSE ^= -1;
		DE_CONFIG ^= -1;
		DE_CDE_SEL ^= -1;
		DE_CDE_CTRL ^= -1;
		DE_MDE_SEL ^= -1;
		delay_ms(100);
	}

	return 0;
}
