NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G
#INC = -I /usr/local/cuda/samples/common/inc

all: main.exe

main.exe: main.o kernel.o
	$(NVCC) $^ -o $@
	
main.o: main.cpp kernel.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@
	
kernel.o: kernel.cu kernel.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@
	
clean:
	rm -f *.o *.exe *.csv