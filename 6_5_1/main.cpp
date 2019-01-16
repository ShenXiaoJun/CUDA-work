#include "kernel.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 15

int main(){
//	int a[] = {0,-3,2,-1,4,-5,6,-9,8,-7};
	int *a = (int *)malloc(N*sizeof(int));
	int *b = (int *)malloc(N*sizeof(int));

	for(int i = 0; i < N; ++i){
		//a[i] = rand()%201-100;
		a[i] = rand()%(2*N+1) - N;
		b[i] = a[i];
	}

	printf("a = [");
	for(int a_idx =0; a_idx < N; ++a_idx)
		if(1)printf("%4d",a[a_idx]);
	printf("]\n");

	struct timeval cpuBegin, cpuEnd;
	gettimeofday(&cpuBegin, NULL);
	for(int i = 0; i < N-1; ++i){
		for(int j = 0; j < N-i-1; ++j){
			if(abs(a[j]) < abs(a[j+1])){
				int tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
	gettimeofday(&cpuEnd, NULL);
	long long cpuTime = (cpuEnd.tv_sec - cpuBegin.tv_sec) * 1000000 + (cpuEnd.tv_usec - cpuBegin.tv_usec);

	printf("CPU max =%4d, cpuTime = %lld us, result = [", a[0], cpuTime);
	for(int a_idx =0; a_idx < N; ++a_idx)
		if(1)printf("%4d",a[a_idx]);
	printf("]\n");


	struct timeval gpuBegin, gpuEnd;
	gettimeofday(&gpuBegin, NULL);
	dotLauncher(b, N);
	gettimeofday(&gpuEnd, NULL);
	long long gpuTime = (gpuEnd.tv_sec - gpuBegin.tv_sec) * 1000000 + (gpuEnd.tv_usec - gpuBegin.tv_usec);

	printf("GPU max =%4d, gpuTime = %lld us, result = [", b[0], gpuTime);
	for(int b_idx = 0; b_idx < N; ++b_idx)
		if(1)printf("%4d",b[b_idx]);
	printf("]\n");

	free(a);
	free(b);
	return 0;
}
