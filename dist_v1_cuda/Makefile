NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G

main.exe: kernel.cu
	$(NVCC) $(NVCC_FLAGS) $^ -o $@
