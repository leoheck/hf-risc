

# sudo apt install iverilog
# sudo apt install gtkwave


# compila os apps, la na pasta deles
# simula 1 por 1 e pega infos que saem na tela e infos extras de execussao

# alu.vhd
# bshifter.vhd
# control.vhd
# cpu.vhd
# datapath.vhd
# int_control.vhd
# reg_bank.vhd


files_vhd = \
	../../riscv/core_rv32i/cpu.vhd \
	../../devices/peripherals/standard_soc_assoc.vhd
	spi_sram_ctrl \
	M23LC1024 \
	M25LC256 \
	boot_ram \
	bram \
	boot_ram.vhd \
	ram.vhd \
	hf-riscv_assoc_tb.vhd




sim:
	iverilog -t vhdl -o test $(files_vhd)


clean:



# Usage: iverilog [-ESvV] [-B base] [-c cmdfile|-f cmdfile]
#                 [-g1995|-g2001|-g2005|-g2005-sv|-g2009|-g2012] [-g<feature>]
#                 [-D macro[=defn]] [-I includedir]
#                 [-M [mode=]depfile] [-m module]
#                 [-N file] [-o filename] [-p flag=value]
#                 [-s topmodule] [-t target] [-T min|typ|max]
#                 [-W class] [-y dir] [-Y suf] [-l file] source_file(s)




# hf-riscv_basic_standard_soc_ext_sram_tb.vhd
# hf-riscv_basic_standard_soc_tb.vhd

# hf-riscv_tb.vhd
# hf-riscv_tb_xtea.vhd

# hf-riscv_sram_ctl_tb.vhd