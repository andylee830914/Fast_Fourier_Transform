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

int n,tempN;
int fft(double *x_r, double *x_i, double *y_r, double *y_i, int N){
	//int c;
	//double theta,theta1;
	//double w_r,w_i,wk_r,wk_i;
	//int k;
    //double t_r, t_i;
    //double t_2r,t_2i;
    //int p, q, m;
 

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
    
    
    
    if ((N%2)==0) {
        bit_reverse(y_r, y_i, N, 2);
        if ((N%3)==0) {
            bit_reverse(y_r, y_i, N, 3);
            butterfly(y_r, y_i, N, 3);
        }
        butterfly(y_r, y_i, N, 2);
    }else if ((N%3)==0){
        bit_reverse(y_r, y_i, N, 3);
        butterfly(y_r, y_i, N, 3);
    
    }
    
    
    
	
	return 0;
}



int print_complex(double *r, double *i, int N){
	int n;
	for(n=0;n<N;++n)
	{
		if(i[n]>=0.0)
			printf("%f +%f i\n",r[n],i[n]);
		else
			printf("%f %f i\n",r[n],i[n]);
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
            printf("%d,%d\n",p,q);
            swap(y_r+p,y_r+q);
            //printf("%d,%d\n\n",p,q);
            swap(y_i+p,y_i+q);
        }
        k = m;
        while(q >= (c-1)*k & k > 0)
        {
            q = q-(c-1)*k;
            k =k/c;
        }
        q = q+k;
    }
    print_complex(y_r, y_i, N);
    return 0;
}


int butterfly(double *y_r, double *y_i, int N,int c){
    double theta,theta1;
    double w_r,w_i,wk_r,wk_i;
    int k;
    double t_r, t_i;
    double t_2r,t_2i;
    int p, q,r;

    
    switch( c ){
            
        case 2:

            n = 2;
            while(n <= N && ((2*N/n)%2)==0){
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
                n = n * 2;
                
            }
            
            
            break;
        case 3:
            n = 3;
            while(n <= N && ((3*N/n)%3)==0){
                for(k=0;k<n/3;k++){
                    theta = -2.0*k*M_PI/n;
                    theta1 = -2.0*M_PI/3;
                    w_r = cos(theta);
                    w_i = sin(theta);
                    wk_r= cos(theta1);
                    wk_i= sin(theta1);
                    //printf("n=%d,w=%f+%f,w2=%f+%f\n",n,w_r,w_i,wk_r,wk_i);
                    
                    for(p=k;p<N;p+=n)
                    {
                        q = p+n/3;
                        r = p+2*n/3;
                        t_r = w_r*y_r[q]-w_i*y_i[q];
                        t_i = w_r*y_i[q]+w_i*y_r[q];
                        t_2r= (w_r*w_r-w_i*w_i)*y_r[r]-(w_r*w_i+w_r*w_i)*y_i[r];
                        t_2i= (w_r*w_r-w_i*w_i)*y_i[r]+(w_r*w_i+w_r*w_i)*y_r[r];
                        
                        
                        
                        y_r[r]=y_r[p]
                        +(wk_r*wk_r-wk_i*wk_i)*t_r-(2*wk_r*wk_i)*t_i
                        +((wk_r*wk_r-wk_i*wk_i)*(wk_r*wk_r-wk_i*wk_i)-(2*wk_r*wk_i)*(2*wk_r*wk_i))*t_2r-(2*(wk_r*wk_r-wk_i*wk_i)*(2*wk_r*wk_i))*t_2i;
                        y_i[r]=y_i[p]
                        +(wk_r*wk_r-wk_i*wk_i)*t_i+(2*wk_r*wk_i)*t_r//wk^2
                        +((wk_r*wk_r-wk_i*wk_i)*(wk_r*wk_r-wk_i*wk_i)-(2*wk_r*wk_i)*(2*wk_r*wk_i))*t_2i+(2*(wk_r*wk_r-wk_i*wk_i)*(2*wk_r*wk_i))*t_2r;//wk^4
                        
                        
                        y_r[q]=y_r[p]
                        +wk_r*t_r-wk_i*t_i//wk^1
                        +(wk_r*wk_r-wk_i*wk_i)*t_2r-(2*wk_r*wk_i)*t_2i;//wk^2
                        y_i[q]=y_i[p]
                        +wk_r*t_i+wk_i*t_r
                        +(wk_r*wk_r-wk_i*wk_i)*t_2i+(2*wk_r*wk_i)*t_2r;
                        
                        y_r[p]=y_r[p]+t_r+t_2r;
                        y_i[p]=y_i[p]+t_i+t_2i;
                    }
                }
                n = n * 3;
                
            }
            break;
            
            
            //print_complex(y_r, y_i, N);
    
    }
    
    return 0;

}
