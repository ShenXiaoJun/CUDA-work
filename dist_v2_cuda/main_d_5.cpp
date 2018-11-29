#include "kernel_d_5.h"
#include <stdlib.h>
#include <stdio.h>
#include <cuda_runtime_api.h>
#define N 64

float scale(int i, int n){
	return ((float)i)/(n-1);
}

int main(){
	int numDevices;
	cudaGetDeviceCount(&numDevices);
	printf("NUmber if deivce:%d\n",numDevices);
	for(int i =0;i<numDevices;++i){
		printf("----------------\n");
		cudaDeviceProp cdp;
		cudaGetDeviceProperties(&cdp, i);
		printf("Device NUmber:%d\n",i);
		printf("Device name:%s\n", cdp.name);
		printf("Compute capability: %d.%d\n", cdp.major, cdp.minor);
		printf("Maximum threads/block: %d\n", cdp.maxThreadsPerBlock);
		printf("Shared memory/block: %lu bytes\n", cdp.sharedMemPerBlock);
		printf("Total global memory: %lu bytes\n", cdp.totalGlobalMem);
	}
	return 0;
}
