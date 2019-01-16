NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G

all: kernel.exe

kernel.exe: kernel.cu
	$(NVCC) $(NVCC_FLAGS) $^ -o $@

clean:
	rm -f *.exe	
