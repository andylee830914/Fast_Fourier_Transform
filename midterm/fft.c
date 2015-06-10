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


int fft(int *x_r,int *y_r, int N){
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
        butterfly(y_r, N, order[m],N0);
        
        
        N0*=order[m];
    }
	
	
	return 0;
}



int print_array(int *r, long N){
	int n;
	for(n=0;n<N;++n)
	{
        printf("%d\n",r[n]);
	}
    printf("\n");
	return 0;
}

int bit_reverse(int *y_r, int *y_i, int N,int c){
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
    return 0;
}


int butterfly(int *y_r, int N,int c,int n){
    int theta,theta1;
    int w_r,w_i,wk_r,wk_i;
    int k;
    int t_r, t_i;
    int t_2r,t_2i;
	int t_3r,t_3i;
	int t_4r,t_4i;
    int p, q,r,s,t;

    n=n*c;
    switch( c ){
            
        case 2:

            //n = 2;
            //while(n <= N && ((2*N/n)%2)==0){
                for(k=0;k<n/2;k++){
                    theta = -2.0*k*M_PI/n;
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
                //n = n * 2;
                
            //}
            
            
            break;
            //print_complex(y_r, y_i, N);
			
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



int ifft(int *x_r, int *y_r, int N){
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
		ibutterfly(y_r, N, order[m],N0);
		
		
		N0*=order[m];
	}
	
	for(n=0;n<N;++n)
	{
		y_r[n] = y_r[n]/N;
	}
	
	
	return 0;
}

int ibutterfly(int *y_r, int N,int c,int n){
	int theta,theta1;
	int w_r,w_i,wk_r,wk_i;
	int k;
	int t_r, t_i;
	int t_2r,t_2i;
	int t_3r,t_3i;
	int t_4r,t_4i;
	int p, q,r,s,t;
	
	n=n*c;
	switch( c ){
			
		case 2:
			
			//n = 2;
			//while(n <= N && ((2*N/n)%2)==0){
			for(k=0;k<n/2;k++){
				theta = 2.0*k*M_PI/n;
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
			//n = n * 2;
			
			//}
			
			
			break;
    }
	
	return 0;
	
}
