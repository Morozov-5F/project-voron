 /**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
ENTRY(loader)

SECTIONS = {
    . = 0x00100000,

    .text ALIGN (0x1000):
    {
        *(.text)
    }

    .rodata ALIGN (0x1000):
    {
        *(.rodata*)
    }

    .data ALIGN (0x1000):
    {
        *(.data)
    }

    .bss ALIGN (0x1000):
    {
        *(COMMON)
        *(.bss)
    }
}