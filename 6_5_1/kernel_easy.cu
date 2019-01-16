#include "kernel.h"
#include <stdio.h>
#define TPB 12
#define ATOMIC 1

__global__
void even_sort(int *d_b, const int n){
	int tid = threadIdx.x;//线程从0开始编号
	if(1 == (tid + 1 ) % 2)//第奇数个轮回
	{
		if(d_b[tid] > d_b[tid + 1] && tid + 1 < n){
			int tmp = d_b[tid];
			d_b[tid] = d_b[tid + 1];
			d_b[tid + 1] = tmp;
		}
	}
	__syncthreads();
}

__global__
void odd_sort(int *d_b, const int n){
	int tid = threadIdx.x;//线程从0开始编号
	if(0 == (tid + 1 ) % 2)//第奇数个轮回
	{
		if(d_b[tid] > d_b[tid + 1] && tid + 1 < n){
			int tmp = d_b[tid];
			d_b[tid] = d_b[tid + 1];
			d_b[tid + 1] = tmp;
		}
	}
}

void dotLauncher(int *b, int n){
	int *d_b = NULL;

	cudaMalloc(&d_b, n*sizeof(int));

	cudaMemcpy(d_b, b, n*sizeof(int), cudaMemcpyHostToDevice);
	for(int i = 0; i < n; ++i){
		even_sort<<<1, n, 0>>>(d_b, n);
		odd_sort<<<1, n, 0>>>(d_b, n);
	}
	cudaMemcpy(b, d_b, n*sizeof(int), cudaMemcpyDeviceToHost);

	cudaFree(d_b);
}
