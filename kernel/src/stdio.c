/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <stdio.h>
#include <stdint.h>

typedef enum vrn_fb_int_to_str_flags_e
{
    VRN_FB_ITS_FLAG_NONE = 0,
    VRN_FB_ITS_FLAG_SMALL = 1,
} vrn_fb_int_to_str_flags_t;

static int int_to_string(int input, char *s, int base, vrn_fb_int_to_str_flags_t flags);

int vsprintf(char *s, const char *format, va_list arg)
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