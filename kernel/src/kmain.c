/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <io/vrn_framebuffer.h>

int kmain(void)
{
    vrn_fb_write_string("Hello, world", 0, 7);

    while (1)
    {

    }
    return 0;
}