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



int fft(double *x_r, double *x_i, double *y_r, double *y_i, int N){
	int c;
	double *u_r, *u_i, *v_r, *v_i ,theta,theta1;
	double w_r,w_i,wk_r,wk_i;
	int n,k;
    double t_r, t_i;
    double t_2r,t_2i;
    int p, q,r, m,test;
    int counter;
    

  
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
	
    test=N;
    
	//case of fft =>2 ,3 ,or 5
	if ((test%2)==0) {
		c=2;
	}else if ((test%3)==0){
		c=3;
    }else if ((test%5)==0){
        c=5;
    }
	switch( c ){
			
		case 2:

			/*for(n=0;n<N/2;n++)
			{
				y_r[n] = x_r[2*n];
				y_i[n] = x_i[2*n];
				y_r[n+N/2] = x_r[2*n+1];
				y_i[n+N/2] = x_i[2*n+1];
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
             */
            
           
            for(n=0;n<N;++n)
            {
                y_r[n] = x_r[n];
                y_i[n] = x_i[n];
            }
            m = N/2;
            q = m;
            for(p=1;p<N-1;++p)
            {
                //printf("%d <-> %d\n", p,q);
                
                if(p < q)
                {
                    //printf("%f,%f\n",y_r[p],y_r[q]);
                    swap(y_r+p,y_r+q);
                    //printf("%f,%f\n\n",y_r[p],y_r[q]);
                    swap(y_i+p,y_i+q);
                }
                k = m;
                while(q >= k & k > 0)
                {
                    q = q-k;
                    k =k/2;
                }
                q = q+k;
            }
            
            //print_complex(y_r, y_i, N);
            n = 2;
            while(n <= N)
            {
                for(k=0;k<n/2;k++)
                {
                    theta = -2.0*k*M_PI/n;
                    w_r = cos(theta);
                    w_i = sin(theta);
                    
                    for(p=k;p<N;p+=n)
                    {
                        q = p+n/2;
                        t_r = w_r*y_r[q]-w_i*y_i[q];
                        t_i = w_r*y_i[q]+w_i*y_r[q];
                        y_r[q] = y_r[p] - t_r;
                        y_i[q] = y_i[p] - t_i;
                        y_r[p] = y_r[p] + t_r;
                        y_i[p] = y_i[p] + t_i;
                        //counter=counter *2;
                    }
                    
                }
                n = n * 2;
                
            }
            
            
            
            //fft(x_r, x_i, y_r, y_i, N);
			break;
		case 3:
            /*
			
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
                //p=k;
                //printf("k=%d",k);
				//printf("N=%d, v_r[k] =%f,w_r=%f,v_r[k+N/3]=%f ,w_i=%f,v_i[k+N/3]=%f, w2_r=%f,v_r[k+2*N/3]=%f, w2_i=%f,v_i[k+2*N/3]=%f\n", N, v_r[k] ,	w_r,v_r[k+N/3] , w_i,v_i[k+N/3] , w2_r,v_r[k+2*N/3] , w2_i,v_i[k+2*N/3]);
				y_r[k]	= v_r[p] +	w_r*v_r[p+N/3] - w_i*v_i[p+N/3] + w2_r*v_r[p+2*N/3] - w2_i*v_i[p+2*N/3];
				y_i[k]	= v_i[p] +	w_r*v_i[p+N/3] + w_i*v_r[p+N/3] + w2_r*v_i[p+2*N/3] + w2_i*v_r[p+2*N/3];
                
                //y_r[k+N/3]	= v_r[p+N/3] +	w_r*v_r[p+N/3] - w_i*v_i[p+N/3] + w2_r*v_r[p+2*N/3] - w2_i*v_i[p+2*N/3];
                //y_i[k+N/3]	= v_i[p+N/3] +	w_r*v_i[p+N/3] + w_i*v_r[p+N/3] + w2_r*v_i[p+2*N/3] + w2_i*v_r[p+2*N/3];

                
                //y_r[k+2*N/3]    = v_r[p+2*N/3] +	w_r*v_r[p+N/3] - w_i*v_i[p+N/3] + w2_r*v_r[p+2*N/3] - w2_i*v_i[p+2*N/3];
                //y_i[k+2*N/3]	= v_i[p+2*N/3] +	w_r*v_i[p+N/3] + w_i*v_r[p+N/3] + w2_r*v_i[p+2*N/3] + w2_i*v_r[p+2*N/3];

			}
             */
            
            for(n=0;n<N;++n)
            {
                y_r[n] = x_r[n];
                y_i[n] = x_i[n];
            }
            m = N/3;
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
                while(q >= 2*k & k > 0)
                {
                    q = q-2*k;
                    k =k/3;
                }
                q = q+k;
            }
            
            //print_complex(y_r, y_i, N);
            n = 3;
            while(n <= N)
            {
                for(k=0;k<n/3;k++)
                {
                    theta = -2.0*k*M_PI/n;
                    theta1 = -2.0*M_PI/3;
                    w_r = cos(theta);
                    w_i = sin(theta);
                    wk_r= cos(theta1);
                    wk_i= sin(theta1);
                    printf("n=%d,w=%f+%f,w2=%f+%f\n",n,w_r,w_i,wk_r,wk_i);

                    for(p=k;p<N;p+=n)
                    {
                        q = p+n/3;
                        r = p+2*n/3;
                        t_r = w_r*y_r[q]-w_i*y_i[q];
                        t_i = w_r*y_i[q]+w_i*y_r[q];
                        t_2r= (w_r*w_r-w_i*w_i)*y_r[r]-(w_r*w_i+w_r*w_i)*y_i[r];
                        t_2i= (w_r*w_r-w_i*w_i)*y_i[r]+(w_r*w_i+w_r*w_i)*y_r[r];
                        
                        //printf("p=%d,q=%d,r=%d\n",p,q,r);
                        printf("t=%f,t2=%f\n",t_r,t_2r);
                        printf("t=%f,t2=%f\n",t_i,t_2i);
                        /*
                        y_r[r] = y_r[p] + (wk_r*wk_r-wk_i*wk_i)*(t_r + t_2r)-2*(wk_r*wk_i)*(t_i + t_2i);
                        y_i[r] = y_i[p] + (wk_r*wk_r-wk_i*wk_i)*(t_i + t_2i)+2*(wk_r*wk_i)*(t_r + t_2r);
                        y_r[q] = y_r[p] + wk_r*(t_r + t_2r)-wk_i*(t_i + t_2i);
                        y_i[q] = y_i[p] + wk_i*(t_r + t_2r)+wk_r*(t_i + t_2i);
                        */
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
                        //counter=counter *3;
                    }
                }
                n = n * 3;
                
            }
            //fft(x_r, x_i, y_r, y_i, N);
			break;
            
        case 5:
            
            for(n=0;n<N;++n)
            {
                y_r[n] = x_r[n];
                y_i[n] = x_i[n];
            }
            m = N/5;
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
                while(q >= 4*k & k > 0)
                {
                    q = q-4*k;
                    k =k/5;
                }
                q = q+k;
            }
            
            print_complex(y_r, y_i, N);
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


