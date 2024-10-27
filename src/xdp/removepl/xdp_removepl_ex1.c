#include <aio_bpf.h>

SEC("xdp_prog")
int xdp_removepl_ex1(struct xdp_md *ctx) {
    /* To Do... */
    return XDP_PASS;
}