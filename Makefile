# Copyright (c) 2021, Evgeniy Morozov
# All rights reserved.
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
PHONY: kernel clean fullclean iso iso_dir

AS = nasm
ASFLAGS = -f elf32
LD = ld

ISODIR=/tmp/voron-os-iso

# Compile assembly files
%.o: %.s
	@echo "  AS $< $@"
	@$(AS) -f elf32 $<

kernel.elf: loader.o
	@echo "Linking kernel"
	@echo "  LD $< $@"
	@$(LD) -T kernel.ld -melf_i386 $< -o $@

kernel: kernel.elf

iso: kernel
	@echo "Making ISO image"
	@$(RM) -rf $(ISODIR) && mkdir -p $(ISODIR)  
	@cp -rf boot/ $(ISODIR) && cp kernel.elf $(ISODIR)/boot
	@grub-mkrescue -o os.iso $(ISODIR)

clean:
	@echo "Cleaning object files"
	@$(RM) *.o

fullclean: clean
	@echo "Cleaning kernel image and ISO"
	@$(RM) kernel.elf
	@$(RM) os.iso
