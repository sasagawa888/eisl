/*
Easter project GPGPU of Easy-ISLisp

*/


#include <cublas.h>
#include <stdio.h>
#include <stdlib.h>
#include "eisl.h"

#define IDX2C(i,j,ld) (((j)*(ld))+(i))
#define IDX3C(c,i,j,in_h,in_w) ((c)*((in_h)*(in_w)) + (i)*(in_w) +(j))
#define IDX4C(n,c,i,j,in_c,in_h,in_w) ((n)*((in_c)*(in_h)*(in_w)) + (c)*((in_h)*(in_w)) + (i)*(in_w) +(j))
#define IDX5C(t,n,c,i,j,in_n,in_c,in_h,in_w) ((t)*((in_n)*(in_c)*(in_h)*(in_w)) + (n)*((in_c)*(in_h)*(in_w)) + (c)*((in_h)*(in_w)) + (i)*(in_w) +(j))
#define SIGMOID(x)  (1 / (1+exp(-1*x)))
#define CHECK(call)                                   \
{                                                     \
    const cudaError_t error = call;                   \
    if (error != cudaSuccess)                         \
    {                                                 \
        return enif_make_int(env,10000+(int)error);   \
    }                                                 \
}
#define CUBLAS(call)                                  \
{                                                     \
    const cublasStatus error = call;                  \
    if (error != CUBLAS_STATUS_SUCCESS)               \
    {                                                 \
        return(11000+(int)error);   \
    }                                                 \
}


int f_dp_mult(int arglist){
    int arg1,arg2,dim1,dim2,dim3,r1, c1, r2, c2, n, i, j, res;
    float *a,*b,*c;
    float* devPtrA;
    float* devPtrB;
    float* devPtrC;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    dim3 = list2(car(dim1),cadr(dim2));
    res = makefarray(dim3,0.0);
    r1 = GET_INT(car(dim1));
    c1 = GET_INT(cadr(dim1));
    r2 = GET_INT(car(dim2));
    c2 = GET_INT(cadr(dim2));
    n = r1*c2;
    // Memory Allocation
    a = (float *)malloc (r1 * c1 * sizeof (*a));
    b = (float *)malloc (r2 * c2 * sizeof (*b));
    c = (float *)malloc (r1 * c2 * sizeof (*c));
    
    // transform to CuBLAS form
    for(j=0;j<c1;j++)
        for(i=0;i<r1;i++)
            a[IDX2C(i,j,r1)] = vector_ref(arg1,i*c1+j);
    
    for (j=0;j<c2;j++)
        for (i=0;i<r2;i++)
            b[IDX2C(i,j,r2)] = vector_ref(arg2,i*c2+j);
        
    // Initialize CUBLAS
    cublasInit();

    CUBLAS(cublasAlloc (r1*c1, sizeof(*a), (void**)&devPtrA));
    CUBLAS(cublasAlloc (r2*c2, sizeof(*b), (void**)&devPtrB));
    CUBLAS(cublasAlloc (r1*c2, sizeof(*c), (void**)&devPtrC));

    CUBLAS(cublasSetMatrix (r1, c1, sizeof(*a), a, r1, devPtrA, r1));
    CUBLAS(cublasSetMatrix (r2, c2, sizeof(*b), b, r2, devPtrB, r2));
    CUBLAS(cublasSetMatrix (r1, c2, sizeof(*c), c, r1, devPtrC, r1));


    //Sgemm
    cublasSgemm('N', 'N', r1, c2, c1, 1.0, devPtrA, r1, devPtrB, r2, 0.0, devPtrC, r1);


    CUBLAS(cublasGetMatrix (r1, c2, sizeof(*c), devPtrC, r1, c, r1));
 
    // Shutdown CUBLAS
    cublasFree(devPtrA);
    cublasFree(devPtrB);
    cublasFree(devPtrC);
    cublasShutdown();
    
    // Set matrix After sgemm
    for(j=0;j<c2;j++)
        for (i=0;i<r1;i++){
            vector_set(res,i*c2+j,c[IDX2C(i,j,r1)]);
        }
  
    return(res);

}

