; Copyright (c) 2021, Evgeniy Morozov
; All rights reserved.
; This source code is licensed under the BSD-style license found in the
; LICENSE file in the root directory of this source tree.

global vrn_outb

; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
vrn_outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret