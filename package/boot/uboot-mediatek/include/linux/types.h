#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H

#include <sys/types.h>

typedef uint16_t __u16;
typedef uint32_t __u32;

#if defined(__CYGWIN__)
typedef __signed__ long long __s64;
typedef unsigned long long __u64;
#else
typedef uint64_t __u64;
#endif

typedef __u16 __le16;
typedef __u32 __le32;
typedef __u64 __le64;
typedef __u16 __be16;
typedef __u32 __be32;
typedef __u64 __be64;

typedef __u64 off64_t;

typedef __u16  __sum16;
typedef __u32  __wsum;

#endif /* _LINUX_TYPES_H */
