# Copyright (c) 2021, Evgeniy Morozov
# All rights reserved.
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
.PHONY: kernel clean fullclean iso iso_dir

AS = nasm
ASFLAGS = -f elf32

LD = ld
LDFLAGS = -T kernel.ld -melf_i386

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

ISODIR=/tmp/voron-os-iso
KERNEL_FILE = kernel/kernel.elf

all: iso

$(KERNEL_FILE):
	@echo "Compiling kernel"
	@$(MAKE) -C kernel kernel

iso: $(KERNEL_FILE)
	@echo "Making ISO image"
	@$(RM) -rf $(ISODIR) && mkdir -p $(ISODIR)  
	@cp -rf boot/ $(ISODIR) && cp $(KERNEL_FILE) $(ISODIR)/boot
	@grub-mkrescue -o os.iso $(ISODIR)

clean:
	@$(MAKE) -C kernel clean

fullclean: clean
	@$(MAKE) -C kernel fullclean
	@echo "Cleaning ISO"
	@$(RM) -r $(ISODIR)
	@$(RM) os.iso
