#include "kernel.h"
#include <stdio.h>
#define TPB 12
// 未完成
__global__
void sort_even(int *d_b, int n, int *d_sort_even_run){
	const int idx = threadIdx.x + blockDim.x * blockIdx.x;
	if(idx >= n) return;
	const int s_idx = threadIdx.x;

	__shared__ int s_prod[TPB];
	if(abs(d_b[idx]) < abs(d_b[idx+1])){
		int tmp = d_b[idx];
		d_b[idx] = d_b[idx+1];
		d_b[idx+1] = tmp;
		s_prod[s_idx] = 1;
	} else s_prod[s_idx] = 0;
	__syncthreads();
	//每个线程块的线程0做管理
	if(s_idx == 0){
		int blockSum = 0;
		for(int j = 0; j < blockDim.x && j < (n - blockDim.x * blockIdx.x); j+=2){
			blockSum += s_prod[j];
			printf("%s,j:%d\n",__func__,j);
		}
		atomicAdd(d_sort_even_run, blockSum);
		printf("%s,Block_%d, blockSum = %d, d_sort_even_run = %d\n", __func__, blockIdx.x, blockSum, *d_sort_even_run);
	}
}

__global__
void sort_odd(int *d_b, int n, int *d_sort_odd_run){
	const int idx = threadIdx.x + blockDim.x * blockIdx.x;
	if(idx + 1 >= n) return;
	const int s_idx = threadIdx.x;

	__shared__ int s_prod[TPB];
	if(abs(d_b[idx]) < abs(d_b[idx+1])){
		int tmp = d_b[idx];
		printf("idx=%d,d_b=%d,d_b+1=%d,start\n",idx,d_b[idx],d_b[idx+1]);
		d_b[idx] = d_b[idx+1];
		d_b[idx+1] = tmp;
		s_prod[s_idx] = 1;
		printf("idx=%d,d_b=%d,d_b+1=%d,end\n",idx,d_b[idx],d_b[idx+1]);
	} else s_prod[s_idx] = 0;
	__syncthreads();
	//每个线程块的线程0做管理
	if(s_idx == 0){
		int blockSum = 0;
		for(int j = 1; j < blockDim.x && j+1 < (n - blockDim.x * blockIdx.x); j+=2){
			blockSum += s_prod[j];
			if(0)printf("%s,j:%d\n",__func__,j);
		}
		atomicAdd(d_sort_odd_run, blockSum);
		printf("%s,Block_%d, blockSum = %d, d_sort_odd_run = %d\n", __func__, blockIdx.x, blockSum, *d_sort_odd_run);
	}
}

void dotLauncher(int *b, int n){
	int *d_b = NULL, *d_sort_odd_run = NULL, *d_sort_even_run = NULL;
	int sort_odd_run = 0, sort_even_run = 0;

	cudaMalloc(&d_b, n*sizeof(int));
	cudaMalloc(&d_sort_odd_run, sizeof(int));
	cudaMalloc(&d_sort_even_run, sizeof(int));

	cudaMemcpy(d_b, b, n*sizeof(int), cudaMemcpyHostToDevice);

	//for(int i=0; i < 2*n; i++){
	for(int i=0; 1; i++){
		cudaMemset(d_sort_even_run,0,sizeof(int));
		cudaMemset(d_sort_odd_run,0,sizeof(int));
		sort_even<<<(n + TPB - 1)/TPB, TPB>>>(d_b, n, d_sort_even_run);
		sort_odd<<<(n + TPB - 1)/TPB, TPB>>>(d_b, n, d_sort_odd_run);
		cudaMemcpy(&sort_even_run, d_sort_even_run, sizeof(int), cudaMemcpyDeviceToHost);
		cudaMemcpy(&sort_odd_run, d_sort_odd_run, sizeof(int), cudaMemcpyDeviceToHost);
		printf("sort_odd_run=%d, sort_even_run=%d\n",sort_odd_run ,sort_even_run);
		if(sort_odd_run + sort_even_run == 0)
			break;
	}
	cudaMemcpy(b, d_b, n*sizeof(int), cudaMemcpyDeviceToHost);

	cudaFree(d_b);
	cudaFree(d_sort_even_run);
	cudaFree(d_sort_odd_run);
}
