CC = clang

SRC_DIR = src
BUILD_DIR = build
MODULES_DIR = modules

BUILD_LOADER_DIR = $(BUILD_DIR)/loader
BUILD_XDP_DIR = $(BUILD_DIR)/xdp

SRC_XDP_DIR = $(SRC_DIR)/xdp
SRC_LOADER_DIR = $(SRC_DIR)/loader

MODULES_XDP_TOOLS_DIR = $(MODULES_DIR)/xdp-tools
MODULES_LIBBPF = $(MODULES_XDP_TOOLS_DIR)/lib/libbpf

SRC_XDP_HEADERS_DIR = $(SRC_XDP_DIR)/headers

XDP_INCS = -I $(MODULES_LIBBPF)/src -I $(SRC_XDP_HEADERS_DIR)
XDP_FLAGS = -O2 -target bpf -c

all: xdp loader

tools: xdp-tools xdp-tools-install
loader: loader_go loader_rust
xdp: xdp_basic xdp_removepl

xdp-tools:
	cd $(MODULES_XDP_TOOLS_DIR) && ./configure
	$(MAKE) -C $(MODULES_XDP_TOOLS_DIR)

xdp-tools-install:
	$(MAKE) -C $(MODULES_XDP_TOOLS_DIR) install
	$(MAKE) -C $(MODULES_LIBBPF)/src install

loader_go:
	go build -o $(BUILD_LOADER_DIR)/loader_go ./$(SRC_LOADER_DIR)/go

loader_rust:

xdp_basic:
	clang $(XDP_INCS) $(XDP_FLAGS) -o $(BUILD_XDP_DIR)/xdp_basic_pass.o $(SRC_XDP_DIR)/basic/xdp_basic_pass.c
	clang $(XDP_INCS) $(XDP_FLAGS) -o $(BUILD_XDP_DIR)/xdp_basic_drop.o $(SRC_XDP_DIR)/basic/xdp_basic_drop.c
	clang $(XDP_INCS) $(XDP_FLAGS) -o $(BUILD_XDP_DIR)/xdp_basic_printk.o $(SRC_XDP_DIR)/basic/xdp_basic_printk.c

xdp_removepl:
	clang $(XDP_INCS) $(XDP_FLAGS) -o $(BUILD_XDP_DIR)/xdp_removepl_ex1.o $(SRC_XDP_DIR)/removepl/xdp_removepl_ex1.c