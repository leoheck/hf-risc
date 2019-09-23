# architecture: mips or riscv
# ARCH = mips
ARCH = riscv

BAUDRATE = 57600
F_CLK = 25000000
SERIAL_DEV = /dev/ttyUSB0

# compiler flags
CFLAGS_STRIP = -fdata-sections -ffunction-sections
LDFLAGS_STRIP = --gc-sections
LD_SCRIPT = hf-risc.ld

ifeq (riscv, riscv)
CROSS_COMPILE = riscv32-unknown-elf-
CFLAGS = -march=rv32i -mabi=ilp32 -Wall -Os -c -mstrict-align -ffreestanding -nostdlib -ffixed-s10 -ffixed-s11 -I ./include -DCPU_SPEED=${F_CLK} -DLITTLE_ENDIAN $(CFLAGS_STRIP) -DDEBUG_PORT #-ffixed-s10 -ffixed-s11 -mno-div -mrvc -fPIC -DDEBUG_PORT
AS_FLAGS = -march=rv32i -mabi=ilp32 #-fPIC
LD_FLAGS = -melf32lriscv $(LDFLAGS_STRIP)
DUMP_FLAGS = -Mno-aliases
else
CROSS_COMPILE = mips-elf-
CFLAGS_NO_HW_MULDIV = -mnohwmult -mnohwdiv -ffixed-lo -ffixed-hi
GCROSS_COMPILE_mips = -Wall -O2 -c -mips2 -mno-branch-likely -mpatfree -mfix-r4000 -mno-check-zero-division -msoft-float -ffreestanding -nostdlib -fomit-frame-pointer -G 0 -I ./include -DCPU_SPEED=${F_CLK} -DBIG_ENDIAN $(CFLAGS_NO_HW_MULDIV) $(CFLAGS_STRIP) -DDEBUG_PORT
AS_mips = -mips1 -msoft-float
LD_mips = -mips1 $(LDFLAGS_STRIP)
endif

.DEFAULT_GOAL := all


tools:
	@ which $(CROSS_COMPILE)gcc
	@ which $(CROSS_COMPILE)as
	@ which $(CROSS_COMPILE)LD_mips
	@ which $(CROSS_COMPILE)objdump
	@ which $(CROSS_COMPILE)readelf
	@ which $(CROSS_COMPILE)objcopy
	@ which $(CROSS_COMPILE)size


# serial:
# 	stty ${BAUDRATE} raw cs8 -parenb -crtscts clocal cread ignpar ignbrk -ixon -ixoff -ixany -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke -F ${SERIAL_DEV}

# load: serial
# 	cp code.bin ${SERIAL_DEV}

# debug: serial
# 	cat ${SERIAL_DEV}


#======

crt_o = build/crt0.o build/libc.o build/interrupt.o build/math.o build/malloc.o
extra_o = build/spi.o build/mcp23s17.o

crt: $(crt_o)

extra: $(extra_o)

build/crt0.o: ./lib/$(ARCH)/crt0.s
	@ echo "Building $@ $(ARCH)"
	@ mkdir -p build/
	$(CROSS_COMPILE)as $(AS_FLAGS) -o $@ $^

