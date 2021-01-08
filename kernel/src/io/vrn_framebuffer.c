/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <io/vrn_framebuffer.h>

void vrn_fb_write_string(const char *str, unsigned char fg, unsigned char bg)
{
    char *fb = (char *)0xB8000;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        fb[2 * i] = str[i];
        fb[2 * i + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
    }
}
