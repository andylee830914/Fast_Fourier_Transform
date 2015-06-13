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
int fft(long *x, long *y, int N,int prime,long W);
int ifft(long *x, long *y, int N,int prime,long W);
/* define input x_r,input x_i,output y_r,output y_i, points of doing fft */
int print_array(long *,int N);
int print_int(long *,int N);
void swap(int *,int *);
//int bit_reverse(double *y_r, double *y_i, int N,int c);
int butterfly(long *y_r, int N,int,int prime,long W);
int ibutterfly(long *y_r, int N,int,int prime,long W);
int groupn(long *x_r,int N);
long Inverse_Zp(long w, int p);