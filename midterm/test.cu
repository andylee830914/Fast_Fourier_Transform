#include <stdio.h>
#include <cuda.h>

#define DATA_SIZE 10

int data[DATA_SIZE];

__global__ static void sum(int *num, int* result,int *result1)
{
    int sum = 0;
    int i;
    for(i = 0; i < DATA_SIZE; i++) {
        sum += num[i] * num[i];
    }

    *result = sum;
    *result1= 1024;
}


bool InitCUDA()
{
    int count;

    cudaGetDeviceCount(&count);
    if(count == 0) {
        fprintf(stderr, "There is no device.\n");
        return false;
    }

    int i;
    for(i = 0; i < count; i++) {
        cudaDeviceProp prop;
        if(cudaGetDeviceProperties(&prop, i) == cudaSuccess) {
            if(prop.major >= 1) {
                break;
            }
        }
    }

    if(i == count) {
        fprintf(stderr, "There is no device supporting CUDA 1.x.\n");
        return false;
    }

    cudaSetDevice(i);

    return true;
}


void GenerateNumbers(int *number, int size)
{
    for(int i = 0; i < size; i++) {
        number[i] = i;
    }
}

int main()
{
    
    if(!InitCUDA()) {
        return 0;
    }
    
    printf("CUDA initialized.\n");

    GenerateNumbers(data, DATA_SIZE);
    for(int i = 0; i < DATA_SIZE; i++) {
        printf("data[%d]=%d\n",i,data[i]);
    }
    int *gpudata, *result,*result1;
    cudaMalloc((void**) &gpudata, sizeof(int) * DATA_SIZE);
    cudaMalloc((void**) &result, sizeof(int));
    cudaMalloc((void**) &result1, sizeof(int));
    cudaMemcpy(gpudata, data, sizeof(int) * DATA_SIZE,cudaMemcpyHostToDevice);


    sum<<<1, 1>>>(gpudata, result,result1);

    int *sum;
    int *results;
    cudaMemcpy(&sum, result, sizeof(int), cudaMemcpyDeviceToHost);
    cudaMemcpy(&results, result1, sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(gpudata);
    cudaFree(result);
    cudaFree(result1);

    printf("sum: %d\n", sum);
    printf("result1: %d\n",results);


    int sums = 0;
    for(int i = 0; i < DATA_SIZE; i++) {
        
	
        sums += data[i] * data[i];
    }
    printf("sum (CPU): %d\n", sums);

    return 0;
}
