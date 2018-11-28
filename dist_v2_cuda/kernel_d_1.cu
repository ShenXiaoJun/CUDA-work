#include "kernel.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
	float *d_in = 0;
	float *d_out = 0;

	cudaMalloc(&d_in, len*sizeof(float));
	cudaMalloc(&d_out, len*sizeof(float));
	
	clock_t copyBegin = clock();
	for(int i=0;i < M;++i)
		cudaMemcpy(d_in, in, len*sizeof(float), cudaMemcpyHostToDevice);
	clock_t copyEnd = clock();
	
	clock_t kernelBegin = clock();
	distanceKernel<<<len/TPB, TPB>>>(d_out, d_in, ref);
	clock_t kernelEnd = clock();

	cudaMemcpy(out, d_out, len*sizeof(float), cudaMemcpyDeviceToHost);
	
	double copyTime = ((double)(copyEnd - copyBegin)) / CLOCKS_PER_SEC;
	double kernelTime = ((double)(kernelEnd - kernelBegin)) / CLOCKS_PER_SEC;
	printf("copy time:%f (ms)\nkernel time:%f (ms)\n",copyTime*1000,kernelTime*1000);

	cudaFree(d_in);
	cudaFree(d_out);
}
