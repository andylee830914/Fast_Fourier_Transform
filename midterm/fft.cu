#include <stdio.h>
#include <cuda.h>

int fft(double *x_r, double *x_i, double *y_r, double *y_i, int N);


int main()
{
	
	
	
	
	return 0;
}


int fft(double *x_r, double *x_i, double *y_r, double *y_i, int N){
	int n,p, m=0;
	int N0,M0;
	int order[100];
	
	//termination conditions
	if(N==1){
		
		y_r[0] = x_r[0];
		y_i[0] = x_i[0];
		
		return 0;
	}
	
	
	
	
	for(n=0;n<N;++n)
	{
		y_r[n] = x_r[n];
		y_i[n] = x_i[n];
	}
	
	N0=N;
	p=1;
	while (N0>1) {
		if ((N0%2)==0) {
			p=2;
		}else if ((N0%3)==0){
			p=3;
		}else if ((N0%5)==0){
			p=5;
		}else{
			p=1;
		}
		M0=0;
		while (M0<N) {
			
			groupn(y_r+M0, y_i+M0, N0, p);
			M0+=N0;
		}
		order[m]=p;
		m++;
		N0/=p;
	}
	
	
	
	while (N0<N) {
		m--;
		butterfly(y_r, y_i, N, order[m],N0);
		
		
		N0*=order[m];
	}
	
	
	return 0;
}
