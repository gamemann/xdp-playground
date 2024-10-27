#include <aio_bpf.h>

SEC("xdp")
int xdp_prog(struct xdp_md *ctx) {
    /* To Do... */
    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";