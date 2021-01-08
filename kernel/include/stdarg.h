/**
 * Copyright (c) 2021, Evgeniy Morozov
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

typedef char * va_list;

#define __va_aligned_sizeof(TYPE) \
    (((sizeof(TYPE) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define va_start(ap, parm_n)                                \
do                                                          \
{                                                           \
    ap = ((char *)&(parm_n)) + __va_aligned_sizeof(parm_n); \
} while (0)

#define va_end(ap)      \
do                      \
{                       \
    ap = (char *)0;     \
} while (0)

#define va_arg(ap, type) \
    (ap += __va_aligned_sizeof(type), *((type *)(ap - __va_aligned_sizeof(type))))
