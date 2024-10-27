#include <aio_bpf.h>

SEC("xdp")
int xdp_prog(struct xdp_md *ctx) {
    bpf_printk("Packet received.\n");

    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";