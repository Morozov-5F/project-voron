/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef VORON_VRN_SERIAL_H
#define VORON_VRN_SERIAL_H

#include <stddef.h>
#include "vrn_io.h"

typedef enum vrn_serial_base_e
{
    VRN_SERIAL_BASE_COM1 = 0x3F8,
    VRN_SERIAL_BASE_COM2 = 0x2F8,
    VRN_SERIAL_BASE_COM3 = 0x3E8,
    VRN_SERIAL_BASE_COM4 = 0x2E8,
} vrn_serial_base_t;

typedef enum vrn_serial_line_config_flag_e
{
    VRN_SERIAL_CF_NONE = 0x0,
    VRN_SERIAL_CF_DATA_BITS_5 = 0,
    VRN_SERIAL_CF_DATA_BITS_6 = 1,
    VRN_SERIAL_CF_DATA_BITS_7 = 2,
    VRN_SERIAL_CF_DATA_BITS_8 = 3,
    VRN_SERIAL_CF_STOP_BITS_1 = 0,
    VRN_SERIAL_CF_STOP_BITS_2 = 1 << 2,
    VRN_SERIAL_CF_PARITY_NONE = 0,
    VRN_SERIAL_CF_PARITY_ODD = 1 << 3,
    VRN_SERIAL_CF_PARITY_EVEN = 2 << 3,
    VRN_SERIAL_CF_PARITY_MARK = 5 << 3,
    VRN_SERIAL_CF_PARITY_SPACE = 7 << 3,
    VRN_SERIAL_CF_DLAB = 1 << 7,
} vrn_serial_line_config_flag_t;

typedef enum vrn_serial_fifo_config_flag_e
{
    VRN_SERIAL_FIFO_CF_NONE = 0,
    VRN_SERIAL_FIFO_CF_ENABLE_FIFO = 1,
    VRN_SERIAL_FIFO_CF_CLR_RX = 1 << 1,
    VRN_SERIAL_FIFO_CF_CLR_TX = 1 << 2,
    VRN_SERIAL_FIFO_CF_DMA = 1 << 3,
    VRN_SERIAL_FIFO_CF_16750 = 1 << 5,
    VRN_SERIAL_FIFO_CF_1_BYTE = 0,
    VRN_SERIAL_FIFO_CF_4_BYTES = 1 << 6,
    VRN_SERIAL_FIFO_CF_8_BYTES = 2 << 6,
    VRN_SERIAL_FIFO_CF_14_BYTES = 3 << 6,

    VRN_SERIAL_FIFO_CF_16750_1_BYTE = VRN_SERIAL_FIFO_CF_1_BYTE,
    VRN_SERIAL_FIFO_CF_16750_16_BYTES = VRN_SERIAL_FIFO_CF_4_BYTES,
    VRN_SERIAL_FIFO_CF_16750_32_BYTE = VRN_SERIAL_FIFO_CF_8_BYTES,
    VRN_SERIAL_FIFO_CF_16750_56_BYTES = VRN_SERIAL_FIFO_CF_14_BYTES,
} vrn_serial_fifo_config_flag_t;

typedef enum vrn_serial_modem_config_flag_e
{
    VRN_SERIAL_MODEM_CF_DTS = 1,
    VRN_SERIAL_MODEM_CF_RTS = 1 << 1,
    VRN_SERIAL_MODEM_AO1 = 1 << 2,
    VRN_SERIAL_MODEM_AO2 = 1 << 3,
    VRN_SERIAL_MODEM_LOOBPACK_MODE = 1 << 4,
    VRN_SERIAL_MODEM_AUTO_FLOW_CONTROL = 1 << 5,
} vrn_serial_modem_config_flag_t;


int vrn_serial_init(vrn_serial_base_t port, int baud, vrn_serial_line_config_flag_t line_cfg,
                    vrn_serial_fifo_config_flag_t fifo_cfg, vrn_serial_modem_config_flag_t modem_cfg);

int vrn_serial_write(vrn_serial_base_t port, unsigned char *buffer, size_t buffer_size);

int vrn_serial_printf(vrn_serial_base_t port, const char *fmt, ...);

int vrn_serial_puts(vrn_serial_base_t port, const char *str);

int vrn_serial_putc(vrn_serial_base_t port, char c);

#endif //VORON_VRN_SERIAL_H
