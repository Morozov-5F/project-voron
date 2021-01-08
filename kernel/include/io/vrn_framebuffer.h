/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

typedef enum vrn_fb_colour_e
{
    VRN_FB_COLOUR_BLACK = (unsigned char)0,
    VRN_FB_COLOUR_BLUE = (unsigned char)1,
    VRN_FB_COLOUR_GREEN = (unsigned char)2,
    VRN_FB_COLOUR_CYAN = (unsigned char)3,
    VRN_FB_COLOUR_RED = (unsigned char)4,
    VRN_FB_COLOUR_MAGENTA = (unsigned char)5,
    VRN_FB_COLOUR_BROWN = (unsigned char)6,
    VRN_FB_COLOUR_LGRAY = (unsigned char)7,
    VRN_FB_COLOUR_DGRAY = (unsigned char)8,
    VRN_FB_COLOUR_LBLUE = (unsigned char)9,
    VRN_FB_COLOUR_LGREEN = (unsigned char)10,
    VRN_FB_COLOUR_LCYAN = (unsigned char)11,
    VRN_FB_COLOUR_LRED = (unsigned char)12,
    VRN_FB_COLOUR_LMAGENTA = (unsigned char)13,
    VRN_FB_COLOUR_LBROWN = (unsigned char)14,
    VRN_FB_COLOUR_WHITE = (unsigned char)15,
} vrn_fb_colour_t;

extern void vrn_outb(unsigned short port, unsigned char data);

void vrn_fb_putc(char c, vrn_fb_colour_t fg, vrn_fb_colour_t bg);

void vrn_fb_puts(const char *str, vrn_fb_colour_t fg, vrn_fb_colour_t bg);

void vrn_fb_move_cursor(unsigned short position);

void vrn_fb_clear(void);