build/%.o: ./lib/%.c
	@ echo "Building $@"
	@ mkdir -p build/
	@ $(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^

#========

# monitor:
# 	$(CROSS_COMPILE)as $(AS_FLAGS) -o boot_rom.o lib/$(ARCH)/boot_rom.s
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o libc.o lib/libc.c
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o math.o lib/math.c
# 		$(CROSS_COMPILE)gcc $(CFLAGS) -o monitor.o boot/monitor.c
# 	$(CROSS_COMPILE)ld $(LD_FLAGS) -Tlib/$(ARCH)/hf-risc_bootloader.ld -Map test.map -N -o test.elf \
# 		boot_rom.o libc.o monitor.o
# 	$(CROSS_COMPILE)objdump $(DUMP_FLAGS) --disassemble --reloc test.elf > test.lst
# 	$(CROSS_COMPILE)objdump $(DUMP_FLAGS) -h test.elf > test.sec
# 	$(CROSS_COMPILE)objdump $(DUMP_FLAGS) -s test.elf > test.cnt
# 	$(CROSS_COMPILE)objcopy -O binary test.elf test.bin --pad-to 4096
# 	$(CROSS_COMPILE)size test.elf
# 	mv test.elf code.elf
# 	mv test.bin code.bin
# 	mv test.lst code.lst
# 	mv test.sec code.sec
# 	mv test.cnt code.cnt
# 	mv test.map code.map
# 	hexdump -v -e '4/1 "%02x" "\n"' code.bin > boot.txt
# 	xxd -b -c 4 code.bin | awk '{print $$2 $$3 $$4 $$5}' > boot_bin.txt
# 	./../tools/xilinx/ram_image ./../tools/xilinx/ram_xilinx.vhd boot.txt boot_ram.vhd

# boot_sim:
# 	$(CROSS_COMPILE)as $(AS_FLAGS) -o boot_rom.o lib/$(ARCH)/boot_rom.s
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o libc.o lib/libc.c
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o math.o lib/math.c
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o bootloader_sim.o boot/bootloader_sim.c
# 	$(CROSS_COMPILE)ld $(LD_FLAGS) -Tlib/$(ARCH)/hf-risc_bootloader.ld -Map test.map -N -o test.elf \
# 		boot_rom.o libc.o bootloader_sim.o
# 	$(CROSS_COMPILE)objdump $(DUMP_FLAGS) --disassemble --reloc test.elf > test.lst
# 	$(CROSS_COMPILE)objdump $(DUMP_FLAGS) -h test.elf > test.sec
# 	$(CROSS_COMPILE)objdump $(DUMP_FLAGS) -s test.elf > test.cnt
# 	$(CROSS_COMPILE)objcopy -O binary test.elf test.bin
# 	$(CROSS_COMPILE)size test.elf
# 	mv test.elf code.elf
# 	mv test.bin code.bin
# 	mv test.lst code.lst
# 	mv test.sec code.sec
# 	mv test.cnt code.cnt
# 	mv test.map code.map
# 	hexdump -v -e '4/1 "%02x" "\n"' code.bin > boot.txt

# eeprom_sim:
# 	echo "b16b00b5" > eeprom.txt
# 	printf "%08x\n" `stat -L -c %s code.txt` >> eeprom.txt
# 	cat code.txt >> eeprom.txt


# ====

apps_c = app/labyrinth.c app/euler.c app/sort.c app/test_trig.c app/pi.c app/malloc_test.c app/ann.c app/xtea2.c app/ann2.c app/hello.c app/float_fixed.c app/xtea.c app/euler_fixed.c app/base64.c app/peripherals_test.c app/test64.c app/mem_test.c app/hanoi.c app/test.c app/fib.c app/core_test.c app/encode.c app/sudoku.c app/test_fp.c app/xtea_hw.c app/newton.c app/test_fixed.c app/interrupt_test.c app/test_crc.c
apps_dir = $(shell find ./app -mindepth 1 -maxdepth 1 -type d)
# apps_c = $(shell find ./app -maxdepth 1 -name "*.c")

apps_o = $(subst app/,build/,$(apps_c:.c=.o))

apps = $(apps_o:.o=)

lsc:
	@ echo "$(apps_c)" | tr " " "\n" | nl

lso:
	@ echo "$(apps_o)" | tr " " "\n" | nl

lsd:
	@ echo "$(apps_dir)" | tr " " "\n" | nl


all: crt $(apps_o)

build/exp_io.o: crt app/%.o
	@ make -s extra_objs="build/spi.o build/mcp23s17.o" $@

build/%.o: app/%.c
	@ echo "Building $@"
	@ $(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^
	@ mkdir -p $(@:.o=)
	@ $(CROSS_COMPILE)ld $(LD_FLAGS) -T./lib/$(ARCH)/$(LD_SCRIPT) -Map $(@:.o=)/code.map -N -o $(@:.o=)/code.elf $(crt_o) $(extra_objs) $@
	@ $(CROSS_COMPILE)objdump --disassemble --reloc $(@:.o=)/code.elf > $(@:.o=)/code.lst
	@ $(CROSS_COMPILE)objdump -h $(@:.o=)/code.elf > $(@:.o=)/code.sec
	@ $(CROSS_COMPILE)objdump -s $(@:.o=)/code.elf > $(@:.o=)/code.cnt
	@ $(CROSS_COMPILE)objcopy -O binary $(@:.o=)/code.elf $(@:.o=)/code.bin
	@ $(CROSS_COMPILE)size $(@:.o=)/code.elf | sed "s|build/.*/code.elf|$(basename $(notdir $@))|g" | tee $(@:.o=.size)
	@ hexdump -v -e '4/1 "%02x" "\n"' $(@:.o=)/code.bin > $(@:.o=)/code.txt





# coremark: $(crt_o)
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o core_list_join.o app/coremark/core_list_join.c
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o core_main.o app/coremark/core_main.c -DFLAGS_STR=\"'$(CROSS_COMPILE)gcc'$(CFLAGS) \" -Dee_printf=printf
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o core_matrix.o app/coremark/core_matrix.c
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o core_state.o app/coremark/core_state.c
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o core_util.o app/coremark/core_util.c
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o core_portme.o app/coremark/core_portme.c -Dee_printf=printf -DPERFORMANCE_RUN=1 -DITERATIONS=1000
# 	$(CROSS_COMPILE)gcc $(CFLAGS) -o coremark.o app/coremark/coremark.c
# 	# @ $(MAKE) --no-print-directory link

# exp_io.o: $(crt_o) spi.o mcp23s17.o
# 	@ $(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^
# 	@ $(CROSS_COMPILE)ld $(LD_FLAGS) -Tlib/$(ARCH)/$(LD_SCRIPT) -Map code.map -N -o code.elf $^ $@
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) --disassemble --reloc code.elf > code.lst
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) -h code.elf > code.sec
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) -s code.elf > code.cnt
# 	@ $(CROSS_COMPILE)objcopy -O binary code.elf code.bin
# 	@ $(CROSS_COMPILE)size code.elf | sed "s/code.elf/$@/g" | tee $@.size
# 	@ hexdump -v -e '4/1 "%02x" "\n"' code.bin > code.txt

