/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <stdarg.h>
#include <io/vrn_framebuffer.h>
#include <stdint.h>

#define VRN_FB_MAX_ROWS    ((char)80)
#define VRN_FB_MAX_COLUMNS ((char)25)

typedef enum vrn_fb_int_to_str_flags_e
{
    VRN_FB_ITS_FLAG_NONE = 0,
    VRN_FB_ITS_FLAG_SMALL = 1,
} vrn_fb_int_to_str_flags_t;

static int vsprintf(char *s, const char *format, va_list arg);
static int int_to_string(int input, char *s, int base, vrn_fb_int_to_str_flags_t flags);

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
    vrn_outb(0x3D4, 14);
    vrn_outb(0x3D5, ((position >> 8) & 0xFF));
    vrn_outb(0x3D4, 15);
    vrn_outb(0x3D5, position & 0xFF);
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

static int vsprintf(char *s, const char *format, va_list arg)
{
    int k = 0;
    int escape_detected = 0;
    for (int i = 0; format[i] != '\0'; ++i)
    {
        if (format[i] == '%')
        {
            escape_detected = 1;
            continue;
        }

        if (escape_detected)
        {
            switch (format[i])
            {
                case '%':
                    s[k++] = '%';
                    break;
                case 'c':
                    s[k++] = va_arg(arg, int);
                    break;
                case 's':
                {
                    char *str_arg = va_arg(arg, char *);
                    for (int j = 0; str_arg[j] != '\0'; ++j)
                    {
                        s[k++] = str_arg[j];
                    }
                    break;
                }
                case 'd':
                case 'i':
                    k += int_to_string(va_arg(arg, int), s + k, 10, VRN_FB_ITS_FLAG_NONE);
                    break;
                case 'o':
                    k += int_to_string(va_arg(arg, int), s + k, 8, VRN_FB_ITS_FLAG_NONE);
                    break;
                case 'x':
                    k += int_to_string(va_arg(arg, int), s + k, 16, VRN_FB_ITS_FLAG_SMALL);
                    break;
                case 'X':
                    k += int_to_string(va_arg(arg, int), s + k, 16, VRN_FB_ITS_FLAG_NONE);
                    break;
                case 'p':
                    k += int_to_string(va_arg(arg, intptr_t), s + k, 16, VRN_FB_ITS_FLAG_NONE);
                    break;
                default:
                    break;
            }

            escape_detected = 0;
            continue;
        }

        s[k++] = format[i];
    }
    s[k] = '\0';
    return k;
}

static int int_to_string(int input, char *s, int base, vrn_fb_int_to_str_flags_t flags)
{
    int sign = 0;
    int const mask = input >> (sizeof(int) * 8 - 1);
    unsigned number = (unsigned)input;
    if (input < 0 && base == 10)
    {
        sign = 1;
        number = (input + mask) ^ mask;
    }

    if (number == 0)
    {
        s[0] = '0';
        return 1;
    }

    int i = 0;
    char *digits = "0123456789ABCDEF";
    if (flags & VRN_FB_ITS_FLAG_SMALL)
    {
        digits = "0123456789abcdef";
    }

    char tmp[32];
    int idx = 0;
    while (number != 0)
    {
        tmp[idx++] = digits[number % base];
        number /= base;
    }
    tmp[idx] = 0;
    if (sign)
    {
        s[i++] = '-';
    }
    while (idx-- > 0)
    {
        s[i++] = tmp[idx];
    }

    return i;
}