#main.exe: main.cpp
#	nvcc -g -G main.cpp -o main.exe

NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G

all: main.exe main_2.exe

main.exe: main.o aux_functions.o
	$(NVCC) $^ -o $@

main_2.exe: main_2.o aux_functions.o
	$(NVCC) $^ -o $@

main.o: main.cpp aux_functions.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@

main_2.o: main_2.cpp aux_functions.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@

aux_functions.o: aux_functions.cpp aux_functions.h
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@

