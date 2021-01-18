#include <cuda.h>
#include <stdio.h>

#define CHECK(call)                                   \
{                                                     \
    const cudaError_t error = call;                   \
    if (error != cudaSuccess)                         \
    {                                                 \
        printf("cuda error %d",(int)error);           \
    }                                                 \
}

extern "C" void cuda_add(float *a, float *b, float *c, int n);

__global__ void add1_kernel(float *a, float *b, float *c, int n)
{
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	while (tid < n)
	{
		c[tid] = a[tid] + b[tid];
		tid += blockDim.x * gridDim.x;
	}
}

void cuda_add(float *a, float *b, float *c, int n);
void cuda_add(float *a, float *b, float *c, int n){
    float *dev_a, *dev_b, *dev_c;

	
    // Allocate for GPU
	CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
	CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
	CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
	CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
	CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

	add1_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, n);

	// copy to host c from GPU dev_c
	CHECK(cudaMemcpy(c, dev_c, n * sizeof(float), cudaMemcpyDeviceToHost));
    
    // free 
    cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

}


extern "C" void cuda_sub(float *a, float *b, float *c, int n);

__global__ void sub1_kernel(float *a, float *b, float *c, int n)
{
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	while (tid < n)
	{
		c[tid] = a[tid] - b[tid];
		tid += blockDim.x * gridDim.x;
	}
}

void cuda_sub(float *a, float *b, float *c, int n);
void cuda_sub(float *a, float *b, float *c, int n){
    float *dev_a, *dev_b, *dev_c;

	
    // Allocate for GPU
	cudaMalloc((void**)&dev_a, n * sizeof(float));
	cudaMalloc((void**)&dev_b, n * sizeof(float));
	cudaMalloc((void**)&dev_c, n * sizeof(float));


    // copy from host a,b to GPU dev_a, dev_b
	cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice);

	sub1_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, n);

	// copy to host c from GPU dev_c
	cudaMemcpy(c, dev_c, n * sizeof(float), cudaMemcpyDeviceToHost);
    
    // free 
    cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

}

