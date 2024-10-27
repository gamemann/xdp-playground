#include <aio_bpf.h>

SEC("xdp_prog")
int xdp_basic_pass(struct xdp_md *ctx) {
    return XDP_PASS;
}