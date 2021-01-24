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

#define CUBLAS(call)                                  \
{                                                     \
    const cublasStatus error = call;                  \
    if (error != CUBLAS_STATUS_SUCCESS)               \
    {                                                 \
        printf("cublas error %d",(int)error);         \
    }                                                 \
}


int f_gpu_mult(int arglist){
    int arg1,arg2,dim1,dim2,dim3,r1, c1, r2, c2, n, i, j, res;
    float *a,*b,*c;
    float* devPtrA;
    float* devPtrB;
    float* devPtrC;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    if(!IS_FARRAY(arg1))
        error(NOT_FARR,"gpu-mult",arg1);
    if(!IS_FARRAY(arg2))
        error(NOT_FARR,"gpu-mult",arg2);

    dim3 = list2(car(dim1),cadr(dim2));
    res = makefarray(dim3,0.0);
    r1 = GET_INT(car(dim1));
    c1 = GET_INT(cadr(dim1));
    r2 = GET_INT(car(dim2));
    c2 = GET_INT(cadr(dim2));
    if(c1 != r2)
        error(WRONG_ARGS,"gpu-mult", arglist);

    n = r1*c2;

    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(res);
    
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
    
    return(res);

}


int f_gpu_add(int arglist){
    int arg1,arg2,res,dim1,dim2,n;
    float *a,*b,*c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    if(!IS_FARRAY(arg1))
        error(NOT_FARR,"gpu-add",arg1);
    if(!IS_FARRAY(arg2))
        error(NOT_FARR,"gpu-add",arg2);
    if(!equalp(dim1,dim2))
        error(WRONG_ARGS,"gpu-add", arglist);
    res = makefarray(dim1,0.0);
    n = GET_INT(car(dim1)) * GET_INT(cadr(dim1));
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(res);

    cuda_add(a, b, c, n);
    return(res);
}



int f_gpu_sub(int arglist){
    int arg1,arg2,res,dim1,dim2,n;
    float *a,*b,*c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    if(!IS_FARRAY(arg1))
        error(NOT_FARR,"gpu-sub",arg1);
    if(!IS_FARRAY(arg2))
        error(NOT_FARR,"gpu-sub",arg2);
    if(!equalp(dim1,dim2))
        error(WRONG_ARGS,"gpu-sub", arglist);
    res = makefarray(dim1,0.0);
    n = GET_INT(car(dim1)) * GET_INT(cadr(dim1));
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(res);

    cuda_sub(a, b, c, n);
    return(res);
}


int f_gpu_smult(int arglist){
    int arg1,arg2,res,dim,n;
    float *a,*b, s;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim = GET_CDR(arg2);
    res = makefarray(dim,0.0);
    s = (float)GET_FLT(arg1);
    n = GET_INT(car(dim)) * GET_INT(cadr(dim));
    a = GET_FVEC(arg2);
    b = GET_FVEC(res);

    cuda_smult(s, n, a, b);
    return(res);
}

