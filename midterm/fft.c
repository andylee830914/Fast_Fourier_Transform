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


int fft(int *x_r,int *y_r, int N,int prime,int W){
	//int c;
	//int theta,theta1;
	//int w_r,w_i,wk_r,wk_i;
	//int k;
    //int t_r, t_i;
    //int t_2r,t_2i;
    int n,p, m=0;
    int N0,M0;
    int order[100];

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
            
            groupn(y_r+M0, N0, p);
            M0+=N0;
        }
        order[m]=p;
        m++;
        N0/=p;
    }
    
    
    
    while (N0<N) {
        m--;
        butterfly(y_r, N, order[m],N0,prime,W);
        
        
        N0*=order[m];
    }
	
	
	return 0;
}



int print_array(int *r, int N){
	int n;
	for(n=0;n<N;++n){
        printf("%d\n",r[n]);
	}
    printf("\n");
	return 0;
}

int print_int(int *r, int N){
    int n,M=N,i,count=0;
    
    for(i=N;i>=0;i--){
        
        if (r[i]==0&&r[i-1]!=0&&count==0) {
            //printf("r[%d]=%d\n",i,r[i]);
            M=i-1;
            count++;
        }
    }
    for(n=M;n>=0;n--){
        
        printf("%d",r[n]);
    }
    
    printf("\n");
    return 0;
}

int bit_reverse(int *y_r, int *y_i, int N,int c){
    int m,q;
    int p,k;
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
    return 0;
}


int butterfly(int *y_r, int N,int c,int n,int prime,int w_0){
    w_0=Inverse_Zp(w_0,prime);
    int w_r;
    int i,j,k;
    int t_r;
    int p, q;

    n=n*c;
    
    
    switch( c ){
            
        case 2:

            w_r=1;
            
           
                for (j=0; j<(N/(2*n)); j++) {
                    w_0=(w_0*w_0)%prime;
                }
            
            
                for(k=0;k<n/2;k++){

                    for (i=0; i<k; i+=n) {
                        w_r=(w_r*w_0)%prime;
                    }

                    
                    for(p=k;p<N;p+=n){
                        q = p+n/2;
                        t_r = (w_r*y_r[q])%prime;
                        y_r[q] = (y_r[p] + (prime-1)*t_r)%prime;
                        y_r[p] = (y_r[p] + t_r)%prime;
                    }
                    
                    
                }
            
            break;
            
			
    }
	
    return 0;

}



int groupn(int *x_r,int N,int p){
    int n,m;
    int *u_r;
	
    u_r= (int *) malloc(N*sizeof(int));

	
    for(n=0;n<N/p;n++)
    {
		
        for (m=0; m<p; m++) {
            u_r[n+m*N/p] = x_r[p*n+m];

        }
    }
	
	
    for(n=0;n<N;n++)
    {
        x_r[n] = u_r[n];
    }
	
    free(u_r);
    return 0;
}



int ifft(int *x_r, int *y_r, int N,int prime,int W){
	int n,p, m=0;
	int N0,M0;
	int order[100];
	
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
			
			groupn(y_r+M0, N0, p);
			M0+=N0;
		}
		order[m]=p;
		m++;
		N0/=p;
	}
	
	
	
	while (N0<N) {
		m--;
		ibutterfly(y_r, N, order[m],N0,prime,W);
		
		
		N0*=order[m];
	}
	
	
	return 0;
}
int Inverse_Zp(int w, int p)
{
    int k, w0 = w;
    for(k=1;k<p;++k)
    {
        if((w*w0) % p == 1)
            break;
        w = (w*w0) % p;
    }
    return w;
}

int ibutterfly(int *y_r, int N,int c,int n,int prime,int w_0){
    int w_r;
	int i,j,k;
	int t_r;
	int p, q;
	
	n=n*c;
	switch( c ){
			
		case 2:
			
            w_r=1;
            
            
            for (j=0; j<(N/(2*n)); j++) {
                w_0=(w_0*w_0)%prime;
            }
            
            for(k=0;k<n/2;k++){
                
                for (i=0; i<k; i+=n) {
                    w_r=(w_r*w_0)%prime;
                }
                for(p=k;p<N;p+=n){
                    q = p+n/2;
                    t_r = (w_r*y_r[q])%prime;
                    y_r[q] = (y_r[p] + (prime-1)*t_r)%prime;
                    y_r[p] = (y_r[p] + t_r)%prime;
                    
                }
                
                
            }
			break;
    }
	
	return 0;
	
}
