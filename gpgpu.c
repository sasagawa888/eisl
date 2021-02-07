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
    if(!floatp(arg1))
        error(NOT_FLT,"gpu-smult",arg1);
    if(!IS_FARRAY(arg2))
        error(NOT_FARR,"gpu-smult",arg2);
    
    dim = GET_CDR(arg2);
    res = makefarray(dim,0.0);
    s = (float)GET_FLT(arg1);
    n = GET_INT(car(dim)) * GET_INT(cadr(dim));
    a = GET_FVEC(arg2);
    b = GET_FVEC(res);

    cuda_smult(s, n, a, b);
    return(res);
}

int f_gpu_emult(int arglist){
    int arg1,arg2,res,dim1,dim2,n;
    float *a,*b,*c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(!IS_FARRAY(arg1))
        error(NOT_FARR,"gpu-emult",arg1);
    if(!IS_FARRAY(arg2))
        error(NOT_FARR,"gpu-emult",arg2);
    
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    if(!equalp(dim1,dim2))
        error(WRONG_ARGS,"gpu-emult",list2(dim1,dim2));
    res = makefarray(dim1,0.0);
    n = GET_INT(car(dim1)) * GET_INT(cadr(dim1));
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(res);

    cuda_emult(n,a,b,c);
    return(res);
}


