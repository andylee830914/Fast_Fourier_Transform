//
//  fft.h
//  midterm
//
//  Created by Lee Yu Hsun on 2015/5/4.
//  Copyright (c) 2015年 Yu Hsun Lee. All rights reserved.
//

#ifndef __midterm__fft__
#define __midterm__fft__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#endif /* defined(__midterm__fft__) */
int fft(double *, double *, double *, double *, int N);
/* define input x_r,input x_i,output y_r,output y_i, points of doing fft */
int print_complex(double *, double *, int N);
void swap(double *,double *);
int bit_reverse(double *y_r, double *y_i, int N,int c);
int butterfly(double *y_r, double *y_i, int N,int c,int);
int groupn(double *x_r,double *x_i,int N,int p);
int reorder(double *x_r,double *x_i,int N);
int scale(double *x_r,double *x_i,int N);