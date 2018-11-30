NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G
all: main.exe
main.exe: kernel.cu
	$(NVCC) $(NVCC_FLAGS) $^ -o $@
