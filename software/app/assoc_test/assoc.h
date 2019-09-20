
#define RESERVED_BASE    0xe0ff0000

#define SYNC_MAC_OPER    (*(volatile uint32_t *)(RESERVED_BASE + 0x4000))
#define SYNC_MAC_RESULT  (*(volatile uint32_t *)(RESERVED_BASE + 0x4010))

#define ASYNC_MAC_OPER   (*(volatile uint32_t *)(RESERVED_BASE + 0x4400))
#define ASYNC_MAC_RESULT (*(volatile uint32_t *)(RESERVED_BASE + 0x4410))
#define ASYNC_MAC_RST    (*(volatile uint32_t *)(RESERVED_BASE + 0x4420))

#define DE_CONFIG        (*(volatile uint32_t *)(RESERVED_BASE + 0x4800))
#define DE_CDE_SEL       (*(volatile uint32_t *)(RESERVED_BASE + 0x4810))
#define DE_MDE_SEL       (*(volatile uint32_t *)(RESERVED_BASE + 0x4820))
#define DE_CDE_CTRL      (*(volatile uint32_t *)(RESERVED_BASE + 0x4830))
#define DE_PAUSE         (*(volatile uint32_t *)(RESERVED_BASE + 0x4840))
