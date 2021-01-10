/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <io/vrn_framebuffer.h>

#include <stdarg.h>

int kmain(void)
{
    vrn_fb_clear();
    
    vrn_fb_puts("Voron OS\n", VRN_FB_COLOUR_BLACK, VRN_FB_COLOUR_LGRAY);
    vrn_fb_puts("\tBoot sequence complete.\n", VRN_FB_COLOUR_BLACK, VRN_FB_COLOUR_LGREEN);
    vrn_fb_puts("\tOS does nothing so far.\n", VRN_FB_COLOUR_BLACK, VRN_FB_COLOUR_LGRAY);

    vrn_fb_printf("\tprintf test: %s, %d, %d, %x, %X\n", "OK", 123, -123, 0xDEADBEEF, 0xCAFEBABE);

    while (1)
    {

    }
    return 0;
}