#include "aux_functions.h"
#define N 64
int main(){
	float in[N] = {0.0f};
	float out[N] = {0.0f};

	const float ref = 0.5f;

	for(int i=0;i<N;++i){
		in[i] = scale(i, N);
	}
	
	distanceArray(out, in, ref, N);

	return 0;
}
