//
//  main.c
//  midterm
//
//  Created by Yu Hsun Lee on 2015/4/15.
//  Copyright (c) 2015年 Yu Hsun Lee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"
#include "fft.h"
#define  MAXCHAR 400

int Char2Int(char *a, int N){
    int i;
    for(i=0; i<N; i++){
        a[i] -= 48;
    }
    
    return 0;
}
int Int2Char(char *a, int N){
    int i;
    for(i=0; i<N; i++){
        a[i] += 48;
    }
    a[N] = 0;
    
    return 0;
}

int Reverse(char *a, int N){
    int i;
    char temp;
    for (i=0; i<N/2; i++) {
        temp        = a[i];
        a[i]        = a[N-1-i];
        a[N-1-i]    = temp;
    }
    
    return 0;
}



int main() {
	int N,length,i,Ninv,prime,W;
	char *a,*b,*c;
	int *y_1, *y_2, *x_1, *x_2,*result;
    int length_a,length_b;
	clock_t t1, t2;
    a = (char *) malloc(MAXCHAR*sizeof(char));
    b = (char *) malloc(MAXCHAR*sizeof(char));
    c = (char *) malloc(2*MAXCHAR*sizeof(char));
    printf("hello midterm \n");
    
    prime=409;
    W=31;
    
	
	printf("Input number a and b (MAXIMUM DIGITS:%d)\n", MAXCHAR);
    scanf("%s %s", a, b);
    printf("%s * %s = \n", a, b);

    
	x_1 = (int *) malloc(MAXCHAR*sizeof(int));//initial x
	x_2 = (int *) malloc(MAXCHAR*sizeof(int));//fft out x
	y_1 = (int *) malloc(MAXCHAR*sizeof(int));//initial y
	y_2 = (int *) malloc(MAXCHAR*sizeof(int));//fft out y
    length_a = (int)strlen(a);
    length_b = (int)strlen(b);
    Reverse(a,length_a);
    Reverse(b,length_b);
    Char2Int(a, length_a);
    Char2Int(b, length_b);
    //initial data
    
    for (i=0; i<length_a; i++) {
        x_1[i]=a[i];
    }
    for (i=0; i<length_b; i++) {
        y_1[i]=b[i];
    }
    
    
    if (length_a>length_b) {
        length=length_a;
    }else{
        length=length_b;
    }
    
    fft(x_1, x_2,  length,prime,W);
    //ifft(x_2, x_2,  length_a);
    fft(y_1, y_2,  length,prime,W);
    //print_array(y_2, length_b);
    //ifft(y_2, y_2,  length_b);
    
    
    N=1;
    while(N<2*length){
        N <<=1;
    }
    N=N/2;
    //print_array(x_2, length);
    //print_array(y_2, length);
    Ninv = Inverse_Zp(N,prime);
    for(i=0;i<length;++i){
        x_2[i] = ((x_2[i]*y_2[i]%prime*Ninv)%prime);
    }
    ifft(x_2, x_2, length,prime,W);
    //print_array(x_2, length);
    for(i=0;i<N;++i){
        x_2[i+1] += x_2[i]/10;
        x_2[i] = x_2[i] % 10;
    }
    //
    print_int(x_2, N);
    /*
	
	
	t1 = clock();
	fft(x_1, y_1, N);
    fft(x_2, y_2, N);
    conv(y_1, y_2, result);
    
	
	//
	t2 = clock();
	
	printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);//print times
    print_array(result, N);
	*/
	free(x_1);
	free(x_2);
	free(y_1);
	free(y_2);
	//sort(v,N);
    return 0;
    
}
