#include "kernel.h"
#define TX 32
#define TY 32

__device__
unsigned char clip(int n){ return n > 255 ? 255 : (n < 0 ? 0 : n);}

__global__
void distanceKernel(uchar4 *d_out, int w, int h, float AtoBsalce, int2 Bpos){
	const int c = blockIdx.x*blockDim.x + threadIdx.x;
	const int r = blockIdx.y*blockDim.y + threadIdx.y;
	if((c>=w) || (r>=h)) return;
	const int i = c + r*w;
	const int Bdist = sqrtf((c - Bpos.x)*(c - Bpos.x) + (r - Bpos.y)*(r - Bpos.y));
	const unsigned char intensity = clip(255 - Bdist);

	d_out[i].x = intensity*AtoBsalce;
	d_out[i].y = 0;
	d_out[i].z = intensity*(1-AtoBsalce);
	d_out[i].w = 255;
}

void kernelLauncher(uchar4 *d_out, int w, int h, int2 Apos, int2 Bpos){
	const dim3 blockSize(TX, TY);
	const dim3 gridSize = dim3((w + TX -1)/TX, (h + TY - 1)/TY);
	const int AtoBdist = sqrtf((Apos.x - Bpos.x)*(Apos.x - Bpos.x) + (Apos.y - Bpos.y)*(Apos.y - Bpos.y));
	float AtoBscaleTmp = AtoBdist/sqrtf(w*w+h*h);
	float AtoBsalce = AtoBscaleTmp > 1 ? 1 : AtoBscaleTmp;
	distanceKernel<<<gridSize, blockSize>>>(d_out, w, h, AtoBsalce, Bpos);
}
