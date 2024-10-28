package main

import (
	"flag"
	"fmt"
	"os"
	"os/signal"
	"syscall"

	"github.com/gamemann/xdp-playground/src/loader/go/xdp"
)

func main() {
	// Parse command line.
	var path string
	var funcName string
	var iface string

	flag.StringVar(&path, "p", "", "Path to the BPF object file.")
	flag.StringVar(&path, "path", "", "Path to the BPF object file.")

	flag.StringVar(&funcName, "s", "xdp_prog", "The XDP program's function name.")
	flag.StringVar(&funcName, "sec", "xdp_prog", "The XDP program's function name.")

	flag.StringVar(&iface, "i", "", "The network interface name to attach to.")
	flag.StringVar(&iface, "interface", "", "The network interface name to attach to.")

	flag.Parse()

	if len(path) < 1 {
		fmt.Println("Path file is empty. Please use -p or --path.")

		os.Exit(1)
	}

	if len(iface) < 1 {
		fmt.Println("Interface name is empty. Please use -i or --interface.")

		os.Exit(1)
	}

	// Load BPF object.
	bpf, err := xdp.LoadObjFile(path)

	if err != nil {
		fmt.Println("Failed to load BPF object file.")
		fmt.Println(err)

		os.Exit(1)
	}

	// Load and attach XDP program.
	prog, err := xdp.LoadXdpProgram(bpf, funcName, iface)

	if err != nil {
		fmt.Println("Failed to load and attach XDP program.")
		fmt.Println(err)

		os.Exit(1)
	}

	fmt.Println("XDP program loaded...")

	// Make a signal.
	sigc := make(chan os.Signal, 1)
	signal.Notify(sigc, syscall.SIGINT, syscall.SIGTERM)

	<-sigc

	fmt.Println("Unloading XDP program...")

	err = xdp.UnloadXdpProgram(prog)

	if err != nil {
		fmt.Println("Failed to unload XDP program.")
		fmt.Println(err)

		os.Exit(1)
	}

	os.Exit(0)
}
