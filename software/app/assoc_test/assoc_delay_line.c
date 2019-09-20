#include <hf-risc.h>
#include "assoc.h"

int main(void) {

	printf("--1st MAC operation\n");

	ASYNC_MAC_OPER = 0x000a000a;
	printf("INT_MAC_OPER: %08x\n", ASYNC_MAC_OPER);
	printf("INT_MAC_RESULT: %08x\n", ASYNC_MAC_RESULT);
	printf("--2nd MAC operation\n");

	ASYNC_MAC_OPER = 0x00020004;
	printf("INT_MAC_OPER: %08x\n", ASYNC_MAC_OPER);
	printf("INT_MAC_RESULT: %08x\n", ASYNC_MAC_RESULT);

	return 0;
}