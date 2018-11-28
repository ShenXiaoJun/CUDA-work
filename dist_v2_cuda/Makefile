NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G

all: main.exe main_d_1.exe main_d_2.exe

main.exe: main.o kernel.o
	$(NVCC) $^ -o $@

main.o: main.cpp kernel.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@

kernel.o: kernel.cu kernel.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@



main_d_1.exe: main_d_1.o kernel_d_1.o
	$(NVCC) $^ -o $@

main_d_1.o: main_d_1.cpp kernel_d_1.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@

kernel_d_1.o: kernel_d_1.cu kernel_d_1.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@


main_d_2.exe: main_d_2.o kernel_d_2.o
	$(NVCC) $^ -o $@

main_d_2.o: main_d_2.cpp kernel_d_2.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@

kernel_d_2.o: kernel_d_2.cu kernel_d_2.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@
