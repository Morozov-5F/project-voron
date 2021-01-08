# Copyright (c) 2021, Evgeniy Morozov
# All rights reserved.
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
PHONY: kernel clean fullclean iso iso_dir

AS = nasm
ASFLAGS = -f elf32

LD = ld
LDFLAGS = -T kernel.ld -melf_i386

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

ISODIR=/tmp/voron-os-iso

kernel.elf: loader.o kmain.o
	@echo "Linking kernel"
	@echo "  LD $^ $@"
	@$(LD) $(LDFLAGS) $^ -o $@

kernel: kernel.elf

iso: kernel
	@echo "Making ISO image"
	@$(RM) -rf $(ISODIR) && mkdir -p $(ISODIR)  
	@cp -rf boot/ $(ISODIR) && cp kernel.elf $(ISODIR)/boot
	@grub-mkrescue -o os.iso $(ISODIR)

%.o: %.s
	@echo "  AS $< $@"
	@$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	@echo "  CC $< $@"
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@echo "Cleaning object files"
	@$(RM) *.o

fullclean: clean
	@echo "Cleaning kernel image and ISO"
	@$(RM) kernel.elf
	@$(RM) os.iso
