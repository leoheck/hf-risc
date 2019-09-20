
## ONLY FOR ASSOC

ARCH = riscv
CROSS_COMPILE = riscv32-unknown-elf-

CLK_FREQ = 25000000

CFLAGS_STRIP = -fdata-sections -ffunction-sections
LDFLAGS_STRIP = --gc-sections
LD_SCRIPT = hf-risc.ld

CFLAGS = -march=rv32i -mabi=ilp32 -Wall -Os -c -mstrict-align -ffreestanding -nostdlib \
	-ffixed-s10 -ffixed-s11 -I ../../include \
	-DCPU_SPEED=$(CLK_FREQ) -DLITTLE_ENDIAN $(CFLAGS_STRIP) -DDEBUG_PORT

AS_FLAGS = -march=rv32i -mabi=ilp32 #-fPIC
LD_FLAGS = -melf32lriscv $(LDFLAGS_STRIP)
DUMP_FLAGS = -Mno-aliases

srcs = $(shell find -name "*.c")
objs = $(addprefix build/,$(srcs:.c=.o))

all: crt $(objs)

crt_o = build/crt0.o build/libc.o build/interrupt.o build/math.o build/malloc.o

crt: $(crt_o)

build/crt0.o: ../../lib/$(ARCH)/crt0.s
	@ echo "Building $@"
	@ mkdir -p build/
	@ $(CROSS_COMPILE)as $(AS_FLAGS) -o $@ $^

build/%.o: ../../lib/%.c
	@ echo "Building $@"
	@ mkdir -p build/
	@ $(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^

build/%.o: %.c
	@ echo "Building $@"
	@ $(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^
	@ mkdir -p $(@:.o=)
	@ $(CROSS_COMPILE)ld $(LD_FLAGS) -T../../lib/$(ARCH)/$(LD_SCRIPT) -Map $(@:.o=)/code.map -N -o $(@:.o=)/code.elf $(crt_o) $@
	@ $(CROSS_COMPILE)objdump --disassemble --reloc $(@:.o=)/code.elf > $(@:.o=)/code.lst
	@ $(CROSS_COMPILE)objdump -h $(@:.o=)/code.elf > $(@:.o=)/code.sec
	@ $(CROSS_COMPILE)objdump -s $(@:.o=)/code.elf > $(@:.o=)/code.cnt
	@ $(CROSS_COMPILE)objcopy -O binary $(@:.o=)/code.elf $(@:.o=)/code.bin
	@ $(CROSS_COMPILE)size $(@:.o=)/code.elf
	@ hexdump -v -e '4/1 "%02x" "\n"' $(@:.o=)/code.bin > $(@:.o=)/code.txt

clean:
	rm -rf *~
	rm -rf build