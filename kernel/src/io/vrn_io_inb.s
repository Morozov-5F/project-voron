; Copyright (c) 2021, Evgeniy Morozov
; All rights reserved.
; This source code is licensed under the BSD-style license found in the
; LICENSE file in the root directory of this source tree.

global vrn_io_inb

; vrn_io_inb - read a byte from an I/O port
; stack: [esp + 4] the I/O port
;        [esp    ] return address
vrn_io_inb:
    mov dx, [esp + 4]
    in al, dx
    ret