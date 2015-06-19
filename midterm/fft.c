//
//  fft.c
//  midterm
//
//  Created by Lee Yu Hsun on 2015/5/4.
//  Copyright (c) 2015年 Yu Hsun Lee. All rights reserved.
//

#include "fft.h"

void swap(double *p,double *q){
    double tmp;
    tmp=*p;
    *p=*q;
    *q=tmp;
    
}


int dst(double *x_r, int N){
    int n,p;
    int N0,M0;
    double *u_r,*u_i,*y_r,*y_i;
    u_r = (double *) malloc((2*N+2)*sizeof(double));
    u_i = (double *) malloc((2*N+2)*sizeof(double));
    y_r = (double *) malloc((2*N+2)*sizeof(double));
    y_i = (double *) malloc((2*N+2)*sizeof(double));
	
	for(n=0;n<N;++n)
	{
		u_i[n] = x_r[n];
		u_r[n] = 0;
		
	}
	reorder(u_r, u_i, N);
    //print_complex(u_i, u_r, (2*N+2));
	N=2*N+2;
	
	//termination conditions
	if(N==1){
		
		y_r[0] = x_r[0];
		y_i[0] = 0;
		
		return 0;
	}
    

    
    
    for(n=0;n<N;++n)
    {
        y_r[n] = u_r[n];
        y_i[n] = u_i[n];
    }
    
    N0=N;
    p=1;
    while (N0>1) {
        M0=0;
        while (M0<N) {
            
            groupn(y_r+M0, y_i+M0, N0, 2);
            M0+=N0;
        }
        N0/=2;
    }
    
    
    
    while (N0<N) {
        butterfly(y_r, y_i, N,N0);
        N0*=2;
    }
	N=(N-2)/2;
	scale(y_r, y_i,N);
    
    
    for(n=0;n<N;++n)
    {
        x_r[n] = y_r[n];
    }
    free(u_r);
    free(u_i);
    free(y_r);
    free(y_i);
	
	return 0;
}

int idst(double *x_r, int N){
    int n,p;
	int N0,M0;
    double *u_r,*u_i,*y_r,*y_i;
    u_r = (double *) malloc((2*N+2)*sizeof(double));
    u_i = (double *) malloc((2*N+2)*sizeof(double));
    y_r = (double *) malloc((2*N+2)*sizeof(double));
    y_i = (double *) malloc((2*N+2)*sizeof(double));

	
	for(n=0;n<N;++n)
	{
		u_i[n] = x_r[n];
		u_r[n] = 0;
		
	}
	reorder(u_r, u_i, N);
    
	N=2*N+2;
		//termination conditions
	if(N==1){
		
		y_r[0] = x_r[0];
		y_i[0] = 0;
		
		return 0;
	}
	
	
	
	
	for(n=0;n<N;++n)
	{
		y_r[n] = u_r[n];
		y_i[n] = u_i[n];
	}
	
	N0=N;
	p=1;
	while (N0>1) {
		M0=0;
		while (M0<N) {
			
			groupn(y_r+M0, y_i+M0, N0, 2);
			M0+=N0;
		}
		N0/=2;
	}
	
	
	
	while (N0<N) {
		butterfly(y_r, y_i, N,N0);
		
		
		N0*=2;
	}
	
	N=(N-2)/2;
	iscale(y_r, y_i,N);
    for(n=0;n<N;++n)
    {
        x_r[n] = y_r[n];
    }
    free(u_r);
    free(u_i);
    free(y_r);
    free(y_i);
	return 0;
}



int print_complex(double *r, double *i, int N){
	int n;
	for(n=0;n<N;++n)
	{
		printf("%f\n",r[n]);
	}
    printf("\n");
	return 0;
}

int bit_reverse(double *y_r, double *y_i, int N,int c){
    int m,p,q,k;
    m = N/c;
    q = m;
    for(p=1;p<N-1;++p)
    {
        //printf("%d <-> %d\n", p,q);
        
        if(p < q)
        {
            //printf("%d,%d\n",p,q);
            swap(y_r+p,y_r+q);
            //printf("%d,%d\n\n",p,q);
            swap(y_i+p,y_i+q);
        }
        k = m;
        while(q >= (c-1)*k & k > 0)
        {
            q = q-(c-1)*k;
            k =k/c;
            //printf("%d,%d\n",q,k);
        }
        q = q+k;
        
    }
    print_complex(y_r, y_i, N);
    return 0;
}


int butterfly(double *y_r, double *y_i, int N,int n){
    double theta;
    double w_r,w_i;
    int k;
    double t_r, t_i;
    int p, q;

    n=n*2;
                for(k=0;k<n/2;k++){
                    theta = -2.0*(k+1)*M_PI/n;
                    w_r = cos(theta);
                    w_i = sin(theta);
                    
                    for(p=k;p<N;p+=n){
                        q = p+n/2;
                        t_r = w_r*y_r[q]-w_i*y_i[q];
                        t_i = w_r*y_i[q]+w_i*y_r[q];
                        y_r[q] = y_r[p] - t_r;
                        y_i[q] = y_i[p] - t_i;
                        y_r[p] = y_r[p] + t_r;
                        y_i[p] = y_i[p] + t_i;
                        
                    }
                    
                }

	
    return 0;

}

int groupn(double *x_r,double *x_i,int N,int p){
    int n,m;
    double *u_r,*u_i;
	
    u_r= (double *) malloc(N*sizeof(double));
    u_i= (double *) malloc(N*sizeof(double));

	
    for(n=0;n<N/p;n++)
    {
		
        for (m=0; m<p; m++) {
            u_r[n+m*N/p] = x_r[p*n+m];
            u_i[n+m*N/p] = x_i[p*n+m];

        }
    }
	
	
    for(n=0;n<N;n++)
    {
        x_r[n] = u_r[n];
        x_i[n] = u_i[n];
    }
	
    free(u_r);
    free(u_i);
    return 0;
}

int reorder(double *x_r,double *x_i,int N){
	int i,n;
	double *s_r,*s_i;
	s_r= (double *) malloc(2*(N+1)*sizeof(double));
	s_i= (double *) malloc(2*(N+1)*sizeof(double));
	//print_complex(x_i, x_r, N);
    
    for (i=0; i<N; i++) {
		s_r[i+1]=x_r[i];
		s_i[i+1]=x_i[i];
	}
    //print_complex(s_i, s_r, N+1);
    
	for(n=1;n<N+1;n++){
		
		x_r[n] = s_r[n];
		x_i[n] = s_i[n];
        x_r[2*N+2-n] = -s_r[n];
        x_i[2*N+2-n] = -s_i[n];
	}
    x_r[0]=0;
    x_i[0]=0;
    x_r[N+1]=0;
    x_i[N+1]=0;
	//print_complex(x_i, x_r, 2*N+2);
	free(s_r);
	free(s_i);
	//print_complex(x_r, x_i, N+1);
	
	return 0;
}

int scale(double *x_r,double *x_i,int N){
	int i;
	for (i=0; i<N; i++) {
		x_r[i]=x_r[i]/2;
		x_i[i]=0;
	}
	
	
	return 0;
}

int iscale(double *x_r,double *x_i,int N){
	int i;
	for (i=0; i<N; i++) {
		x_r[i]=x_r[i]/(N+1);
		x_i[i]=0;
	}
	
	
	return 0;
}