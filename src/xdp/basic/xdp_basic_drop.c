#include <aio_bpf.h>

SEC("xdp_prog")
int xdp_basic_drop(struct xdp_md *ctx) {
    return XDP_DROP;
}