int f_gpu_pooling(int arglist){
    int arg1,arg2,res1,res2,dim1,dim2,in_n,in_c,in_h,in_w,st_h,st_w;
    float *a,*b, *c;

    arg1 = car(arglist);   //farray
    arg2 = cadr(arglist);  //stride-list (st_h,st_w)
    if(!IS_FARRAY(arg1))
        error(NOT_FARR,"gpu-pooling",arg1);
    if(!listp(arg2))
        error(NOT_LIST,"gpu-pooling",arg2);
    dim1 = GET_CDR(arg1);
    if(length(dim1) != 4)
        error(WRONG_ARGS,"gpu-pooling",arg1);
    if(length(arg2) != 2)
        error(WRONG_ARGS,"gpu-pooling",arg2);
    
    in_n = GET_INT(nth(0,dim1));
    in_c = GET_INT(nth(1,dim1));
    in_h = GET_INT(nth(2,dim1));
    in_w = GET_INT(nth(3,dim1));
    st_h = GET_INT(nth(0,arg2));
    st_w = GET_INT(nth(1,arg2));

    dim2 = list4(nth(0,dim1),nth(1,dim1),makeint(in_h/st_h),makeint(in_w/st_w));
    res1 = makefarray(dim2,0.0);
    res2 = makefarray(dim2,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(res1);
    c = GET_FVEC(res2);

    cuda_pooling(in_n,in_c,in_h,in_w,a,b,c,st_h,st_w);
    return(list2(res1,res2));
}

int f_gpu_unpooling(int arglist){
    int arg1,arg2,arg3,res,dim1,dim2,dim3,in_n,in_c,in_h,in_w,st_h,st_w;
    float *a,*b, *c;

    arg1 = car(arglist);   //farray1
    arg2 = cadr(arglist);  //farray2
    arg3 = cadr(arglist);  //stride-list (st_h,st_w)
    if(!IS_FARRAY(arg1))
        error(NOT_FARR,"gpu-unpooling",arg1);
    if(!IS_FARRAY(arg2))
        error(NOT_FARR,"gpu-unpooling",arg2);    
    if(!listp(arg3))
        error(NOT_LIST,"gpu-unpooling",arg2);
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    if(length(dim1 != 4))
        error(WRONG_ARGS,"gpu-unpooling",arg1);
    if(length(dim1 != 4))
        error(WRONG_ARGS,"gpu-unpooling",arg1);
    if(!equalp(dim1,dim2))
        error(WRONG_ARGS,"gpu-unpooling",list2(dim1,dim2));
    if(length(arg3 != 2))
        error(WRONG_ARGS,"gpu-unpooling",arg3);
    
    in_n = GET_INT(nth(0,dim1));
    in_c = GET_INT(nth(1,dim1));
    in_h = GET_INT(nth(2,dim1));
    in_w = GET_INT(nth(3,dim1));
    st_h = GET_INT(nth(0,arg2));
    st_w = GET_INT(nth(1,arg2));

    dim3 = list4(nth(dim1,0),nth(dim1,1),makeint(in_h*st_h),makeint(in_w*st_w));
    res = makefarray(dim3,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(res);

    cuda_unpooling(in_n,in_c,in_h,in_w,a,b,c,st_h,st_w);
}


/*
1st arg input tensor
2nd arg filter tensor
3rd arg stride list
4th arg padding size
*/
int f_gpu_convolute(int arglist){
    int arg1,arg2,arg3,arg4,dim1,dim2,dim3,in_n,in_c,in_h,in_w,filt_n,filt_c,filt_h,filt_w,st_h,st_w,pad,oh,ow,res;
    float *a,*b,*c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    arg4 = cadddr(arglist);
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    in_n = GET_INT(nth(0,dim1));
    in_c = GET_INT(nth(1,dim1));
    in_h = GET_INT(nth(2,dim1));
    in_w = GET_INT(nth(3,dim1));
    filt_n = GET_INT(nth(0,dim2));
    filt_c = GET_INT(nth(1,dim2));
    filt_h = GET_INT(nth(2,dim2));
    filt_w = GET_INT(nth(3,dim2));
    st_h = GET_INT(nth(0,arg3));
    st_w = GET_INT(nth(1,arg3));
    pad = GET_INT(arg4);

    oh = (in_h+2*pad-filt_h)/st_h + 1;
    ow = (in_w+2*pad-filt_w)/st_w + 1;
    dim3 = list4(makeint(in_n),makeint(filt_n),makeint(oh),makeint(ow));
    res = makefarray(dim3,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(res);

    cuda_convolute(in_n,in_c,in_h,in_w,filt_n,filt_c,filt_h,filt_w,a,b,c,st_h,st_w,pad);
    return(res);
}
  

 //void deconvolute1(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w,
 //                  float *a, float *b, float *c, int st_h, int st_w, int pad){ 
/*
1st arg input loss tensor
2nd arg filter tensor
3rd arg stride list
4th arg padding size
*/
int f_gpu_deconvolute(int arglist){
    int arg1,arg2,arg3,arg4,dim1,dim2,dim3,in_n,in_c,in_h,in_w,filt_n,filt_c,filt_h,filt_w,st_h,st_w,pad,res,
        oh,ow,oh1,ow1,pad1;
    float *a,*b,*c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    arg4 = cadddr(arglist);
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    in_n = GET_INT(nth(0,dim1));
    in_c = GET_INT(nth(1,dim1));
    in_h = GET_INT(nth(2,dim1));
    in_w = GET_INT(nth(3,dim1));
    filt_n = GET_INT(nth(0,dim2));
    filt_c = GET_INT(nth(1,dim2));
    filt_h = GET_INT(nth(2,dim2));
    filt_w = GET_INT(nth(3,dim2));
    st_h = GET_INT(nth(0,arg3));
    st_w = GET_INT(nth(1,arg3));
    pad = GET_INT(arg4);
    pad1 = filt_h - 1;
    // pad1 = filt_h -1,  pad is original padding size
    oh = (in_h+2*pad1-filt_h)/st_h + 1;
    ow = (in_w+2*pad1-filt_w)/st_w + 1;
    oh1 = (in_h+2*(pad1-pad)-filt_h)/st_h + 1;
    ow1 = (in_w+2*(pad1-pad)-filt_w)/st_w + 1;
    dim3 = list4(makeint(in_n),makeint(filt_c),makeint(oh1),makeint(ow1));
    res = makefarray(dim3,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(res);

    if(st_h == 1 && st_w == 1)
        cuda_deconvolute2(in_n,in_c,in_h,in_w,filt_n,filt_c,filt_h,filt_w,a,b,c,st_h,st_w,pad);
    else    
        cuda_deconvolute1(in_n,in_c,in_h,in_w,filt_n,filt_c,filt_h,filt_w,a,b,c,st_h,st_w,pad);

    return(res);
}


int f_gpu_activate(int arglist){
    int arg1,arg2,dim1,temp,n,res,r1,c1;
    float *a,*b;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim1 = GET_CDR(arg1);
    r1 = GET_INT(nth(0,dim1));
    c1 = GET_INT(nth(1,dim1));

    temp = dim1;
    n = 1;
    while(!nullp(temp)){
        n = n * GET_INT(car(temp));
        temp = cdr(temp);
    }
    res = makefarray(dim1,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(res);
    if(arg2 == makesym("SIGMOID")){
        cuda_activate_sigmoid(n,a,b);
    }
    else if(arg2 == makesym("TANH")){
        cuda_activate_tanh(n,a,b);
    }
    else if(arg2 == makesym("RELU")){
        cuda_activate_relu(n,a,b);
    }
    else if(arg2 == makesym("SOFTMAX")){
        cuda_activate_softmax(r1,c1,a,b);
    }
    else
        error(WRONG_ARGS,"gpu-activate",arg2);

    return(res);

}

int f_gpu_diff(int arglist){
    int arg1,arg2,dim1,dim2,n,temp,res;
    float *a,*b,*c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);

    temp = dim1;
    n = 1;
    while(!nullp(temp)){
        n = n * GET_INT(car(temp));
        temp = cdr(temp);
    }
    res = makefarray(dim1,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(res);
    if(arg2 == makesym("SIGMOID")){
        cuda_differ_sigmoid(n,a,b,c);
    }
    else if(arg2 == makesym("TANH")){
        cuda_differ_tanh(n,a,b,c);
    }
    else if(arg2 == makesym("RELU")){
        cuda_differ_relu(n,a,b,c);
    }
   
   return(res);
}

int f_gpu_gradfilter(int arglist){
    int arg1,arg2,arg3,arg4,arg5,dim1,dim2,dim3,in_n,in_c,in_h,in_w,filt_n,filt_c,filt_h,filt_w,
        loss_n,loss_c,loss_h,loss_w,st_h,st_w,pad,res;
    float *a,*b,*d;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    arg4 = nth(3,arglist);
    arg5 = nth(4,arglist);

    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    dim3 = GET_CDR(arg3);
    in_n = GET_INT(nth(0,dim1));
    in_c = GET_INT(nth(1,dim1));
    in_h = GET_INT(nth(2,dim1));
    in_w = GET_INT(nth(3,dim1));
    filt_n = GET_INT(nth(0,dim2));
    filt_c = GET_INT(nth(1,dim2));
    filt_h = GET_INT(nth(2,dim2));
    filt_w = GET_INT(nth(3,dim2));
    loss_n = GET_INT(nth(0,dim3));
    loss_c = GET_INT(nth(1,dim3));
    loss_h = GET_INT(nth(2,dim3));
    loss_w = GET_INT(nth(3,dim3));
    st_h = GET_INT(nth(0,arg4));
    st_w = GET_INT(nth(1,arg4));
    pad = GET_INT(arg5);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    res = makefarray(dim2,0.0);
    d = GET_FVEC(res);
    
    if(st_h == 1 && st_w == 1)
        cuda_gradfilter1(in_n,in_c,in_h,in_w,filt_n,filt_c,filt_h,filt_w,loss_c,loss_h,loss_w,a,b,d,st_h,st_w,pad);
    else
        cuda_gradfilter2(in_n,in_c,in_h,in_w,filt_n,filt_c,filt_h,filt_w,loss_c,loss_h,loss_w,a,b,d,st_h,st_w,pad);
    
    return(res);
}

int f_gpu_full(int arglist){
    int arg1,dim1,dim2,in_n,in_c,in_h,in_w,res;
    float *a,*b;

    arg1 = car(arglist);
    dim1 = GET_CDR(arg1);
    in_n = GET_INT(nth(0,dim1));
    in_c = GET_INT(nth(1,dim1));
    in_h = GET_INT(nth(2,dim1));
    in_w = GET_INT(nth(3,dim1));
    dim2 = list2(nth(0,dim1),makeint(in_c*in_h*in_w));

    res = makefarray(dim2,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(res);
    cuda_full(in_n,in_c,in_h,in_w,a,b);
    return(res);
}

int f_gpu_unfull(int arglist){
    int arg1,arg2,arg3,arg4,dim1,dim2,r,in_n,in_c,in_h,in_w,res;
    float *a,*b;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    arg4 = cadddr(arglist);
    dim1 = GET_CDR(arg1);
    r = GET_INT(nth(0,dim1));
    in_c = GET_INT(arg2);
    in_h = GET_INT(arg3);
    in_w = GET_INT(arg4);
    dim2 = list4(makeint(r),makeint(in_c),makeint(in_h),makeint(in_w));

    res = makefarray(dim2,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(res);
    cuda_full(r,in_c,in_h,in_w,a,b);
    return(res);
}


int f_gpu_dropout(int arglist){
    int arg1,arg2,dim1,n,temp,res;
    float *a,*b,dropout_rate;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim1 = GET_CDR(arg1);
    dropout_rate = (float)GET_FLT(arg2);
    
    temp = dim1;
    n = 1;
    while(!nullp(temp)){
        n = n * GET_INT(car(temp));
        temp = cdr(temp);
    } 
    res = makefarray(dim1,0.0);
    a = GET_FVEC(res);
    cuda_dropout(n,dropout_rate,a);
    return(res);
}

int f_gpu_sgd(int arglist){
    int arg1,arg2,arg3,dim1,dim2,temp,n,res;
    float lr,*a,*b,*c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    lr = (float)GET_FLT(arg3);

    temp = dim1;
    n = 1;
    while(!nullp(temp)){
        n = n * GET_INT(car(temp));
        temp = cdr(temp);
    }
    res = makefarray(dim1,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(res);
    cuda_sgd(n,a,b,c,lr);
    return(res);
}



int f_gpu_momentum(int arglist){
    int arg1,arg2,arg3,arg4,dim1,dim2,dim3,temp,n,res1,res2;
    float lr,*a,*b,*c,*d,*e;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    arg4 = cadddr(arglist);
    
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    dim3 = GET_CDR(arg3);
    lr = (float)GET_FLT(arg4);

    temp = dim1;
    n = 1;
    while(!nullp(temp)){
        n = n * GET_INT(car(temp));
        temp = cdr(temp);
    }
    res1 = makefarray(dim1,0.0);
    res2 = makefarray(dim1,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(arg3);
    d = GET_FVEC(res1);
    e = GET_FVEC(res2);
    /*
    1st arg row-size of vectorized each-matrix
    2nd arg wight-matrix    (a)
    3rd arg v-matrix        (b)
    4th arg gradient-matrix (c)
    5th arg output next_v-matrix (d)
    6th arg output weight_matrix (e)
    7th arg learning rate
    */
    cuda_momentum(n,a,b,c,d,e,lr);
    return(list2(res1,res2));
}


int f_gpu_adagrad(int arglist){
    int arg1,arg2,arg3,arg4,dim1,dim2,dim3,temp,n,res1,res2;
    float lr,*a,*b,*c,*d,*e;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    arg4 = cadddr(arglist);
    
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    dim3 = GET_CDR(arg3);
    lr = (float)GET_FLT(arg4);

    temp = dim1;
    n = 1;
    while(!nullp(temp)){
        n = n * GET_INT(car(temp));
        temp = cdr(temp);
    }
    res1 = makefarray(dim1,0.0);
    res2 = makefarray(dim1,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(arg3);
    d = GET_FVEC(res1);
    e = GET_FVEC(res2);
    /*
    1st arg row-size of vectorized each-matrix
    2nd arg wight-matrix (a)
    3rd arg h-matrix     (b)
    4th arg grad-matrix  (c)
    5th arg output new-h (d)
    6th arg output new-w (e)
    7th arg learning rate
    */
    cuda_momentum(n,a,b,c,d,e,lr);
    return(list2(res1,res2));
}


int f_gpu_rms(int arglist){
    int arg1,arg2,arg3,arg4,dim1,dim2,dim3,temp,n,res1,res2;
    float lr,*a,*b,*c,*d,*e;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    arg4 = cadddr(arglist);
    
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    dim3 = GET_CDR(arg3);
    lr = (float)GET_FLT(arg4);

    temp = dim1;
    n = 1;
    while(!nullp(temp)){
        n = n * GET_INT(car(temp));
        temp = cdr(temp);
    }
    res1 = makefarray(dim1,0.0);
    res2 = makefarray(dim1,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(arg3);
    d = GET_FVEC(res1);
    e = GET_FVEC(res2);
    /*
    1st arg row-size of vectorized each-matrix
    2nd arg wight-matrix (a)
    3rd arg h-matrix     (b)
    4th arg grad-matrix  (c)
    5th arg output new-h (d)
    6th arg output new-w (e)
    7th arg learning rate
    */
    cuda_rms(n,a,b,c,d,e,lr);
    return(list2(res1,res2));
}

int f_gpu_adam(int arglist){
    int arg1,arg2,arg3,arg4,arg5,dim1,dim2,dim3,dim4,temp,n,res1,res2,res3;
    float lr,*a,*b,*c,*d,*e,*f,*g;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    arg4 = cadddr(arglist);
    
    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    dim3 = GET_CDR(arg3);
    lr = (float)GET_FLT(arg4);

    temp = dim1;
    n = 1;
    while(!nullp(temp)){
        n = n * GET_INT(car(temp));
        temp = cdr(temp);
    }
    res1 = makefarray(dim1,0.0);
    res2 = makefarray(dim1,0.0);
    res3 = makefarray(dim1,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    c = GET_FVEC(arg3);
    d = GET_FVEC(arg4);
    e = GET_FVEC(res1);
    f = GET_FVEC(res2);
    g = GET_FVEC(res3);
    /*
    1st arg row-size of vectorized each-matrix
    2nd arg w-matrix     (a)
    3rd arg m-matrix     (b)
    4th arg v-matrix     (c)
    5th arg grad-matrix  (d)
    6th arg output m1    (e)
    7th arg output v1    (f)
    8th arg output w1    (g)
    9th arg learning rate
    */
    cuda_adam(n,a,b,c,d,e,f,g,lr);
    return(list3(res1,res2,res3));
}



int f_gpu_transpose(int arglist){
    int arg1,i,j,r1,c1,dim1,dim2,res;
    float *a,*b;

    arg1 = car(arglist);
    dim1 = GET_CDR(arg1);
    dim2 = reverse(dim1);
    r1 = GET_INT(nth(0,dim1));
    c1 = GET_INT(nth(1,dim1));
    res = makefarray(dim2,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(res);
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++){
            b[IDX2C(j,i,c1)] = a[IDX2C(i,j,r1)];
        }
    }
    return(res);
}


int f_gpu_ident(int arglist){
    int arg1,dim1,n,i,j,res;
    float *a;

    arg1 = car(arglist);
    dim1 = list2(arg1,arg1);
    n = GET_INT(arg1);

    res = makefarray(dim1,0.0);
    a = GET_FVEC(res);
    // Set matrix data 
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j)
                a[IDX2C(i,j,n)] = 1.0;
            else
                a[IDX2C(i,j,n)] = 0.0;
        }
    }
    return(res);
}


 
int f_gpu_trace(int arglist){
    int arg1,dim1,i, j,r1,c1,res;
    float *a,trace;

    arg1 = car(arglist);
    dim1 = GET_CDR(arg1);
    r1 = GET_INT(nth(0,dim1));
    c1 = GET_INT(nth(1,dim1));
    a = GET_FVEC(arg1);
    trace = 0.0;
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++){
            if(i==j)
                trace = trace + a[IDX2C(i,j,r1)];
        }
    }

    return(makeflt((double)trace));
}

int f_gpu_loss(int arglist){
    int arg1,arg2,arg3,dim1,dim2,i,j,r1,c1;
    float d,s,delta,*a,*b;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);

    dim1 = GET_CDR(arg1);
    dim2 = GET_CDR(arg2);
    a = GET_FVEC(arg1);
    b = GET_FVEC(arg2);
    r1 = GET_INT(nth(0,dim1));
    c1 = GET_INT(nth(1,dim1));

    if(arg3 == makesym("SQUARE")){
        s = 0.0;
        for(i=0;i<r1;i++){
            for (j=0;j<c1;j++){
                d = a[IDX2C(i,j,r1)] -  b[IDX2C(i,j,r1)];
                s = s + d*d;            
            }
        } 
        s = s / (2.0*(float)(r1));
        return(makeflt((double)s));
    }
    else if(arg3 == makesym("CROSS")){
        delta = 1e-7;
        s = 0.0;
        for(i=0;i<r1;i++){
            for (j=0;j<c1;j++){
            d = a[IDX2C(i,j,r1)] + delta;
            s = s + b[IDX2C(i,j,r1)] * log(d);
            }
        }
        s = -1.0 * s / (float)r1;
        return(makeflt((double)s));
    }
    else
        error(WRONG_ARGS,"gpu-loss",arg3);
}


int f_gpu_average(int arglist){
    int arg1,dim1,dim2,i,j,r1,c1,res;
    float *a,*b,sum;

    arg1 = car(arglist);
    dim1 = GET_CDR(arg1);
    dim2 = list2(makeint(1),nth(1,dim1));
    res = makefarray(dim2,0.0);
    a = GET_FVEC(arg1);
    b = GET_FVEC(res);
    r1 = GET_INT(nth(0,dim1));
    c1 = GET_INT(nth(1,dim1));
    for(j=0;j<c1;j++){
        sum = 0.0;
        for(i=0;i<r1;i++){
            sum = sum + a[IDX2C(i,j,r1)];
        }
        b[j] = sum / (float)r1;
    }
    return(res);
}


int f_gpu_sum(int arglist){
    int arg1,dim1,i,j,r1,c1;
    float *a,sum;

    arg1 = car(arglist);
    dim1 = GET_CDR(arg1);
    a = GET_FVEC(arg1);
    r1 = GET_INT(nth(0,dim1));
    c1 = GET_INT(nth(1,dim1));

    sum = 0.0;
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++){
            sum = sum + a[IDX2C(i,j,r1)];
        }
    }

    return(makeflt((double)sum));
}



/*
calculate accuracy
1st arg predicted matrix
2nd arg list of label. each element is integer
return accuracy rate
*/
  
int f_gpu_accuracy(int arglist){
    int arg1,arg2,dim,r1,c1,i,j,n,index,sum;
    float *a;
    double max,rate;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim = GET_CDR(arg1);
    r1 = GET_INT(car(dim));
    c1 = GET_INT(cadr(dim));
      
	sum = 0;
	for(i=0;i<r1;i++){
        max = 0.0;
        n = GET_INT(car(arg2));
        arg2 = cdr(arg2);
		for(j=0;j<c1;j++){
			if(a[IDX2C(i,j,r1)] > max){
				max = a[IDX2C(i,j,r1)];
				index = j;
			}
		}
		if(index == n)
			sum++;
	}
	rate = (double)sum / (double)r1;
	return(makeflt(rate));
  }
  
/*
calculate correct number
1st arg predicted matrix
2nd arg list of label. each element is integer
return correct number
*/

int f_gpu_correct(int arglist){
    int arg1,arg2,dim,r1,c1,i,j,n,index,sum;
    float *a;
	double max;
      
    arg1 = car(arglist);
    arg2 = cadr(arglist);
    dim = GET_CDR(arg1);
    r1 = GET_INT(car(dim));
    c1 = GET_INT(cadr(dim));
	  
	sum = 0;
	for(i=0;i<r1;i++){
        max = 0.0;
        n = GET_INT(car(arg2));
        arg2 = cdr(arg2);
		for(j=0;j<c1;j++){
			if(a[IDX2C(i,j,r1)] > max){
				max = a[IDX2C(i,j,r1)];
				index = j;
			}
		}
		if(index == n)
			sum++;
	}
  
	return(makeflt((double)sum));
  }
  
   /*
  random_select for matrix data
  1st arg row of matrix a
  2nd arg col of matrix a
  3rd arg matrix a
  4th arg row ob matrix b
  5th arg col of matrix b
  6th arg matrix b
  7th arg count of select
  8th arg output random selected a
  9th arg output random selected b 
  */
  
  void random_select1(int r1, int c1, float *a, int r2, int c2, float *b, int n, float *c, float *d){
	  int i, j, r;
	
	
	  // random-select
	  for(i=0;i<n;i++){
		  r = rand() % r1;
		  for(j=0;j<c1;j++){
			  c[IDX2C(i,j,n)] = a[IDX2C(r,j,r1)];
		  }
		  for(j=0;j<c2;j++){
			  d[IDX2C(i,j,n)] = b[IDX2C(r,j,r2)];
		  }    
	  }
  
  }
  


 
  /*
  random_select for 4D-tensor data
  1st arg nth of matrix a
  2nd arg channel of matrix a
  3rd arg hight of matrix a
  4th arg width of matrix a
  5th arg matrix a
  6th arg row ob matrix b
  7th arg col of matrix b
  8th arg matrix b
  9th arg count of select
  10th arg output random selected a
  11th arg output random selected b
  */
  
  void random_select2(int n1, int c1, int h1, int w1, float *a, int r2, int c2, float *b, int n, float *c, float *d){
	  int i, j, k, l, r;
	
	  // random-select
	  for(i=0;i<n;i++){
		  r = rand() % n1;
		  for(j=0;j<c1;j++){
			  for(k=0;k<h1;k++){
				  for(l=0;l<w1;l++){
					  c[IDX4C(i,j,k,l,c1,h1,w1)] = a[IDX4C(r,j,k,l,c1,h1,w1)];
				  }
			  }
		  }
		  for(j=0;j<c2;j++){
			  d[IDX2C(i,j,n)] = b[IDX2C(r,j,r2)];
		  }    
	  }
  
  }
  


  /*
  random_select for 3D-tensor data
  1st arg nth of matrix a
  2nd arg hight of matrix a
  3rd arg width of matrix a
  4th arg matrix a
  5th arg row ob matrix b
  6th arg col of matrix b
  7th arg matrix b
  8th arg count of select
  9th arg output random selected a
  10th arg output random selected b
  */
  
  void random_select3(int n1, int h1, int w1, float *a, int r2, int c2, float *b, int n, float *c, float *d){
	  int i, j, k, r;
	  
	  // random-select
	  for(i=0;i<n;i++){
		  r = rand() % n1;
		  for(j=0;j<h1;j++){
			  for(k=0;k<w1;k++){
				  c[IDX3C(i,j,k,h1,w1)] = a[IDX3C(r,j,k,h1,w1)];
			  }
		  }
		  for(j=0;j<c2;j++){
			  d[IDX2C(i,j,n)] = b[IDX2C(r,j,r2)];
		  }    
	  }	 
  }
  
  /*
  1st arg count of data
  2nd arg input1
  3rd arg intpu2
  */
  int is_near1(int n, float *a, float *b){
	  int i, sw;
	
	  // near check
	  sw = 0;
	  for(i=0;i<n;i++){
		 if(fabsf(a[i]) > fabsf(b[i])*1.15 || fabsf(a[i]) < fabsf(b[i])*0.85){
			  printf("%f %f \r\n", a[i], b[i]);
			  sw = 1;
		  }
	  }
	  if(sw == 0)
		  return(1); //true
	  else
		  return(0); //false
  }
  
  


  int is_equal1(int n, float *a, float *b){
	  int i;
	 
	  // equal check
	  for(i=0;i<n;i++){
		 if(a[i] != b[i]){
			  return(0); //false
		  }
	  }
	  
	  return(1); //true
  }
  
  
  int analizer1(int n, float *a, int id){
	  int i;
	  float max,min,sum;
	
	  
	  // near check
	  for(i=0;i<n;i++){
		  if(isnan(a[i])){
			  return(9999);
		  }
		  if(isinf(a[i])){
			  return(9998);
		  }
	  }
  
	  //find max min avarage
	  max = -999999999;
	  min = 999999999;
	  sum = 0;
	  for(i=0;i<n;i++){
		  if(a[i] > max)
			  max = a[i];
		  
		  if(a[i] < min)
			  min = a[i];
		  
		  sum = sum+a[i];
  
	  }
	  printf("id max min average\r\n");
	  printf("%d %f %f %f \r\n", id, max, min, sum/(float)n);
  
	  return(1);
  }
  
  

  
	
	/*
	1st arg in_n of tensor
	2nd arg in_c of tensor
	3rd arg in_h of tensor
	4th arg in_w of tensor
	5th arg input tensor
	6th arg output tensor
	*/

  void standardize1(int in_n, int in_c, int in_h, int in_w, float *a, float *b){
	  int n1,i,c1,h1,w1,count;
	  float sum,average;
	
	  n1 = in_n * in_c * in_h * in_w;
	  
	  for(i=0;i<in_n;i++){
		  sum = 0.0;
		  for(c1=0;c1<in_c;c1++){
			  for(h1=0;h1<in_h;h1++){
				  for(w1=0;w1<in_w;w1++){
					  sum = sum + a[IDX4C(i,c1,h1,w1,in_c,in_h,in_w)];
				  }
			  }
		  }
		  count = in_c * in_h * in_w;
		  average = sum / (float)count;
		  for(c1=0;c1<in_c;c1++){
			  for(h1=0;h1<in_h;h1++){
				  for(w1=0;w1<in_w;w1++){
					  b[IDX4C(i,c1,h1,w1,in_c,in_h,in_w)] = a[IDX4C(i,c1,h1,w1,in_c,in_h,in_w)] - average;
				  }
			  }
		  }
	  }
	  
  }
  

  /*
  1st arg in_n of 3D tensor
  2rd arg in_r of 3D tensor
  3th arg in_c of 3D tensor
  4th arg input tensor
  5th arg nth in_r of 3D tensor
  6th arg output tensor
  */
  
  void pickup1(int in_n, int in_row, int in_col, float *a, int nth, float *b){
	  int n1,i,j;
	  

	  for(i=0;i<in_n;i++){
		  for(j=0;j<in_col;j++){
			  b[IDX2C(i,j,in_n)] = a[IDX3C(i,nth,j,in_row,in_col)];
		  }
	  }
		
  }
	
  
  	
  /*
  1st arg size of tensor or matrix
  2rd arg input tensor or matrix
  3rd arg output 	
  */
  
  void copy1(int n, float *a, float *b){
	  int i;
	  
	  for(i=0;i<n;i++){
		  b[i] = a[i];
	  }
	
  }
  
  /*
  1st arg row 
  2nd arg col
  3rd arg input tensor
  4th arg output1
  5th arg output2
  6th arg output3
  7th arg output4
  */

  void slice1(int in_r, int in_c, float *a, float *b, float *c, float *d, float *e){
	  int in_c1,i,j,n,bias;


	  in_c1 = in_c / 4;
	  n = in_r * (in_c / 4);
	  
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c1;j++){
			  b[IDX2C(i,j,in_r)] = a[IDX2C(i,j,in_r)]; 
		  }
	  }
	  bias = in_c / 4;
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c1;j++){
			  c[IDX2C(i,j,in_r)] = a[IDX2C(i,j+bias,in_r)]; 
		  }
	  }
	  bias = 2 * (in_c / 4);
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c1;j++){
			  d[IDX2C(i,j,in_r)] = a[IDX2C(i,j+bias,in_r)]; 
		  }
	  }
	  bias = 3 * (in_c / 4);
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c1;j++){
			  e[IDX2C(i,j,in_r)] = a[IDX2C(i,j+bias,in_r)]; 
		  }
	  }
		
	 
  }
  

  /*
  1st arg row 
  2nd arg col
  3rd arg output tensor
  4th arg input1
  5th arg input2
  6th arg input3
  7th arg input4
  */
  
  void unslice1(int in_r, int in_c, float *a, float *b, float *c, float *d, float *e){
	  int i,j,n,bias;
	
	  n = in_r * in_c * 4;
	  
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c;j++){
			  a[IDX2C(i,j,in_r)] = b[IDX2C(i,j,in_r)];
		  }
	  }
	  bias = in_c;
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c;j++){
			  a[IDX2C(i,j+bias,in_r)] = c[IDX2C(i,j,in_r)]; 
		  }
	  }
	  bias = 2 * in_c;
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c;j++){
			  a[IDX2C(i,j+bias,in_r)] = d[IDX2C(i,j,in_r)] ; 
		  }
	  }
	  bias = 3 * in_c;
	  for(i=0;i<in_r;i++){
		  for(j=0;j<in_c;j++){
			  a[IDX2C(i,j+bias,in_r)] = e[IDX2C(i,j,in_r)]; 
		  }
	  }
	  
  }
  
  
  
