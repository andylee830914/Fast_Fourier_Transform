//
//  fft.c
//  midterm
//
//  Created by Lee Yu Hsun on 2015/5/4.
//  Copyright (c) 2015年 Yu Hsun Lee. All rights reserved.
//

#include "fft.h"
int fft(double *x_r, double *x_i, double *y_r, double *y_i, int N){
	int c;
	double *u_r, *u_i, *v_r, *v_i ,theta = 2*M_PI/N;
	double w_r,w_i,w2_r,w2_i;
	int n,k,p;
	u_r= (double *) malloc(N*sizeof(double));
	u_i= (double *) malloc(N*sizeof(double));
	v_r= (double *) malloc(N*sizeof(double));
	v_i= (double *) malloc(N*sizeof(double));

	//termination conditions
	if(N==1){
		
		y_r[0] = x_r[0];
		y_i[0] = x_i[0];
		
		return 0;
	}
	
	
	//case of fft =>2 ,3 ,or 5
	if ((N%2)==0) {
		c=2;
	}else if ((N%3)==0){
		c=3;
	}
	switch( c ){
			
		case 2:

			for(n=0;n<N/2;n++)
			{
				u_r[n] = x_r[2*n];
				u_i[n] = x_i[2*n];
				u_r[n+N/2] = x_r[2*n+1];
				u_i[n+N/2] = x_i[2*n+1];
			}
			fft(u_r,u_i,v_r,v_i,N/2);
			fft(u_r+N/2,u_i+N/2,v_r+N/2,v_i+N/2,N/2);
			for(k=0;k<N/2;++k)
			{
				w_r = cos(-k*theta);
				w_i = sin(-k*theta);
				y_r[k]		= v_r[k] +	w_r*v_r[k+N/2] - w_i*v_i[k+N/2];
				y_i[k]		= v_i[k] +	w_r*v_i[k+N/2] + w_i*v_r[k+N/2];
				y_r[k+N/2]	= v_r[k] - (w_r*v_r[k+N/2] - w_i*v_i[k+N/2]);
				y_i[k+N/2]	= v_i[k] - (w_r*v_i[k+N/2] + w_i*v_r[k+N/2]);
			}
			
			break;
		case 3:
			
			for(n=0;n<N/3;n++)
			{
				u_r[n] = x_r[3*n];
				u_i[n] = x_i[3*n];
				u_r[n+N/3] = x_r[3*n+1];
				u_i[n+N/3] = x_i[3*n+1];
				u_r[n+2*N/3] = x_r[3*n+2];
				u_i[n+2*N/3] = x_i[3*n+2];
			}
			//
			fft(u_r,u_i,v_r,v_i,N/3);
			fft(u_r+N/3,u_i+N/3,v_r+N/3,v_i+N/3,N/3);
			fft(u_r+2*N/3,u_i+2*N/3,v_r+2*N/3,v_i+2*N/3,N/3);
			//printf("N=%d, %f,u_r[k+N/3] = %f, u_i[k+N/3] = %f\n", N,v_r[0], v_r[1],v_r[2]);
			for(k=0;k<N;++k)
			{
				w_r = cos(-k*theta);
				w_i = sin(-k*theta);
				w2_r= pow(w_r,2)-pow(w_i, 2);
				w2_i= 2*w_r*w_i;
				p=k%(N/3);
				//printf("N=%d, v_r[k] =%f,w_r=%f,v_r[k+N/3]=%f ,w_i=%f,v_i[k+N/3]=%f, w2_r=%f,v_r[k+2*N/3]=%f, w2_i=%f,v_i[k+2*N/3]=%f\n", N, v_r[k] ,	w_r,v_r[k+N/3] , w_i,v_i[k+N/3] , w2_r,v_r[k+2*N/3] , w2_i,v_i[k+2*N/3]);
				y_r[k]	= v_r[p] +	w_r*v_r[p+N/3] - w_i*v_i[p+N/3] + w2_r*v_r[p+2*N/3] - w2_i*v_i[p+2*N/3];
				y_i[k]	= v_i[p] +	w_r*v_i[p+N/3] + w_i*v_r[p+N/3] + w2_r*v_i[p+2*N/3] + w2_i*v_r[p+2*N/3];
			}
			
			break;
	}
	
	return 0;
}



int print_complex(double *r, double *i, int N)
{
	int n;
	for(n=0;n<N;++n)
	{
		if(i[n]>=0.0)
			printf("%f +%f i\n",r[n],i[n]);
		else
			printf("%f %f i\n",r[n],i[n]);
	}
	return 0;
}