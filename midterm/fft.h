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
int fft(int *x, int *y, int N);
int ifft(int *x, int *y, int N);
/* define input x_r,input x_i,output y_r,output y_i, points of doing fft */
int print_array(int *,int N);
void swap(int *,int *);
//int bit_reverse(double *y_r, double *y_i, int N,int c);
int butterfly(int *y_r, int N,int c,int);
int ibutterfly(int *y_r, int N,int c,int);
int groupn(int *x_r,int N,int p);
int conv(int *x,int *y,int *result);
int Inverse_Zp(int w, int p);