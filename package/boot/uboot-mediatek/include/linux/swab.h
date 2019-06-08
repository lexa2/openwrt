#ifndef _LINUX_SWAB_H
#define _LINUX_SWAB_H

#include <linux/types.h>

#define ___constant_swab32(x) ((__u32)(                         \
        (((__u32)(x) & (__u32)0x000000ffUL) << 24) |            \
        (((__u32)(x) & (__u32)0x0000ff00UL) <<  8) |            \
        (((__u32)(x) & (__u32)0x00ff0000UL) >>  8) |            \
        (((__u32)(x) & (__u32)0xff000000UL) >> 24)))

static __inline__  __u32 __fswab32(__u32 val)
{
        return __builtin_bswap32(val);
}


/**
 * __swab32 - return a byteswapped 32-bit value
 * @x: value to byteswap
 */
#define __swab32(x)                             \
        (__builtin_constant_p((__u32)(x)) ?     \
        ___constant_swab32(x) :                 \
        __fswab32(x))

#endif