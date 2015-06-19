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

int Order(int w, int p)
{
    int k, w0 = w;
    for(k=1;k<p;++k)
    {
        if(w % p == 1)
            break;
        w = (w*w0) % p;
    }
    return k;
}

int isPrime(int prime) {
    int i;
    for (i=2; i*i<=prime; i++) {
        if ((prime % i) == 0) {
            return 0;
        }
    }
    return 1;
}

int Parameter_Finder(int N,int *prime, int *omega){
    int p,n,find_w;
    p=81*(N/2)+1;
    while(1){
        if(isPrime(p)==1){
            if( (p - 1) % N == 0){
                find_w = 0;
                for(n=2;n<p;++n){
                    if(Order(n,p)==N){
                        find_w = 1;
                        break;
                    }
                }
                if(find_w == 1) break;
            }
        }
        p += 2;
    }
    
    *prime=p;
    *omega=n;
    
    //printf("N=%d,prime=%d,omega=%d\n",N,p,n);
    
    
    return 0;
}



int main() {
	int N,length,i,prime,W;
    long Ninv;
	char *a,*b,*c;
	long *y_1, *y_2, *x_1, *x_2;
    int length_a,length_b;
	clock_t t1, t2;
    a = (char *) malloc(MAXCHAR*sizeof(char));
    b = (char *) malloc(MAXCHAR*sizeof(char));
    c = (char *) malloc(2*MAXCHAR*sizeof(char));
    printf("hello final : Multiplication \n");
    
    
    
	
	printf("Input number a and b (MAXIMUM DIGITS:%d)\n", MAXCHAR);
    scanf("%s %s", a, b);
    printf("%s * %s = ", a, b);

    
	x_1 = (long *) malloc(MAXCHAR*sizeof(long));//initial x
	x_2 = (long *) malloc(MAXCHAR*sizeof(long));//fft out x
	y_1 = (long *) malloc(MAXCHAR*sizeof(long));//initial y
	y_2 = (long *) malloc(MAXCHAR*sizeof(long));//fft out y
    length_a = (int)strlen(a);
    length_b = (int)strlen(b);
    Reverse(a,length_a);
    Reverse(b,length_b);
    Char2Int(a, length_a);
    Char2Int(b, length_b);
    if (length_a==1&&length_b==1) {
        printf("%d",a[0]*b[0]);
        return 0;
    }
    //initial data
    if (length_a>length_b) {
        length=length_a;
    }else{
        length=length_b;
    }
    N=1;
    while(N<2*length){
        N <<=1;
    }
    //initial parameter
    Parameter_Finder(N,&prime,&W);
    /*N=16;
    prime=1409;
    W=10;*/
    Ninv = Inverse_Zp(N,prime);
    //printf("Ninv=%ld\n",Ninv);
    
    for (i=0; i<N; i++) {
        x_1[i]=a[i];
        if (i>=length_a) {
            x_1[i]=0;
        }
    }
    for (i=0; i<N; i++) {
        y_1[i]=b[i];
        if (i>=length_b) {
            y_1[i]=0;
        }
    }

    t1 = clock();
    fft(x_1, x_2,N,prime,W);
    fft(y_1, y_2,N,prime,W);
    
    for(i=0;i<N;++i){
        x_2[i] = (((x_2[i]%prime)*(y_2[i]%prime)*Ninv)%prime);
    }
    
    ifft(x_2, x_2, N,prime,W);
    for(i=0;i<N;++i){
        x_2[i+1] += x_2[i]/10;
        x_2[i] = x_2[i] % 10;
    }
    t2 = clock();
    print_int(x_2, N);

	printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);//print times
	free(x_1);
	free(x_2);
	free(y_1);
	free(y_2);
	//sort(v,N);
    return 0;
    
}
