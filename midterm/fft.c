//
//  fft.c
//  midterm
//
//  Created by Lee Yu Hsun on 2015/5/4.
//  Copyright (c) 2015年 Yu Hsun Lee. All rights reserved.
//

#include "fft.h"

void swap(int *p,int *q){
    int tmp;
    tmp=*p;
    *p=*q;
    *q=tmp;
    
}


int fft(long *x_r,long *y_r, int N,int prime,long W){
    int n;
    int N0,M0;

	//termination conditions
	if(N==1){
		
		y_r[0] = x_r[0];
		
		return 0;
	}
    

    
    
    for(n=0;n<N;++n)
    {
        y_r[n] = x_r[n];
    }
    //print_array(y_r, N);
    N0=N;
    while (N0>1) {
        M0=0;
        while (M0<N) {
            groupn(y_r+M0, N0);
            M0+=N0;
        }
        N0/=2;
    }
    
    
    
    while (N0<N) {
        butterfly(y_r, N,N0,prime,W);
        N0*=2;
    }
	
	
	return 0;
}



int print_array(long *r, int N){
	int n;
	for(n=0;n<N;++n){
        printf("%ld\n",r[n]);
	}
    printf("\n");
	return 0;
}

int print_int(long *r, int N){
    int n,M=N,i,count=0;
    
    for(i=N;i>=0;i--){
        
        if (r[i]==0&&r[i-1]!=0&&count==0) {
            //printf("r[%d]=%d\n",i,r[i]);
            M=i-1;
            count++;
        }
    }
    for(n=M;n>=0;n--){
        
        printf("%ld",r[n]);
    }
    
    printf("\n");
    return 0;
}

int butterfly(long *y_r, int N,int n,int prime,long w_0){
    w_0=Inverse_Zp(w_0,prime);
    printf("wi=%d\n",w_0);
    long w_r;
    int i,j,k;
    long t_r;
    int p, q;
    n=n*2;
    
            w_r=1;
                for (j=0; j<(N/(2*n)); j++) {
                    w_0=((w_0%prime)*(w_0%prime))%prime;
                }
                for(k=0;k<n/2;k++){
                    for (i=0; i<k; i+=n) {
                        w_r=((w_r%prime)*(w_0%prime))%prime;
                    }
                    for(p=k;p<N;p+=n){
                        q = p+n/2;
                        t_r = ((w_r%prime)*(y_r[q]%prime))%prime;
                        y_r[q] = (y_r[p]%prime + (prime-1)*t_r)%prime;
                        y_r[p] = (y_r[p]%prime + t_r)%prime;
                        //printf("y_r[%d]=%ld,y_r[%d]=%ld\n",p,y_r[p],q,y_r[q]);
                    }
                }

            
			
    
	
    return 0;

}



int groupn(long *x_r,int N){
    int n,m;
    long *u_r;
	
    u_r= (long *) malloc(N*sizeof(long));

	
    for(n=0;n<N/2;n++)
    {
		
        for (m=0; m<2; m++) {
            u_r[n+m*N/2] = x_r[2*n+m];

        }
    }
    for(n=0;n<N;n++)
    {
        x_r[n] = u_r[n];
    }
	
    free(u_r);
    return 0;
}



int ifft(long *x_r, long *y_r, int N,int prime,long W){
	int n;
	int N0,M0;
	//termination conditions
	if(N==1){
		
		y_r[0] = x_r[0];
		
		return 0;
	}
	
	for(n=0;n<N;++n)
	{
		y_r[n] = x_r[n];
	}
	
	N0=N;
	while (N0>1) {
		M0=0;
		while (M0<N) {
			groupn(y_r+M0, N0);
			M0+=N0;
		}
		N0/=2;
	}
	
	
	
	while (N0<N) {
		ibutterfly(y_r, N,N0,prime,W);
		N0*=2;
	}
	
	
	return 0;
}
long Inverse_Zp(long w, int p)
{
    int k;
    long w0 = w;
    for(k=1;k<p;++k)
    {
        if((w*w0) % p == 1)
            break;
        w = (w*w0) % p;
    }
    return w;
}

int ibutterfly(long *y_r, int N,int n,int prime,long w_0){
    long w_r;
	int i,j,k;
	long t_r;
	int p, q;
	
	n=n*2;

            w_r=1;
            for (j=0; j<(N/(2*n)); j++) {
                w_0=((w_0%prime)*(w_0%prime))%prime;
            }
            for(k=0;k<n/2;k++){
                
                for (i=0; i<k; i+=n) {
                    w_r=((w_r%prime)*(w_0%prime))%prime;
                }
                for(p=k;p<N;p+=n){
                    q = p+n/2;
                    t_r = ((w_r%prime)*(y_r[q]%prime))%prime;
                    y_r[q] = (y_r[p]%prime + (prime-1)*t_r)%prime;
                    y_r[p] = (y_r[p]%prime + t_r)%prime;
                }
            }
	
	return 0;
	
}
