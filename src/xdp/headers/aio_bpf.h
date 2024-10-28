#pragma once

#include <linux/bpf.h>

#include <bpf/bpf_helpers.h>
#include <xdp/xdp_helpers.h>
#include <xdp/prog_dispatcher.h>

#include <linux/if_ether.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/udp.h>

#include <linux/types.h>

#ifndef likely
    #define likely(x) __builtin_expect(!!(x), 1)
#endif

#ifndef unlikely
    #define unlikely(x) __builtin_expect(!!(x), 0)
#endif

#ifndef htons
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define htons(x) ((__be16)___constant_swab16((x)))
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define htons(x) (x)
    #endif
#endif

#ifndef ntohs
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define ntohs(x) ((__be16)___constant_swab16((x)))
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define ntohs(X) (x)
    #endif
#endif

#ifndef htonl
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define htonl(x) ((__be32)___constant_swab32((x)))
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define htonl(x) (x)
    #endif
#endif

#ifndef ntohl
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define ntohl(x) ((__be32)___constant_swab32((x)))
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define ntohl(x) (x)
    #endif
#endif

#ifndef memcpy
    #define memcpy(dest, src, n) __builtin_memcpy((dest), (src), (n))
#endif

#ifndef memset
    #define memset(dest, n, j) __builtin_memset((dest), (n), (j))
#endif

#ifndef memcmp
#define memcmp(s, d, l) __builtin_memcmp((s), (d), (l))
#endif