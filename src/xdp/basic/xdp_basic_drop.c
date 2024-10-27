#include <aio_bpf.h>

SEC("xdp")
int xdp_prog(struct xdp_md *ctx) {
    return XDP_DROP;
}

char _license[] SEC("license") = "GPL";