# test_spi.o: $(crt_o) spi.o lib/spi.c
# 	@ $(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^
# 	@ $(CROSS_COMPILE)ld $(LD_FLAGS) -Tlib/$(ARCH)/$(LD_SCRIPT) -Map code.map -N -o code.elf $^ $@
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) --disassemble --reloc code.elf > code.lst
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) -h code.elf > code.sec
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) -s code.elf > code.cnt
# 	@ $(CROSS_COMPILE)objcopy -O binary code.elf code.bin
# 	@ $(CROSS_COMPILE)size code.elf | sed "s/code.elf/$@/g" | tee $@.size
# 	@ hexdump -v -e '4/1 "%02x" "\n"' code.bin > code.txt

# aes_tiny.o: $(crt_o) aes.o app/aes_tiny/aes.c
# 	@ $(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^
# 	@ $(CROSS_COMPILE)ld $(LD_FLAGS) -Tlib/$(ARCH)/$(LD_SCRIPT) -Map code.map -N -o code.elf $^ $@
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) --disassemble --reloc code.elf > code.lst
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) -h code.elf > code.sec
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) -s code.elf > code.cnt
# 	@ $(CROSS_COMPILE)objcopy -O binary code.elf code.bin
# 	@ $(CROSS_COMPILE)size code.elf | sed "s/code.elf/$@/g" | tee $@.size
# 	@ hexdump -v -e '4/1 "%02x" "\n"' code.bin > code.txt

# aes_lite.o: $(crt_o) app/aes_lite/aes.c
# 	@ $(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^
# 	@ $(CROSS_COMPILE)ld $(LD_FLAGS) -Tlib/$(ARCH)/$(LD_SCRIPT) -Map code.map -N -o code.elf $^ $@
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) --disassemble --reloc code.elf > code.lst
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) -h code.elf > code.sec
# 	@ $(CROSS_COMPILE)objdump $(DUMP_FLAGS) -s code.elf > code.cnt
# 	@ $(CROSS_COMPILE)objcopy -O binary code.elf code.bin
# 	@ $(CROSS_COMPILE)size code.elf | sed "s/code.elf/$@/g" | tee $@.size
# 	@ hexdump -v -e '4/1 "%02x" "\n"' code.bin > code.txt

# include app/malardalen/malardalen.mk
# include app/powerstone/powerstone.mk



clean:
	rm -rf build
	-rm -rf *.vhd
	-rm -rf *~
	-rm -rf app/*~

info:
	@ find -name "*.size" -printf "cat %p\n" | sh | sort | uniq | tac
