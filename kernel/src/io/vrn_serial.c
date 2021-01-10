/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <io/vrn_serial.h>
#include <stdarg.h>
#include <stdio.h>

#define VRN_SERIAL_INTERNAL_CLOCK (115200)

#define VRN_SERIAL_DATA_PORT(base)          (base)
#define VRN_SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define VRN_SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define VRN_SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define VRN_SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#define IS_TX_EMPTY(base) (vrn_io_inb(VRN_SERIAL_LINE_STATUS_PORT(base)) & 0x20)

int vrn_serial_init(vrn_serial_base_t port, int baud, vrn_serial_line_config_flag_t line_cfg,
                    vrn_serial_fifo_config_flag_t fifo_cfg, vrn_serial_modem_config_flag_t modem_cfg) {

    unsigned short divisor = VRN_SERIAL_INTERNAL_CLOCK / baud;
    if (divisor == 0)
    {
        divisor = 1;
    }

    vrn_io_outb(VRN_SERIAL_LINE_COMMAND_PORT(port), VRN_SERIAL_CF_DLAB);
    vrn_io_outb(VRN_SERIAL_DATA_PORT(port), (divisor >> 8) & 0x00FF);
    vrn_io_outb(VRN_SERIAL_DATA_PORT(port), divisor & 0x00FF);
    vrn_io_outb(VRN_SERIAL_LINE_COMMAND_PORT(port), line_cfg);
    vrn_io_outb(VRN_SERIAL_FIFO_COMMAND_PORT(port), fifo_cfg);
    vrn_io_outb(VRN_SERIAL_MODEM_COMMAND_PORT(port), modem_cfg);

    return 0;
}


int vrn_serial_putc(vrn_serial_base_t port, char c)
{
    while (!IS_TX_EMPTY(port));

    vrn_io_outb(VRN_SERIAL_DATA_PORT(port), c);

    return 0;
}

int vrn_serial_write(vrn_serial_base_t port, unsigned char *buffer, size_t buffer_size)
{
    for (size_t i = 0; i < buffer_size; ++i)
    {
        vrn_serial_putc(port, (char)buffer[i]);
    }

    return buffer_size;
}

int vrn_serial_puts(vrn_serial_base_t port, const char *str)
{
    size_t i;
    for (i = 0; str[i] != '\0'; ++i)
    {
        vrn_serial_putc(port, str[i]);
    }
    return i;
}

int vrn_serial_printf(vrn_serial_base_t port, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char str[256];

    vsprintf(str, fmt, args);

    vrn_serial_puts(port, str);

    va_end(args);

    return 0;
}
