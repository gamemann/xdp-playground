#include <aio_bpf.h>

SEC("xdp_prog")
int xdp_basic_printk(struct xdp_md *ctx) {
    bpf_printk("Packet received.\n");
    
    return XDP_PASS;
}