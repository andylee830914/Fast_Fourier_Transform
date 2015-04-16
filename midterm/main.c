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



int main() {
	int i,N,*v;
    printf("hello midterm \n");
	
	srand(time(NULL));
	N=10;
	v=(int *) malloc(N *sizeof(int));
	printf("ori   ");
	for(i=0;i<N;++i){
		v[i]=rand() % 100;
		//printf("%d,",v[i]);
	}
	
	
	sort(v,N);
    return 0;
}
