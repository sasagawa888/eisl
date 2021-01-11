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


int mult1(int a_bin, int b_bin){
    int  c_bin;
    int r1, c1, r2, c2, n, i, j;
    float *a,*b,*c;
    float* devPtrA;
    float* devPtrB;
    float* devPtrC;

    n = r1*c2;
    //a = (float *) a_bin.data;
    //b = (float *) b_bin.data;
    //c = (float *) enif_make_new_binary(env, n * sizeof(float), &c_bin);

    for(j=0;j<c2;j++)
        for(i=0;i<r1;i++)
            c[IDX2C(i,j,r1)] = 0.0;


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
    

    return(c_bin);

}


int f_set_matmat(int arglist){
    int i,j,k,k1,m,m1,n,n1,arg1,arg2,arg3;
    cublasStatus stat;
    float* devPtrA;
    float* devPtrB;
    float* devPtrC;
    float* a = 0;
    float* b = 0;
    float* c = 0;
  
    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    m = GET_INT(car(GET_CDR(arg2)));
    k = GET_INT(cadr(GET_CDR(arg2)));
    k1 = GET_INT(car(GET_CDR(arg3)));
    n = GET_INT(cadr(GET_CDR(arg3)));
    m1 = GET_INT(car(GET_CDR(arg1)));
    n1 = GET_INT(cadr(GET_CDR(arg1)));
    if(m != m1 || k != k1 || n != n1)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    
    // Memory Allocation
    a = (float *)malloc (m * k * sizeof (*a));
    if (!a)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    b = (float *)malloc (m * k * sizeof (*b));
    if (!b)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    c = (float *)malloc (m * k * sizeof (*c));
    if (!c)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
        
    // Initalize
    for(j=0;j<k;j++)
        for(i=0;i<m;i++)
            a[IDX2C(i,j,m)] = GET_FLT(vector_ref(arg2,i*k+j));
    
    for (j=0;j<n;j++)
        for (i=0;i<k;i++)
            b[IDX2C(i,j,k)] = GET_FLT(vector_ref(arg3,i*n+j));
        
    for(j=0;j<n;j++)
        for(i=0;i<m;i++)
            c[IDX2C(i,j,m)] = 0.0;
            
    // Initialize CUBLAS
    cublasInit();

    stat = cublasAlloc (m*k, sizeof(*a), (void**)&devPtrA);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    stat = cublasAlloc (k*n, sizeof(*b), (void**)&devPtrB);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL); 
    stat = cublasAlloc (m*n, sizeof(*c), (void**)&devPtrC);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL); 
  

    stat = cublasSetMatrix (m, k, sizeof(*a), a, m, devPtrA, m);
    if(stat != CUBLAS_STATUS_SUCCESS)
    error(ILLEGAL_ARGS,"set-matmat",NIL);
    stat = cublasSetMatrix (k, n, sizeof(*b), b, k, devPtrB, k);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    stat = cublasSetMatrix (m, n, sizeof(*c), c, m, devPtrC, m);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL); 

  
    //Sgemm
    cublasSgemm('N', 'N', m, n, k, 1.0, devPtrA, m, devPtrB, k, 0.0, devPtrC, m);

    stat = cublasGetMatrix (m, n, sizeof(*c), devPtrC, m, c, m);
    if(stat != CUBLAS_STATUS_SUCCESS){
        cublasFree(devPtrA);
        cublasFree(devPtrB);
        cublasFree(devPtrC);
        cublasShutdown();
        error(ILLEGAL_ARGS,"set-matmat",NIL); 
    }

    // Shutdown CUBLAS
    cublasFree(devPtrA);
    cublasFree(devPtrB);
    cublasFree(devPtrC);
    cublasShutdown();

    // Set matrix After sgemm
    for(j=0;j<n;j++)
        for (i=0;i<m;i++){
            SET_TAG(vector_ref(arg1,i*n+j),FLTN);
            SET_FLT(vector_ref(arg1,i*n+j),c[IDX2C(i,j,m)]);
        }
  
    free(a);
    free(b);
    free(c);
    return(NIL);
}