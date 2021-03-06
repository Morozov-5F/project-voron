/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef VRN_IO_H
#define VRN_IO_H

extern void vrn_io_outb(unsigned short port, unsigned char data);

extern unsigned char vrn_io_inb(unsigned short port);

#endif //VORON_VRN_IO_H
