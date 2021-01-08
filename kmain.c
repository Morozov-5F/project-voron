/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

void fb_out(const char *str, char fg, char bg)
{
    char *fb = (char *)0xB8000;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        fb[2 * i] = str[i];
        fb[2 * i + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
    }
}

int kmain(void)
{
    fb_out("Hello, world", 0, 7);

    while (1)
    {

    }
    return 0;
}