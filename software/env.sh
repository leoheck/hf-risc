#!/bin/bash

# Configure toolchain

TOOLPATH="/home/$USER/Dropbox/Chip-Astaroth/riscv-tools/riscv32-unknown-elf/gcc-8.3.0"

export PATH=${TOOLPATH}/bin:$PATH
export MANPATH=${TOOLPATH}/share/man:${MANPATH}

export ARCH=riscv
export CROSS_COMPILE=riscv32-unknown-elf-
