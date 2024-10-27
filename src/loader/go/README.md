This is a loader made in Go that uses [`dropbox/goebpf`](https://github.com/dropbox/goebpf) to load the BPF and XDP programs.

**NOTE** - The section name of the XDP program needs to be `xdp` in order to load.

## Building
I recommend using `make` in the root of this repository to build this tool. The executable will be stored in the [`build/loader/`](../../../build/loader/) directory.

## Command Line Usage
The following command line arguments are supported.

| Name | Flags | Default | Description |
| ---- | ----- | ------- | ----------- |
| Path | `-p --path` | `""` | The path to the BPF object file (XDP programs in this repository stored in [`build/xdp/`](../../../build/xdp)). |
| Function | `-f --func` | `"xdp_prog"` | The name of the XDP function (is always `xdp_prog` for programs inside of this repository) |
| Interface | `-i --interface` | `""` | The network interface name to attach the XDP program to. |
| Help | `-h --help` | N/A | Prints the help menu. |

## Running
You must run this program as root. Here are a couple of examples when executing from the root of this repository.

```bash
# Load basic pass on enp1s0 interface.
sudo ./build/loader/loader_go -p ./build/xdp/xdp_basic_pass.o -i enp1s0

# Load basic printk on enp1s0 interface.
sudo ./build/loader/loader_go -p ./build/xdp/xdp_basic_printk.o -i enp1s0
```