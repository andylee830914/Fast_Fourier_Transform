//
//  main.c
//  midterm
//
//  Created by Yu Hsun Lee on 2015/4/15.
//  Copyright (c) 2015年 Yu Hsun Lee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "fft.h"
int Transpose(double **A, int N)
{
    int i, j;
    double v;
    for(i=0;i<N;++i)
    {
        for(j=i+1;j<N;++j)
        {
            v = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = v;
        }
    }
    return 0;
}
int Exact_Source(double **F, int N)
{
    int i,j;
    double x, y, h;
    h = 1.0/N;
    for(i=0;i<N-1;++i)
    {
        for(j=0;j<N-1;++j)
        {
            //k = j + i*(N-1);
            x = (i+1)*h;
            y = (j+1)*h;
            F[i][j] = -(1.0+4.0)*h*h*M_PI*M_PI*sin(M_PI*x)*sin(2*M_PI*y);
        }
    }
    return 1;	
}

int dst2d(double **X,int N){
    int j;
    
    for (j=N-1; j>=0; j--) {
    
       
        //printf("BEFORE\n");
        //print_complex(X[j], x_i, N);
        dst(X[j], N);
        //printf("AFTER\n");
        //print_complex(X[j], x_i, N);
    
    }
    Transpose(X, N);
    
    for (j=N-1; j>=0; j--) {
        
        
        //printf("BEFORE\n");
        //print_complex(X[j], x_i, N);
        dst(X[j], N);
        //printf("AFTER\n");
        //print_complex(X[j], x_i, N);
        
    }
    Transpose(X, N);
    
    return 0;
}

int idst2d(double **X,int N){
    int j;
    
    for (j=0; j<N; j++) {
        idst(X[j],  N);
    }
    Transpose(X, N);
    
    for (j=0; j<N; j++) {
        idst(X[j],  N);
    }
    Transpose(X, N);
    
    return 0;
}
int Exact_Solution(double **U, int N)
{
    // put the exact solution
    int i,j,k;
    double x, y, h;
    h = 1.0/N;
    for(i=0;i<N-1;++i)
    {
        for(j=0;j<N-1;++j)
        {
            //k = j + i*(N-1);
            x = (i+1)*h;
            y = (j+1)*h;
            U[i][j] = sin(M_PI*x)*sin(2*M_PI*y);
        }
    }
    return 1;
}


int output(double **F,int N){
    
    int i,j;
    for (i=0; i<N; ++i) {
        for (j=0; j<N; ++j) {
            printf("%f ",F[i][j]);
        }
        printf("\n");
    }
    return 0;
}


int main() {
    int i, j, k, N, M;
    double **A, *x, *u, **U, *b, **F, *r;
	clock_t t1, t2;
    printf("hello final : DST \n");
    N=4;
    M = (N-1)*(N-1);
    b = (double *) malloc(M*sizeof(double));
    F = (double **) malloc((N-1)*sizeof(double*));
    F[0] = b;
    for(i=1;i<N-1;++i) F[i] = F[i-1] + (N-1);
    u = (double *) malloc(M*sizeof(double));
    U = (double **) malloc((N-1)*sizeof(double*));
    U[0] = u;
    for(i=1;i<N-1;++i) U[i] = U[i-1] + (N-1);
    Exact_Source(F, N);
    output(F,N-1);
    printf("N=%d,\n",N);
    
    
	//t1 = clock();
    dst2d(F,N-1);
    output(F,N-1);
    printf("\n");
    idst2d(F,N-1);
    output(F,N-1);
	//t2 = clock();
	//Exact_Solution(U, N);
    //output(U, N-1);
	//printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);//print times
	
    free(b);
    free(u);
    free(U);
    free(F);
	//sort(v,N);
    return 0;
}
