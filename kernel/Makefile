# Copyright (c) 2021, Evgeniy Morozov
# All rights reserved.
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
.PHONY: kernel clean fullclean

AS = nasm
ASFLAGS = -f elf32

LD = ld
LDFLAGS = -T kernel.ld -melf_i386

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -I include

kernel.elf: src/loader.o src/kmain.o src/io/vrn_framebuffer.o
	@echo "Linking kernel"
	@echo "  LD $^ $@"
	@$(LD) $(LDFLAGS) $^ -o $@

kernel: kernel.elf

%.o: %.s
	@echo "  AS $< $@"
	@$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	@echo "  CC $< $@"
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@echo "Cleaning object files"
	@$(RM) *.o
	@$(RM) src/*.o

fullclean: clean
	@echo "Cleaning kernel image and ISO"
	@$(RM) kernel.elf
	@$(RM) os.iso
