package xdp

import (
	"fmt"

	"github.com/dropbox/goebpf"
)

func LoadObjFile(path string) (goebpf.System, error) {
	bpf := goebpf.NewDefaultEbpfSystem()

	err := bpf.LoadElf(path)

	return bpf, err
}

func LoadXdpProgram(bpf goebpf.System, funcName string, iface string) (goebpf.Program, error) {
	xdp := bpf.GetProgramByName(funcName)

	if xdp == nil {
		return nil, fmt.Errorf("error loading XDP program by function name (%s)", funcName)
	}

	err := xdp.Load()

	if err != nil {
		return xdp, err
	}

	return xdp, xdp.Attach(iface)
}

func UnloadXdpProgram(prog goebpf.Program) error {
	return prog.Detach()
}
