NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G
INC = -I /usr/local/cuda/samples/common/inc

all: main.exe main_d_1.exe main_d_2.exe main_d_3.exe main_d_5.exe

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



main_d_3.exe: main_d_3.o kernel_d_3.o
	$(NVCC) $^ -o $@

main_d_3.o: main_d_3.cpp kernel_d_3.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@

kernel_d_3.o: kernel_d_3.cu kernel_d_3.h
	$(NVCC) $(NVCC_FLAGS) $(INC) -c $< -o $@



main_d_5.exe: main_d_5.o kernel_d_5.o
	$(NVCC) $^ -o $@

main_d_5.o: main_d_5.cpp kernel_d_5.h
	$(NVCC) $(NVCC_FLAGS) $(INC) -c $< -o $@

kernel_d_5.o: kernel_d_5.cu kernel_d_5.h
	$(NVCC) $(NVCC_FLAGS) $(INC) -c $< -o $@
