#include <hf-risc.h>
#include "assoc.h"

// Test all peripherals
uint32_t to_onehot(uint32_t val) {
    uint32_t onehot;
    switch(val) {
        case  0: onehot = 0x0001; break;
        case  1: onehot = 0x0002; break;
        case  2: onehot = 0x0004; break;
        case  3: onehot = 0x0008; break;
        case  4: onehot = 0x0010; break;
        case  5: onehot = 0x0020; break;
        case  6: onehot = 0x0040; break;
        case  7: onehot = 0x0080; break;
        case  8: onehot = 0x0100; break;
        case  9: onehot = 0x0200; break;
        case 10: onehot = 0x0400; break;
        case 11: onehot = 0x0800; break;
        case 12: onehot = 0x1000; break;
        case 13: onehot = 0x2000; break;
        case 14: onehot = 0x4000; break;
        case 15: onehot = 0x8000; break;
        default: onehot = 0x0001;
    }
    return onehot;
}

int main(void) {

    // sync mac

    printf("\nMAC SYNC (16 bits)\n\n");

    // SYNC_MAC_RST = 0; // reset mac sync

    printf("-- 1st MAC operation\n");
    SYNC_MAC_OPER = 0x002a001b;
    printf("   INT_MAC_OPER: %08x\n", SYNC_MAC_OPER);
    printf(" INT_MAC_RESULT: %08x\n", SYNC_MAC_RESULT);
    printf("       expected: %08x\n", 0x46e);

    printf("-- 2nd MAC operation\n");
    SYNC_MAC_OPER = 0x00120014;
    printf("   INT_MAC_OPER: %08x\n", SYNC_MAC_OPER);
    printf(" INT_MAC_RESULT: %08x\n", SYNC_MAC_RESULT);
    printf("       expected: %08x\n", 0x5d6);

    // async mac

    printf("\nMAC ASYNC (8 bits)\n\n");

    ASYNC_MAC_RST = 0; // reset mac async

    printf("-- 1st MAC operation\n");
    ASYNC_MAC_OPER = 0x00002a1b;
    printf("   INT_MAC_OPER: %04x\n", ASYNC_MAC_OPER);
    printf(" INT_MAC_RESULT: %04x\n", ASYNC_MAC_RESULT);
    printf("       expected: %04x\n", 0x46e);

    printf("-- 2nd MAC operation\n");
    ASYNC_MAC_OPER = 0x00001214;
    printf("   INT_MAC_OPER: %04x\n", ASYNC_MAC_OPER);
    printf(" INT_MAC_RESULT: %04x\n", ASYNC_MAC_RESULT);
    printf("       expected: %04x\n", 0x5d6);

    // delay line

    printf("\nDELAY LINE\n\n");

    printf("-- Delay line, initial configs\n");

    printf("    DE_PAUSE: %08x\n", DE_PAUSE);
    printf("   DE_CONFIG: %08x\n", DE_CONFIG);
    printf("  DE_CDE_SEL: %08x\n", DE_CDE_SEL);
    printf(" DE_CDE_CTRL: %08x\n", DE_CDE_CTRL);
    printf("  DE_MDE_SEL: %08x\n", DE_MDE_SEL);

    printf("-- Delay line, set new configuration\n");

    DE_PAUSE = 0x3; // pause mux-de and comp-de
    DE_CONFIG = 18;
    DE_CDE_SEL = 15; // set total comp-de delay
    DE_CDE_CTRL = to_onehot(0); // set comp-de middle point
    DE_MDE_SEL = 0; // set MUX-de delay

    printf("    DE_PAUSE: %08x\n", DE_PAUSE);
    printf("   DE_CONFIG: %08x\n", DE_CONFIG);
    printf("  DE_CDE_SEL: %08x\n", DE_CDE_SEL);
    printf(" DE_CDE_CTRL: %08x\n", DE_CDE_CTRL);
    printf("  DE_MDE_SEL: %08x\n", DE_MDE_SEL);

    DE_PAUSE = 0x0; // release mux-de and comp-de

    printf(" POST_DE_PAUSE: %08x\n", DE_PAUSE);

    return 0;
}
