#include "kernel_d_3.h"
#include <stdlib.h>
#include <stdio.h>
#include <helper_cuda.h>
#define TPB 3200

__device__
float distance(float x1, float x2){
	return sqrt((x2-x1)*(x2-x1));
}

__global__
void distanceKernel(float *d_out, float *d_in, float ref){
	const int i = blockIdx.x*blockDim.x + threadIdx.x;
	const float x = d_in[i];
	d_out[i] = distance(x, ref);
	printf("blockIdx:%2d,blockDim:%2d,threadIdx:%2d,i = %2d:dist from %f to %f.\n",
		blockIdx.x,blockDim.x,threadIdx.x, i, ref, x, d_out[i]);
}

void distanceArray(float *out, float *in, float ref, int len){
	float *d_in = 0;
	float *d_out = 0;

	checkCudaErrors( cudaMalloc(&d_in, len*sizeof(float)) );
	checkCudaErrors( cudaMalloc(&d_out, len*sizeof(float)) );

	checkCudaErrors( cudaMemcpy(d_in, in, len*sizeof(float), cudaMemcpyHostToDevice) );
	
	distanceKernel<<<len/TPB, TPB>>>(d_out, d_in, ref);
	checkCudaErrors( cudaPeekAtLastError() );
	checkCudaErrors( cudaDeviceSynchronize() );

	checkCudaErrors( cudaMemcpy(out, d_out, len*sizeof(float), cudaMemcpyDeviceToHost) );
	
	checkCudaErrors( cudaFree(d_in) );
	checkCudaErrors( cudaFree(d_out) );
}
