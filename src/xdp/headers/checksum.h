#pragma once

#include <aio_bpf.h>

#include <stdint.h>
#include <linux/ip.h>

#define MAX_UDP_SIZE 1400

static __always_inline __u16 calcUdpCsum(struct iphdr *iph, struct udphdr *udph, void *data_end) {
    __u32 csum_buffer = 0;
    __u16 *buf = (void *)udph;

    // Compute pseudo-header checksum
    csum_buffer += (__u16)iph->saddr;
    csum_buffer += (__u16)(iph->saddr >> 16);
    csum_buffer += (__u16)iph->daddr;
    csum_buffer += (__u16)(iph->daddr >> 16);
    csum_buffer += (__u16)iph->protocol << 8;
    csum_buffer += udph->len;

    // Compute checksum on udp header + payload
    for (int i = 0; i < MAX_UDP_SIZE; i += 2) {
        if ((void *)(buf + 1) > data_end)
            break;

        if ((void *)buf <= data_end) {
            csum_buffer += *buf;
            buf++;
        }
    }

    if ((void *)buf + 1 <= data_end)
        csum_buffer += *(__u8 *)buf;

    __u16 csum = (__u16)csum_buffer + (__u16)(csum_buffer >> 16);
    csum = ~csum;

    return csum;
}

static __always_inline __u16 csum_fold_helper(__u32 csum) {
    __u32 r = csum << 16 | csum >> 16;
    csum = ~csum;
    csum -= r;
    return (__u16)(csum >> 16);
}

static __always_inline __u32 csum_add(__u32 addend, __u32 csum) {
    __u32 res = csum;
    res += addend;
    return (res + (res < addend));
}

static __always_inline __u32 csum_sub(__u32 addend, __u32 csum) {
    return csum_add(csum, ~addend);
}


static __always_inline void update_iph_checksum(struct iphdr *iph) {
    __u16 *next_iph_u16 = (__u16 *)iph;
    __u32 csum = 0;
    iph->check = 0;
#pragma clang loop unroll(full)
    for (__u32 i = 0; i < sizeof(*iph) >> 1; i++) {
        csum += *next_iph_u16++;
    }

    iph->check = ~((csum & 0xffff) + (csum >> 16));
}

static __always_inline __u16 csum_diff4(__u32 from, __u32 to, __u16 csum) {
    __u32 tmp = csum_sub(from, ~((__u32)csum));

    return csum_fold_helper(csum_add(to, tmp));
}