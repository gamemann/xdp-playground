This repository contains smaller XDP/(e)BPF programs I've made for testing and helping others. With that said, it also utilizes multiple loaders.

This is a work-in-progress and will work on it over time.

## Prerequisite
### XDP-Tools
You must install [XDP-Tools](https://github.com/xdp-project/xdp-tools). I've added two useful chains in the [`Makefile`](./Makefile) for doing so.

```bash
# Install required packages via Apt on Debian/Ubuntu.
sudo apt install -y m4 gcc-multilib lib32z1-dev libelf-dev libpcap-dev

# Build XDP-Tools and LibBPF.
make xdp-tools

# Install XDP-Tools and LibBPF (must be executed as root via sudo or as root user).
sudo make xdp-tools-install
```

### Make, Clang, Etc.
You'll also want to make sure you have `make` and `clang` installed. I typically use the following packages.

```bash
# Install packages via Debian/Ubuntu.
sudo apt install -y build-essential clang make
```

## Building
You may build all source files via the `make` command. All XDP/BPF programs are stored in the [`build/xdp`](./build/xdp/) directory after building and loaders are stored in [`build/loader`](./build/loader/).

## Loaders
### Go
This is a loader made in Go that uses [`dropbox/goebpf`](https://github.com/dropbox/goebpf) to load the BPF and XDP programs.

**NOTE** - The section name of the XDP program needs to be `xdp` in order to load.

#### Building
I recommend using `make` in the root of this repository to build this tool. The executable will be stored in the [`build/loader/`](../../../build/loader/) directory.

#### Command Line Usage
The following command line arguments are supported.

| Name | Flags | Default | Description |
| ---- | ----- | ------- | ----------- |
| Path | `-p --path` | `""` | The path to the BPF object file (XDP programs in this repository stored in [`build/xdp/`](../../../build/xdp)). |
| Function | `-f --func` | `"xdp_prog"` | The name of the XDP function (is always `xdp_prog` for programs inside of this repository) |
| Interface | `-i --interface` | `""` | The network interface name to attach the XDP program to. |
| Help | `-h --help` | N/A | Prints the help menu. |

#### Running
You must run this program as root. Here are a couple of examples when executing from the root of this repository.

```bash
# Load basic pass on enp1s0 interface.
sudo ./build/loader/loader_go -p ./build/xdp/xdp_basic_pass.o -i enp1s0

# Load basic printk on enp1s0 interface.
sudo ./build/loader/loader_go -p ./build/xdp/xdp_basic_printk.o -i enp1s0
```

### Rust
*To Do...*

## Credits
* [Christian Deacon](https://github.com/gamemann)