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


int dct(double *x_r, double *x_i, double *y_r, double *y_i, int N){
	//int c;
	//double theta,theta1;
	//double w_r,w_i,wk_r,wk_i;
	//int k;
    //double t_r, t_i;
    //double t_2r,t_2i;
	
	reorder(x_r, x_i, N);
	N=4*N;
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
	N=N/4;
	scale(y_r, y_i,N);
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


int butterfly(double *y_r, double *y_i, int N,int c,int n){
    double theta,theta1;
    double w_r,w_i,wk_r,wk_i;
    int k;
    double t_r, t_i;
    double t_2r,t_2i;
	double t_3r,t_3i;
	double t_4r,t_4i;
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
        case 3:
            //n = 3;
            //while(n <= N && ((3*N/n)%3)==0){
			theta1 = -2.0*M_PI/3;
			wk_r= cos(theta1);
			wk_i= sin(theta1);
                for(k=0;k<n/3;k++){
                    theta = -2.0*k*M_PI/n;
                    w_r = cos(theta);
                    w_i = sin(theta);
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
						+wk_r*(t_r+t_2r)+wk_i*(t_i-t_2i);
						y_i[r]=y_i[p]
						+wk_r*(t_i+t_2i)-wk_i*(t_r-t_2r);
						
						y_r[q]=y_r[p]
						+wk_r*(t_r+t_2r)-wk_i*(t_i-t_2i);//wk^1
						y_i[q]=y_i[p]
						+wk_r*(t_i+t_2i)+wk_i*(t_r-t_2r);
						
						y_r[p]=y_r[p]+t_r+t_2r;
						y_i[p]=y_i[p]+t_i+t_2i;
                    }
                }
                //n = n * 3;
			
            //}
            break;
		case 5:
			//n = 3;
			//while(n <= N && ((3*N/n)%3)==0){
			theta1 = -2.0*M_PI/5;
			wk_r= cos(theta1);
			wk_i= sin(theta1);
			for(k=0;k<n/5;k++){
				theta = -2.0*k*M_PI/n;
				w_r = cos(theta);
				w_i = sin(theta);
				
				//printf("n=%d,w=%f+%f,w2=%f+%f\n",n,w_r,w_i,wk_r,wk_i);
				
				for(p=k;p<N;p+=n)
				{
					q = p+n/5;
					r = p+2*n/5;
					s = p+3*n/5;
					t = p+4*n/5;
					t_r = w_r*y_r[q]-w_i*y_i[q];
					t_i = w_r*y_i[q]+w_i*y_r[q];
					t_2r= (w_r*w_r-w_i*w_i)*y_r[r]-(w_r*w_i+w_r*w_i)*y_i[r];
					t_2i= (w_r*w_r-w_i*w_i)*y_i[r]+(w_r*w_i+w_r*w_i)*y_r[r];
					t_3r= (w_r*w_r*w_r-3*w_r*w_i*w_i)*y_r[s]-(3*w_r*w_r*w_i-w_i*w_i*w_i)*y_i[s];
					t_3i= (w_r*w_r*w_r-3*w_r*w_i*w_i)*y_i[s]+(3*w_r*w_r*w_i-w_i*w_i*w_i)*y_r[s];
					t_4r= ((w_r*w_r-w_i*w_i)*(w_r*w_r-w_i*w_i)-(2*w_r*w_i)*(2*w_r*w_i))*y_r[t]-(2*(w_r*w_r-w_i*w_i)*(2*w_r*w_i))*y_i[t];
					t_4i= ((w_r*w_r-w_i*w_i)*(w_r*w_r-w_i*w_i)-(2*w_r*w_i)*(2*w_r*w_i))*y_i[t]+(2*(w_r*w_r-w_i*w_i)*(2*w_r*w_i))*y_r[t];
					
					y_r[t]=y_r[p]
					+wk_r*(t_4r+t_r)-wk_i*(t_4i-t_i)//wk^1
					+(wk_r*wk_r-wk_i*wk_i)*(t_3r+t_2r)-(2*wk_r*wk_i)*(t_3i-t_2i);
					y_i[t]=y_i[p]
					+wk_r*(t_4i+t_i)+wk_i*(t_4r-t_r)
					+(wk_r*wk_r-wk_i*wk_i)*(t_3i+t_2i)+(2*wk_r*wk_i)*(t_3r-t_2r);
					
					y_r[s]=y_r[p]
					+wk_r*(t_2r+t_3r)-wk_i*(t_2i-t_3i)//wk^1
					+(wk_r*wk_r-wk_i*wk_i)*(t_4r+t_r)-(2*wk_r*wk_i)*(t_4i-t_i);
					y_i[s]=y_i[p]
					+wk_r*(t_2i+t_3i)+wk_i*(t_2r-t_3r)
					+(wk_r*wk_r-wk_i*wk_i)*(t_4i+t_i)+(2*wk_r*wk_i)*(t_4r-t_r);
					
					y_r[r]=y_r[p]
					+wk_r*(t_3r+t_2r)-wk_i*(t_3i-t_2i)//wk^1
					+(wk_r*wk_r-wk_i*wk_i)*(t_r+t_4r)-(2*wk_r*wk_i)*(t_i-t_4i);
					y_i[r]=y_i[p]
					+wk_r*(t_3i+t_2i)+wk_i*(t_3r-t_2r)
					+(wk_r*wk_r-wk_i*wk_i)*(t_i+t_4i)+(2*wk_r*wk_i)*(t_r-t_4r);
					
					y_r[q]=y_r[p]
					+wk_r*(t_r+t_4r)-wk_i*(t_i-t_4i)//wk^1
					+(wk_r*wk_r-wk_i*wk_i)*(t_2r+t_3r)-(2*wk_r*wk_i)*(t_2i-t_3i);
					y_i[q]=y_i[p]
					+wk_r*(t_i+t_4i)+wk_i*(t_r-t_4r)
					+(wk_r*wk_r-wk_i*wk_i)*(t_2i+t_3i)+(2*wk_r*wk_i)*(t_2r-t_3r);
					
					y_r[p]=y_r[p]+t_r+t_2r+t_3r+t_4r;
					y_i[p]=y_i[p]+t_i+t_2i+t_3i+t_4i;
				}
			}
			//n = n * 3;
			
			//}
			break;

			
			
            //print_complex(y_r, y_i, N);
			
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
	double *u_r,*u_i;
	u_r= (double *) malloc(4*N*sizeof(double));
	u_i= (double *) malloc(4*N*sizeof(double));

	for (i=0; i<N; i++) {
		u_r[2*i+1]=x_r[i];
		u_i[2*i+1]=x_i[i];
	}
	for(n=0;n<4*N;n++){
		if ((n%2==0)) {
			u_r[n]=0;
			u_i[n]=0;
		}
		x_r[n] = u_r[n];
		x_i[n] = u_i[n];
	}
	
	free(u_r);
	free(u_i);
	
	
	return 0;
}


int scale(double *x_r,double *x_i,int N){
	int i;
	x_r[0]=x_r[0]/sqrt(N);
	x_i[0]=0;
	for (i=1; i<N; i++) {
		x_r[i]=x_r[i]*sqrt(2.0/N);
		x_i[i]=0;
	}
	
	
	return 0;
}
