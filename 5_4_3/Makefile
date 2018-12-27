NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G
FLAGS = -Wno-deprecated-gpu-targets

all: main_1.exe main_2.exe main_3.exe main_4.exe main_3_5x5.exe

main_1.exe: main_1.o kernel_1.o
	$(NVCC) $(FLAGS) $^ -o $@
	
main_1.o: main_1.cpp kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@
	
kernel_1.o: kernel_1.cu kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@

main_2.exe: main_2.o kernel_2.o
	$(NVCC) $(FLAGS) $^ -o $@
main_2.o: main_2.cpp kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@
kernel_2.o: kernel_2.cu kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@

main_3.exe: main_3.o kernel_3.o
	$(NVCC) $(FLAGS) $^ -o $@
main_3.o: main_3.cpp kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@
kernel_3.o: kernel_3.cu kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@
	
main_4.exe: main_4.o kernel_4.o
	$(NVCC) $(FLAGS) $^ -o $@
main_4.o: main_4.cpp kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@
kernel_4.o: kernel_4.cu kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@
	
main_3_5x5.exe: main_3_5x5.o kernel_3_5x5.o
	$(NVCC) $(FLAGS) $^ -o $@
main_3_5x5.o: main_3_5x5.cpp kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@
kernel_3_5x5.o: kernel_3_5x5.cu kernel.h
	$(NVCC) $(NVCC_FLAGS) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o *.exe out_1.bmp out_2.bmp out_3.bmp out_4.bmp out_3_5x5.bmp