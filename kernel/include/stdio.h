/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef VORON_STDIO_H
#define VORON_STDIO_H

#include <stdarg.h>

int vsprintf(char *s, const char *format, va_list arg);

#endif //VORON_STDIO_H
