#main.exe: main.cpp
#	nvcc -g -G main.cpp -o main.exe

NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -g -G

main.exe: main.cpp
	$(NVCC) $(NVCC_FLAGS) $< -o $@
