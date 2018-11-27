#include <stdio.h>
#define N 64
//#define N 128
//#define N 1024
//#define N 63
//#define N 65
//#define N 4096
#define TPB 32
//#define TPB 1


float scale(int i, int n){
	return ((float) i)/(n - 1);
}

__device__ 
float distance(float x1, float x2){
	return sqrt((x2-x1)*(x2-x1));
}

__global__ 
void distanceKernel(float *d_out, float *d_in, float ref){
	const int i = blockIdx.x*blockDim.x + threadIdx.x;
	float x = 0;
	//if(i>N-1)
	//	return;
	x = d_in[i];
	d_out[i] = distance(x, ref);
	if(0)
	{
		printf("blockIdx:%2d,blockDim:%2d,threadIdx:%2d, i = %2d: dist from %f to %f.\n",
			blockIdx.x,blockDim.x,threadIdx.x,i, ref, x, d_out[i]);
	}
	//if(i==4095) printf("find 4095\n");
}

int main(){
	const float ref = 0.5f;
	float *in = 0;
	float *out = 0;
	
	cudaMallocManaged(&in, N*sizeof(float));
	cudaMallocManaged(&out, N*sizeof(float));
	
	for(int i=0;i<N;++i)
		in[i]=scale(i,N);

	distanceKernel<<<(N+TPB-1)/TPB, TPB>>>(out, in, ref);
	cudaDeviceSynchronize();
	
	cudaFree(in);
	cudaFree(out);
	return 0;
}
