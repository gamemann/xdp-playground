#include <aio_bpf.h>
#include <checksum.h>

#define TARGET_PORT 1600

#define MAX_PAYLOAD 400

#define PL_REM_POS 10
#define PL_REM_SIZE 4

SEC("xdp")
int xdp_prog(struct xdp_md *ctx) {
    void *data = (void *)(long)ctx->data;
    void *data_end = (void *)(long)ctx->data_end;

    struct ethhdr *eth = data;

    if (eth + 1 > (struct ethhdr *)data_end)
        return XDP_DROP;

    if (eth->h_proto != htons(ETH_P_IP))
        return XDP_PASS;

    struct iphdr *iph = data + sizeof(struct ethhdr);

    if (iph + 1 > (struct iphdr *)data_end)
        return XDP_DROP;

    if (iph->protocol != IPPROTO_UDP)
        return XDP_PASS;

    struct udphdr *udph = data + sizeof(struct ethhdr) + (iph->ihl * 4);

    if (udph + 1 > (struct udphdr *)data_end)
        return XDP_DROP;

    if (udph->dest != htons(TARGET_PORT))
        return XDP_PASS;

    __u8 *pl = data + sizeof(struct ethhdr) + (iph->ihl * 4) + sizeof(struct udphdr);

    int pl_len = (data_end - data) - sizeof(struct ethhdr) - (iph->ihl * 4) - sizeof(struct udphdr);

    if (pl_len < PL_REM_POS + PL_REM_SIZE)
        return XDP_PASS;

    int new_pl_len = pl_len - PL_REM_SIZE;

    // Retrieve new payload (with bytes removed).
    int i;
    __u8 new_payload[MAX_PAYLOAD];

    for (i = 0; i < MAX_PAYLOAD; i++) {
        if (pl + i + 1 > (__u8 *)data_end || i >= pl_len)
            break;

        // Ignore bytes we're removing.
        if (i >= PL_REM_POS && i <= PL_REM_POS + PL_REM_SIZE)
            continue;

        new_payload[i] = pl[i];
    }

    // Set new payload.
    for (i = 0; i < MAX_PAYLOAD; i++) {
        if (pl + i + 1 > (__u8 *)data_end || i >= new_pl_len)
            break;

        pl[i] = new_payload[i];
    }

    // Set new UDP header length.
    udph->len = htons(ntohs(udph->len) - PL_REM_SIZE);

    // Set new IP header length.
    iph->tot_len = htons(ntohs(iph->tot_len) - PL_REM_SIZE);

    // Recalculate checksums.
    udph->check = 0;
    udph->check = calcUdpCsum(iph, udph, data_end);

    update_iph_checksum(iph);

    // Remove bytes from end of packet.
    if (bpf_xdp_adjust_tail(ctx, (int)-PL_REM_SIZE) != 0)
        return XDP_ABORTED;

    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";