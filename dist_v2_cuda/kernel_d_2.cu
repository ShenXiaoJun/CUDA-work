#include "kernel.h"
#include <stdlib.h>
#include <stdio.h>

#define TPB 32
#define M 100

__device__
float distance(float x1, float x2){
	return sqrt((x2-x1)*(x2-x1));
}

__global__
void distanceKernel(float *d_out, float *d_in, float ref){
	const int i = blockIdx.x*blockDim.x + threadIdx.x;
	const float x = d_in[i];
	d_out[i] = distance(x, ref);
	//printf("blockIdx:%2d,blockDim:%2d,threadIdx:%2d,i = %2d:dist from %f to %f.\n",
	//	blockIdx.x,blockDim.x,threadIdx.x, i, ref, x, d_out[i]);
}

void distanceArray(float *out, float *in, float ref, int len){
	cudaEvent_t startCpy, stopCpy;
	cudaEvent_t startKernel, stopKernel;
	cudaEventCreate(&startCpy);
	cudaEventCreate(&stopCpy);
	cudaEventCreate(&startKernel);
	cudaEventCreate(&stopKernel);

	float *d_in = 0;
	float *d_out = 0;

	cudaMalloc(&d_in, len*sizeof(float));
	cudaMalloc(&d_out, len*sizeof(float));
	
	cudaEventRecord(startCpy);
	for(int i=0;i < M;++i)
		cudaMemcpy(d_in, in, len*sizeof(float), cudaMemcpyHostToDevice);
	cudaEventRecord(stopCpy);
	
	cudaEventRecord(startKernel);
	distanceKernel<<<len/TPB, TPB>>>(d_out, d_in, ref);
	cudaEventRecord(stopKernel);

	cudaMemcpy(out, d_out, len*sizeof(float), cudaMemcpyDeviceToHost);

	cudaEventSynchronize(stopCpy);
	cudaEventSynchronize(stopKernel);
	
	float copyTime = 0;
	cudaEventElapsedTime(&copyTime,startCpy,stopCpy);
	float kernelTime = 0;
	cudaEventElapsedTime(&kernelTime,startKernel,stopKernel);
	printf("copy time:%f (ms)\nkernel time:%f (ms)\n",copyTime,kernelTime);

	cudaFree(d_in);
	cudaFree(d_out);
}
