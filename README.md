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
*To Do...*

### Rust
*To Do...*

## Credits
* [Christian Deacon](https://github.com/gamemann)