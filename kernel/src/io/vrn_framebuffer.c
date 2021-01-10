/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <stdarg.h>
#include <io/vrn_framebuffer.h>
#include <stdio.h>

#define VRN_FB_MAX_ROWS    ((char)80)
#define VRN_FB_MAX_COLUMNS ((char)25)

static char *gs_vrn_framebuffer = (char *)0xB8000;
static char gs_cursor_x = 0;
static char gs_cursor_y = 0;

void vrn_fb_putc(char c, vrn_fb_colour_t fg, vrn_fb_colour_t bg)
{
    char attribute = ((fg & 0x0f) << 4) | (bg & 0x0f);

    if (c == '\r')
    {
        gs_cursor_x = 0;
    }
    else if (c == '\n')
    {
        gs_cursor_x = 0;
        gs_cursor_y = (gs_cursor_y + 1) % VRN_FB_MAX_COLUMNS; // For now the framebuffer wraps up;
    }
    else if (c == '\t')
    {
        gs_cursor_x = (gs_cursor_x + 4) & ~(4 - 1);
    }
    else if (c >= ' ')
    {
        char *location = gs_vrn_framebuffer + 2 * (gs_cursor_y * VRN_FB_MAX_ROWS + gs_cursor_x);
        location[0] = c;
        location[1] = attribute;

        gs_cursor_x++;
    }

    if (gs_cursor_x >= VRN_FB_MAX_ROWS)
    {
        gs_cursor_x = 0;
        gs_cursor_y = (gs_cursor_y + 1) % VRN_FB_MAX_COLUMNS;
    }

    vrn_fb_move_cursor(gs_cursor_y * VRN_FB_MAX_ROWS + gs_cursor_x);
}

void vrn_fb_puts(const char *str, vrn_fb_colour_t fg, vrn_fb_colour_t bg)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        vrn_fb_putc(str[i], fg, bg);
    }
}

void vrn_fb_move_cursor(unsigned short position)
{
    vrn_io_outb(0x3D4, 14);
    vrn_io_outb(0x3D5, ((position >> 8) & 0xFF));
    vrn_io_outb(0x3D4, 15);
    vrn_io_outb(0x3D5, position & 0xFF);
}

void vrn_fb_clear(void)
{
    for (int i = 0; i < VRN_FB_MAX_ROWS * VRN_FB_MAX_COLUMNS; ++i)
    {
        vrn_fb_putc(' ', VRN_FB_COLOUR_BLACK, VRN_FB_COLOUR_WHITE);
    }
    gs_cursor_x = 0;
    gs_cursor_y = 0;
    vrn_fb_move_cursor(gs_cursor_y * VRN_FB_MAX_ROWS + gs_cursor_x);
}

void vrn_fb_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char str[256];

    vsprintf(str, fmt, args);

    vrn_fb_puts(str, VRN_FB_COLOUR_BLACK, VRN_FB_COLOUR_LGRAY);

    va_end(args);
}