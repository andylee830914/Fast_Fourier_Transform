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
	double *u_r, *u_i, *v_r, *v_i ,w_r,w_i,theta = 2*M_PI/N;
	int n,k;
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