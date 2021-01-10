/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <io/vrn_framebuffer.h>
#include <io/vrn_serial.h>

int kmain(void)
{
    vrn_fb_clear();
    
    vrn_fb_puts("VRN OS\n", VRN_FB_COLOUR_BLACK, VRN_FB_COLOUR_LGRAY);

    vrn_serial_init(VRN_SERIAL_BASE_COM1, 115200, VRN_SERIAL_CF_DATA_BITS_8,
                    VRN_SERIAL_FIFO_CF_14_BYTES | VRN_SERIAL_FIFO_CF_CLR_RX | VRN_SERIAL_FIFO_CF_CLR_TX | VRN_SERIAL_FIFO_CF_ENABLE_FIFO,
                    VRN_SERIAL_MODEM_CF_RTS | VRN_SERIAL_MODEM_CF_DTS);
    vrn_fb_puts("\tCOM1 initialized\n", VRN_FB_COLOUR_BLACK, VRN_FB_COLOUR_GREEN);
    vrn_fb_puts("Boot sequence complete\n", VRN_FB_COLOUR_BLACK, VRN_FB_COLOUR_LGREEN);

    vrn_serial_printf(VRN_SERIAL_BASE_COM1, "VRN OS started\n");

    while (1)
    {
    }
    return 0;
}