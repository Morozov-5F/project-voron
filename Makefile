# Copyright (c) 2021, Evgeniy Morozov
# All rights reserved.
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
.PHONY: kernel clean fullclean iso iso_dir kernel/kernel.elf

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

emulate:
	@bochs -f bochsrc.txt -rc bochsinit.txt -q

clean:
	@$(MAKE) -C kernel clean

fullclean: clean
	@$(MAKE) -C kernel fullclean
	@echo "Cleaning ISO"
	@$(RM) -r $(ISODIR)
	@$(RM) os.iso
	@$(RM) bochslog.txt
