NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G

all: kernel_4_3.exe kernel_4_4.exe

kernel_4_3.exe: kernel_4_3.cu
	$(NVCC) $(NVCC_FLAGS) $^ -o $@

kernel_4_4.exe: kernel_4_4.cu
	$(NVCC) $(NVCC_FLAGS) $^ -o $@
	