#include <cuda.h>
#include <stdio.h>

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
        printf("cuda error %d",(int)error);           \
    }                                                 \
}

extern "C" void cuda_add(float *a, float *b, float *c, int n);
extern "C" void cuda_sub(float *a, float *b, float *c, int n);
extern "C" void cuda_smult(float s, int n, float *a, float *b);
extern "C" void cuda_pooling(int in_n, int in_c, int in_h, int in_w, float *a, float *b, float *c, int st_h, int st_w);
extern "C" void cuda_unpooling(int in_n, int in_c, int in_h, int in_w, float *a, float *b, float *c,int st_h, int st_w);
extern "C" void cuda_convolute(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w, float *a, float *b, float *c,
    int st_h, int st_w, int pad);
extern "C" void cuda_deconvolute1(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w,
    float *a, float *b, float *c, int st_h, int st_w, int pad);
extern "C" void cuda_deconvolute2(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w,
        float *a, float *b, float *c, int st_h, int st_w, int pad);
extern "C" void cuda_gradfilter1(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w, 
    int loss_c, int loss_h, int loss_w, float *a, float *b, float *d, int st_h, int st_w, int pad);
extern "C" void cuda_gradfilter2(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w, 
    int loss_c, int loss_h, int loss_w, float *a, float *b, float *d, int st_h, int st_w, int pad);
extern "C" void cuda_emult(int n, float *a, float *b,float *c);
extern "C" void cuda_full(int in_n, int in_c, int in_h, int in_w, float *a, float *b);
extern "C" void cuda_unfull(int in_n, int in_c, int in_h, int in_w, float *a, float *b);
extern "C" void cuda_activate_sigmoid(int n, float *a, float *b);
extern "C" void cuda_activate_tanh(int n, float *a, float *b);
extern "C" void cuda_activate_relu(int n, float *a, float *b);
extern "C" void cuda_activate_softmax(int r1, int c1, float *a, float *b);
extern "C" void cuda_differ_sigmoid(int n, float *a, float *b, float *c);
extern "C" void cuda_differ_tanh(int n, float *a, float *b, float *c);
extern "C" void cuda_differ_relu(int n, float *a, float *b, float *c);
extern "C" void cuda_dropout(int n, float dropout_rate, float *a);

__global__ void add1_kernel(float *a, float *b, float *c, int n)
{
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	while (tid < n)
	{
		c[tid] = a[tid] + b[tid];
		tid += blockDim.x * gridDim.x;
	}
}

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




__global__ void sub1_kernel(float *a, float *b, float *c, int n)
{
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	while (tid < n)
	{
		c[tid] = a[tid] - b[tid];
		tid += blockDim.x * gridDim.x;
	}
}


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




__global__ void smult_kernel(float d, float *a, float *b, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {
        b[tid] = d * a[tid];
        tid += blockDim.x * gridDim.x;
    }
}



void cuda_smult(float s, int n, float *a, float *b){
    float *dev_a, *dev_b;

    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

    smult_kernel << <128, 128 >> >(s,dev_a, dev_b, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(b, dev_b, n * sizeof(float), cudaMemcpyDeviceToHost));

    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);

}


__global__ void pooling_kernel(float *a, float *b, float *c, int st_h, int st_w, int in_c, int in_h, int in_w)
{
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    int n1,c1,h1,w1,h2,w2,in_h2,in_w2,start_h1,end_h1,start_w1,end_w1,max_h,max_w;
    float max,fmax_h,fmax_w; 
    n1 = bid;
    c1 = tid;
    in_h2 = in_h / st_h;
    in_w2 = in_w / st_w;
    
    for(w2=0;w2<in_w2;w2++){
        for(h2=0;h2<in_h2;h2++){
            max = -999999999.0;
            start_h1 = st_h*h2;
            end_h1 = st_h*(h2+1);
            start_w1 = st_w*w2;
            end_w1 = st_w*(w2+1);
            for(h1=start_h1;h1<end_h1;h1++){
                for(w1=start_w1;w1<end_w1;w1++){
                    if(a[IDX4C(n1,c1,h1,w1,in_c,in_h,in_w)] >= max){
                        max = a[IDX4C(n1,c1,h1,w1,in_c,in_h,in_w)];
                        max_h = h1;
                        max_w = w1;
                    }
                }
            }
            b[IDX4C(n1,c1,h2,w2,in_c,in_h2,in_w2)] = max;
            fmax_h = (float)max_h;
            fmax_w = (float)max_w;
            c[IDX4C(n1,c1,h2,w2,in_c,in_h2,in_w2)] = fmax_h * 1000.0 + fmax_w; 
        }
    }
    
}
  
  /*
  1st arg in_n of tensor
  2nd arg in_c of tensor
  3rd arg in_h of tensor
  4th arg in_w of tensor
  5th arg input tensor
  6th arg output tensor (forward result)
  7th arg output tensor (backward result)
  8th arg stride hight
  9th arg stride width

  return list [ts1,ts2]
  ts1 is result data for forward
  ts2 is result data dor backward. this is sparse matrix 
  e.g. 
  |0.1,0.2,0.3,0.4|
  |0.5,0.6,0.7,0.8|
  |0.9,1.0,1.1,1.2|
  |1.3,1.4,1.5,1.6|
  
  ts1
  |0.6,0.8|
  |1.4,1.6|

  ts2
  each element is  row*1000+col
  |1.0*1000+1.0,1.0*1000*3.0|
  |3.0*1000+1.0,3.0*1000+3.0|
  
  */
  
  void cuda_pooling(int in_n, int in_c, int in_h, int in_w, float *a, float *b, float *c, int st_h, int st_w){
	  int n1, n2;
	  float *dev_a, *dev_b, *dev_c;
	
	  
	  n1 = in_n * in_c * in_h * in_w;
	  n2 = in_n * in_c * (in_h / st_h) * (in_w / st_w);
	  
	  // Allocate for GPU
	  CHECK(cudaMalloc((void**)&dev_a, n1 * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_b, n2 * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_c, n2 * sizeof(float)));
	
	  // copy from host a to GPU dev_a
	  CHECK(cudaMemcpy(dev_a, a, n1 * sizeof(float), cudaMemcpyHostToDevice));
	  
	  dim3 blocks(in_n,1,1);
	  dim3 threads(in_c,1,1);
	  pooling_kernel <<<blocks, threads>>>(dev_a, dev_b, dev_c, st_h, st_w, in_c, in_h, in_w);
	
	  // copy to host b,c from GPU dev_b,dev_c
	  CHECK(cudaMemcpy(b, dev_b, n2 * sizeof(float), cudaMemcpyDeviceToHost));
	  CHECK(cudaMemcpy(c, dev_c, n2 * sizeof(float), cudaMemcpyDeviceToHost));
		
  
	  // return forward data and backward data {b_bin,c_bin} 
	  
	  // free 
	  cudaFree(dev_a);
	  cudaFree(dev_b);
	  cudaFree(dev_c);

  }
  
  
  __global__ void unpooling_kernel(float *a, float *b, float *c, int st_h, int st_w, int in_c, int in_h, int in_w)
  {
	  int bid = blockIdx.x;
	  int tid = threadIdx.x;
	  int n1,c1,h1,w1,h2,w2,start_h1,end_h1,start_w1,end_w1,max_h,max_w,in_h1,in_w1;
	  float loss,elt;
  
	  n1 = bid;
	  c1 = tid;
	  in_h1 = in_h * st_h;
	  in_w1 = in_w * st_w;
	  for(h2=0;h2<in_h;h2++){
		  for(w2=0;w2<in_w;w2++){
			  start_h1 = st_h*h2;
			  end_h1 = st_h*(h2+1);
			  start_w1 = st_w*w2;
			  end_w1 = st_w*(w2+1);
			  elt = a[IDX4C(n1,c1,h2,w2,in_c,in_h,in_w)];
			  loss = b[IDX4C(n1,c1,h2,w2,in_c,in_h,in_w)];
			  max_h = (int) floor(elt / 1000.0);
			  max_w = (int) fmodf(elt,1000.0);
			  for(h1=start_h1;h1<end_h1;h1++){
				  for(w1=start_w1;w1<end_w1;w1++){
					  if(h1 == max_h && w1 == max_w){
						  c[IDX4C(n1,c1,h1,w1,in_c,in_h1,in_w1)] = loss;
					  }
					  else{
						  c[IDX4C(n1,c1,h1,w1,in_c,in_h1,in_w1)] = 0.0;
					  }
				  }
			  }
		  }
	  }
		  
  }
	
  /*
  1st arg in_n of sparse-tensor
  2nd arg in_c of sparse-tensor
  3rd arg in_h of sparse-tensor
  4th arg in_w of sparse-tensor
  5th arg input sparse-tensor
  6th arg input loss-tensor
  7th arg output tensor(backward)
  8th arg stride hight
  9th arg stride width
  
  return gradiate tensor
  e.g.
  ts1 index-tensor
	each element is  row*1000+col
	|1.0*1000+1.0,1.0*1000*3.0|
	|3.0*1000+1.0,3.0*1000+3.0|
  ts2 loss-tensor
	|0.1,0.2|
	|0.3,0.4|
  
  return
	|0.0,0.0,0.0,0.0|
	|0.0,0.1,0.0,0.2|
	|0.0,0.0,0.0,0.0|
	|0.0,3.4,0.0,0.4|
  
  */
  
  void cuda_unpooling(int in_n, int in_c, int in_h, int in_w, float *a, float *b, float *c,int st_h, int st_w){
	  int n1, n2;
	  float *dev_a, *dev_b, *dev_c;
	
	  n1 = in_n * in_c * in_h * in_w;
	  n2 = in_n * in_c * (in_h * st_h) * (in_w * st_w);
	  
		
	  // Allocate for GPU
	  CHECK(cudaMalloc((void**)&dev_a, n1 * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_b, n1 * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_c, n2 * sizeof(float)));
  
	
	  // copy from host a,b to GPU dev_a, dev_b
	  CHECK(cudaMemcpy(dev_a, a, n1 * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_b, b, n1 * sizeof(float), cudaMemcpyHostToDevice));

	  
	  dim3 blocks(in_n,1,1);
	  dim3 threads(in_c,1,1);
	  unpooling_kernel <<<blocks, threads>>>(dev_a, dev_b, dev_c, st_h, st_w, in_c, in_h, in_w);
	
	  // copy to host d from GPU dev_d
	  CHECK(cudaMemcpy(c, dev_c, n2 * sizeof(float), cudaMemcpyDeviceToHost));
  
	  // free 
	  cudaFree(dev_a);
	  cudaFree(dev_b);
	  cudaFree(dev_c);
  
  }
  
  	
  
  __global__ void convolute1_kernel(float *a, float *b, float *c, int filt_n, int filt_c, int filt_h, int filt_w,
	int st_h, int st_w, int pad, int in_c, int in_h, int in_w, int oh, int ow)
{
   int bid = blockIdx.x;
   int tid = threadIdx.x;
   int n1,c1,c2,h1,w1,h2,w2,start_h1,end_h1,start_w1,end_w1;
   float sum,elt1,elt2;
	 
   n1 = bid;
   c2 = tid;
   for(w2=0;w2<ow;w2++){
	   for(h2=0;h2<oh;h2++){
		   sum = 0.0;
		   start_h1 = st_h*h2-pad;
		   end_h1 = start_h1 + filt_h;
		   start_w1 = st_w*w2-pad;
		   end_w1 = start_w1 + filt_w;
		   for(c1=0;c1<in_c;c1++){
			   for(h1=start_h1;h1<end_h1;h1++){
				   for(w1=start_w1;w1<end_w1;w1++){
					   if(h1 >= 0 && h1 < in_h && w1 >= 0 && w1 < in_w){
						   elt1 = a[IDX4C(n1,c1,h1,w1,in_c,in_h,in_w)];
						   elt2 = b[IDX4C(c2,c1,h1-start_h1,w1-start_w1,filt_c,filt_h,filt_w)];
						   sum = sum + elt1*elt2;
					   }
				   }
			   }
		   }
		   c[IDX4C(n1,c2,h2,w2,filt_n,oh,ow)] = sum;   
	   }
   }
	   
}
 
/*
1st arg in_n of input tensor
2nd arg in_c of input tensor
3rd arg in_h of input tensor
4th arg in_w of input tensor
5th arg filt_n of filter tensor
6th arg filt_c of filter tensor
7th arg filt_h of filter tensor
8th arg filt_w of filter tensor
9th arg input tensor
10th arg filter tensor
11th arg filter output-tensor
12th arg stride hight
13th arg stride width
14th arg padding   
*/

void cuda_convolute(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w, float *a, float *b, float *c,
                int st_h, int st_w, int pad){
   int n1, n2, n3, oh, ow;
   float *dev_a, *dev_b, *dev_c;
 
   
   n1 = in_n * in_c * in_h * in_w;
   n2 = filt_n * filt_c * filt_h * filt_w;
   oh = (in_h+2*pad-filt_h)/st_h + 1;
   ow = (in_w+2*pad-filt_w)/st_w + 1;
   n3 = in_n * filt_n * oh * ow;  // n of filter generate n channel
   
   // Allocate for GPU
   CHECK(cudaMalloc((void**)&dev_a, n1 * sizeof(float)));
   CHECK(cudaMalloc((void**)&dev_b, n2 * sizeof(float)));
   CHECK(cudaMalloc((void**)&dev_c, n3 * sizeof(float)));

 
   // copy from host a,b to GPU dev_a, dev_b
   CHECK(cudaMemcpy(dev_a, a, n1 * sizeof(float), cudaMemcpyHostToDevice));
   CHECK(cudaMemcpy(dev_b, b, n2 * sizeof(float), cudaMemcpyHostToDevice));


   dim3 blocks(in_n,1,1);
   dim3 threads(filt_n,1,1);
   convolute1_kernel <<<blocks, threads>>>(dev_a, dev_b, dev_c, filt_n, filt_c, filt_h, filt_w, st_h, st_w, pad, in_c, in_h, in_w, oh, ow);
 
   // copy to host c from GPU dev_c
   CHECK(cudaMemcpy(c, dev_c, n3 * sizeof(float), cudaMemcpyDeviceToHost));

   // free 
   cudaFree(dev_a);
   cudaFree(dev_b);
   cudaFree(dev_c);
   
}


  
__global__ void deconvolute1_kernel(float *a, float *b, float *c, int filt_n, int filt_c, int filt_h, int filt_w,
	int st_h, int st_w, int pad1, int pad, int in_c, int in_h, int in_w, int oh, int ow, int oh1, int ow1)
{
   int bid = blockIdx.x;
   int tid = threadIdx.x;
   int n1,c1,c2,h1,w1,h2,w2,start_h1,end_h1,start_w1,end_w1;
   float sum,elt1,elt2;
   
   n1 = bid;
   c2 = tid;
	   
   //full convolute. stride=1 always
   for(w2=0;w2<ow;w2++){
	   for(h2=0;h2<oh;h2++){
		   start_h1 = h2-pad1;  
		   end_h1 = start_h1 + filt_h;
		   start_w1 = w2-pad1;
		   end_w1 = start_w1 + filt_w;
		   sum = 0.0;
		   for(h1=start_h1;h1<end_h1;h1++){
			   for(w1=start_w1;w1<end_w1;w1++){
				   for(c1=0;c1<filt_n;c1++){        
					   if(h1 >= 0 && h1 < in_h && w1 >= 0 && w1 < in_w){
						   elt1 = a[IDX4C(n1,c1,h1,w1,in_c,in_h,in_w)]; //loss tensor
						   elt2 = b[IDX4C(c1,c2,h1-start_h1,w1-start_w1,filt_c,filt_h,filt_w)]; //filter tensor
						   sum = sum + elt1*elt2;
					   } 
				   }   
			   }
		   }
		   if(h2-pad >=0 && h2-pad < oh1 && w2-pad >= 0 && w2-pad < ow1){
			   c[IDX4C(n1,c2,h2-pad,w2-pad,filt_c,oh1,ow1)] = sum;
		   }             
	   }
   }
   
}
 
/*
1st arg in_n of input tensor
2nd arg in_c of input tensor
3rd arg in_h of input tensor
4th arg in_w of input tensor
5th arg filt_n of filter tensor
6th arg filt_c of filter tensor
7th arg filt_h of filter tensor
8th arg filt_w of filter tensor
9th arg input loss tensor
10th arg filter tensor
11th arg output tensor
12th arg stride hight
13th arg stride width
14th arg padding   

memo
ex padding = 1
loss 4*4
filter 2*2
input 3*3  padding=1
(3-2+2*1)/1 + 1 = 4  
decovolute compute 5*5(3*3 padding=1) and save result range 3*3


*/
void cuda_deconvolute1(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w,
                   float *a, float *b, float *c, int st_h, int st_w, int pad){
   int pad1, n1, n2, n3, oh, ow, oh1, ow1, i,j,k,l;
   float *b1;
   float *dev_a, *dev_b, *dev_c;
 
   
   n1 = in_n * in_c * in_h * in_w;
   n2 = filt_n * filt_c * filt_h * filt_w;
   pad1 = filt_h - 1;
   // pad1 = filt_h -1,  pad is original padding size
   oh = (in_h+2*pad1-filt_h)/st_h + 1;
   ow = (in_w+2*pad1-filt_w)/st_w + 1;
   oh1 = (in_h+2*(pad1-pad)-filt_h)/st_h + 1;
   ow1 = (in_w+2*(pad1-pad)-filt_w)/st_w + 1;
   n3 = in_n * filt_c * oh1 * ow1;  // channel of filter generate same channel input tensor
   b1 = (float *)malloc (n2 * sizeof (float));
 
	 
   //rotate 180 degree
   for(i=0;i<filt_n;i++){  
	   for(j=0;j<filt_c;j++){
		   for(k=0;k<filt_h;k++){
			   for(l=0;l<filt_w;l++){
				   b1[IDX4C(i,j,filt_h-k-1,filt_w-l-1,filt_c,filt_h,filt_w)] = b[IDX4C(i,j,k,l,filt_c,filt_h,filt_w)];
			   }
		   }
	   }
   }

   
   // Allocate for GPU
   CHECK(cudaMalloc((void**)&dev_a, n1 * sizeof(float)));
   CHECK(cudaMalloc((void**)&dev_b, n2 * sizeof(float)));
   CHECK(cudaMalloc((void**)&dev_c, n3 * sizeof(float)));

 
   // copy from host a,b1,c to GPU dev_a, dev_b, dev_c
   CHECK(cudaMemcpy(dev_a, a, n1 * sizeof(float), cudaMemcpyHostToDevice));
   CHECK(cudaMemcpy(dev_b, b1, n2 * sizeof(float), cudaMemcpyHostToDevice));
   CHECK(cudaMemcpy(dev_c, c, n3 * sizeof(float), cudaMemcpyHostToDevice));

   dim3 blocks(in_n,1,1);
   dim3 threads(filt_c,1,1);
   deconvolute1_kernel <<<blocks, threads>>>(dev_a, dev_b, dev_c, filt_n, filt_c, filt_h, filt_w, st_h, st_w, pad1, pad, in_c, in_h, in_w, oh, ow, oh1, ow1);
 
   // copy to host c from GPU dev_c
   CHECK(cudaMemcpy(c, dev_c, n3 * sizeof(float), cudaMemcpyDeviceToHost));

   // free 
   cudaFree(dev_a);
   cudaFree(dev_b);
   cudaFree(dev_c);
   free(b1);
   
}




__global__ void deconvolute2_kernel(float *a1, float *a, float *b, float *c, int filt_n, int filt_c,int filt_h, int filt_w,
	int st_h, int st_w, int pad, int in_c, int in_h, int in_w, int loss_h, int loss_w)
{
   int bid = blockIdx.x;
   int tid = threadIdx.x;
   int n1,c1,c2,h1,w1,h2,w2,oh,ow,start_h1,end_h1,start_w1,end_w1;
   int j,k,l,k1,l1;
   float sum,elt1,elt2;
   
   n1 = bid;
   c2 = tid;
   // caution! stride=1 
   oh = (in_h+2*pad-filt_h) + 1;
   ow = (in_w+2*pad-filt_w) + 1;
   
   //dilate loss tensor.
   for(j=0;j<filt_n;j++){
	   for(k=0;k<loss_h;k++){
		   for(l=0;l<loss_w;l++){
			   elt1 = a[IDX4C(n1,j,k,l,in_c,loss_h,loss_w)];
			   k1 = st_h*k;
			   l1 = st_w*l;
			   a1[IDX4C(n1,j,k1,l1,in_c,in_h,in_w)] = elt1;
		   }
	   }
   }
   //full convulute. stride=1
   for(c2=0;c2<filt_c;c2++){
	   for(w2=0;w2<ow;w2++){
		   for(h2=0;h2<oh;h2++){
			   start_h1 = h2-pad;
			   end_h1 = start_h1 + filt_h;
			   start_w1 = w2-pad;
			   end_w1 = start_w1 + filt_w;
			   sum = 0.0;
			   for(h1=start_h1;h1<end_h1;h1++){
				   for(w1=start_w1;w1<end_w1;w1++){
					   for(c1=0;c1<filt_n;c1++){        
						   if(h1 >= 0 && h1 < in_h && w1 >= 0 && w1 < in_w){
							   elt1 = a1[IDX4C(n1,c1,h1,w1,in_c,in_h,in_w)]; //loss tensor
							   elt2 = b[IDX4C(c1,c2,h1-start_h1,w1-start_w1,filt_c,filt_h,filt_w)]; //filter tensor
							   sum = sum + elt1*elt2;
						   }
					   }
				   }   
			   }
			   c[IDX4C(n1,c2,h2,w2,filt_c,oh,ow)] = sum;              
		   }
	   }
   }
   
}




/*
dilate loss tensor 
e.g.

|1.0,2.0|
|3.0,4.0|

dilated stride=2
|1.0,0.0,2.0|
|0.0,0.0,0.0|
|3.0,0.0,4.0|


*/


/*
1st arg in_n of input loss tensor
2nd arg in_c of input loss tensor
3rd arg in_h of input loss  tensor
4th arg in_w of input loss tensor
5th arg filt_n of filter tensor
6th arg filt_c of filter tensor
7th arg filt_h of filter tensor
8th arg filt_w of filter tensor
9th arg input loss tensor
10th arg filter tensor
11th arg output tensor
12th arg stride hight
13th arg stride width
14th arg padding   
*/

void cuda_deconvolute2(int in_n, int in_c, int loss_h, int loss_w, int filt_n, int filt_c, int filt_h,int filt_w,
             float *a, float *b, float *c,int st_h, int st_w,int pad){
   int pad1, n1, n2, n3, oh, ow, i,j,k,l,in_h, in_w;
   float *a1, *b1;
   float *dev_a, *dev_a1, *dev_b, *dev_c;

 
	   
   // size for dilate
   in_h = loss_h + (loss_h - 1)*(st_h - 1);
   in_w = loss_w + (loss_w - 1)*(st_w - 1);

   n1 = in_n * in_c * in_h * in_w;  //loss tensor size 
   n2 = filt_n * filt_c * filt_h * filt_w;  //filter tensor size
   pad1 = (filt_h - 1) + pad;    //padding size with dilate
   oh = (in_h+2*pad1-filt_h) + 1; //output deconvolute tensor size. caution stride=1.
   ow = (in_w+2*pad1-filt_w) + 1; // 
   n3 = in_n * filt_c * oh * ow;   // 
   a1 = (float *)malloc (n1 * sizeof (float));
   b1 = (float *)malloc (n2 * sizeof (float));

   //rotate 180 degree
   for(i=0;i<filt_n;i++){  
	   for(j=0;j<filt_c;j++){
		   for(k=0;k<filt_h;k++){
			   for(l=0;l<filt_w;l++){
				   b1[IDX4C(i,j,filt_h-k-1,filt_w-l-1,filt_c,filt_h,filt_w)] = b[IDX4C(i,j,k,l,filt_c,filt_h,filt_w)];
			   }
		   }
	   }
   }


   // dilate 
   for(i=0;i<n1;i++){
	   a1[i] = 0.0;
   }

   CHECK(cudaMalloc((void**)&dev_a1, n1 * sizeof(float)));
   CHECK(cudaMalloc((void**)&dev_a, in_n*1*loss_h*loss_w * sizeof(float)));
   CHECK(cudaMalloc((void**)&dev_b, n2 * sizeof(float)));
   CHECK(cudaMalloc((void**)&dev_c, n3 * sizeof(float)));

   CHECK(cudaMemcpy(dev_a1, a1, n1 * sizeof(float), cudaMemcpyHostToDevice));
   CHECK(cudaMemcpy(dev_a, a, in_n*1*loss_h*loss_w  * sizeof(float), cudaMemcpyHostToDevice));
   CHECK(cudaMemcpy(dev_b, b1, n2 * sizeof(float), cudaMemcpyHostToDevice));
   CHECK(cudaMemcpy(dev_c, c, n3 * sizeof(float), cudaMemcpyHostToDevice));

   dim3 blocks(in_n,1,1);
   dim3 threads(filt_c,1,1);
   deconvolute2_kernel <<<blocks, filt_c>> >(dev_a1, dev_a, dev_b, dev_c, filt_n, filt_c, filt_h, filt_w, st_h, st_w, pad1, in_c, in_h, in_w, loss_h, loss_w);
 
   // copy to host c from GPU dev_c
   CHECK(cudaMemcpy(c, dev_c, n3 * sizeof(float), cudaMemcpyDeviceToHost));
   
   // free 
   cudaFree(dev_a);
   cudaFree(dev_a1);
   cudaFree(dev_b);
   cudaFree(dev_c);
   free(a1);
   free(b1);
 
}

  
__global__ void gradfilter1_kernel(float *a, float *b, float *c, int filt_n, int filt_c, int filt_h, int filt_w, int loss_c, int loss_h, int loss_w, int st_h, int st_w, int pad, int in_c, int in_h, int in_w, int n)
{
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    int n1,c1,c2,h1,w1,h2,w2,h3,w3;
    float sum,elt1,elt2;

    n1 = bid;
    c2 = tid;
    
    for(c1=0;c1<filt_c;c1++){
    //h1,w1 is index of filter
        for(h1=0;h1<filt_h;h1++){
            for(w1=0;w1<filt_w;w1++){
                //h2,w2 is index of loss tensor
                sum = 0.0;
                for(h2=0;h2<loss_h;h2++){
                    for(w2=0;w2<loss_w;w2++){
                        //h3,w3 is index of input tensor
                        h3 = h1 - pad + h2;
                        w3 = w1 - pad + w2;
                        if(h3>=0 && h3<in_h && w3>=0 && w3<in_w){
                            elt1 = a[IDX4C(n1,c1,h3,w3,in_c,in_h,in_w)];    //input tensor
                            elt2 = b[IDX4C(n1,c2,h2,w2,loss_c,loss_h,loss_w)]; //loss tensor
                            sum = sum + elt1*elt2;
                        }
                    }
                }
                //set filter tensor
                c[IDX5C(n1,c2,c1,h1,w1,filt_n,filt_c,filt_h,filt_w)] =  sum;
            }
        }
    } 
               
}



  
/*
1st arg in_n of input tensor
2nd arg in_c of input tensor
3rd arg in_h of input tensor
4th arg in_w of input tensor
5th arg filt_n of filter tensor
6th arg filt_c of filter tensor
7th arg filt_h of filter tensor
8th arg filt_w of filter tensor
9th arg loss_c of loss tensor
10th arg loss_h of loss tensor
11th arg loss_w of loss tensor
12th arg filter tensor
13th arg loss tensor
14th arg output tensor
15th arg stride hight
16th arg stride width
17th arg padding   
*/

void cuda_gradfilter1(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w,
                 int loss_c, int loss_h, int loss_w, float *a, float *b, float *d, int st_h, int st_w, int pad){
    int n1,n2,n3,n4,i,j,k,l,m;
    float *c;
    float *dev_a, *dev_b, *dev_c;
    float elt;
  
    
    n1 = in_n * in_c * in_h * in_w;
    n2 = in_n * loss_c * loss_h * loss_w;
    n3 = in_n * filt_n * filt_c * filt_h * filt_w;
    n4 = filt_n * filt_c * filt_h * filt_w;
    c = (float *)malloc (n3 * sizeof (float));

    //initialize c
    for(i=0;i<n3;i++){
        c[i] = 0.0;
    }
  
    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n1 * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n2 * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_c, n3 * sizeof(float)));

    
    // copy from host a,b,c to GPU dev_a, dev_b, dev_c
    CHECK(cudaMemcpy(dev_a, a, n1 * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n2 * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_c, c, n3 * sizeof(float), cudaMemcpyHostToDevice));

    dim3 blocks(in_n,1,1);
    dim3 threads(filt_n,1,1);
    gradfilter1_kernel <<<blocks, threads>>>(dev_a, dev_b, dev_c, filt_n, filt_c, filt_h, filt_w, loss_c, loss_h, loss_w, st_h, st_w, pad, in_c, in_h, in_w, in_n);
  
    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(c, dev_c, n3 * sizeof(float), cudaMemcpyDeviceToHost));

    //average
    // clear d
    for(i=0;i<n4;i++){
        d[i] = 0.0;
    }
    // copy from c to d and compute sum
    for(i=0;i<in_n;i++){
        for(j=0;j<filt_n;j++){
            for(k=0;k<filt_c;k++){
                for(l=0;l<filt_h;l++){
                    for(m=0;m<filt_w;m++){
                        elt = c[IDX5C(i,j,k,l,m,filt_n,filt_c,filt_h,filt_w)];
                        d[IDX4C(j,k,l,m,filt_c,filt_h,filt_w)] = d[IDX4C(j,k,l,m,filt_c,filt_h,filt_w)] + elt;
                    }
                }
            }
        }
    }
    // average
    for(i=0;i<n4;i++){
        d[i] = d[i] / (float)in_n;
    }
    
    
    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
    free(c);
}

  
__global__ void gradfilter2_kernel(float *a, float *b1, float *b, float *c, int filt_n, int filt_c, int filt_h, int filt_w, int loss_c, int loss_h, int loss_w, int st_h, int st_w, int pad, int in_c, int in_h, int in_w, int n)
{
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    int n1,c1,c2,h1,w1,h2,w2,h3,w3,loss_h1,loss_w1,j,k,l,k1,l1;
    float sum,elt1,elt2;
    
    n1 = bid;
    c2 = tid;
    //dilated loss tensor size
    loss_h1 = loss_h+(loss_h-1)*(st_h-1);
    loss_w1 = loss_w+(loss_w-1)*(st_w-1);
    //dilate loss tensor.
    for(j=0;j<loss_c;j++){
        for(k=0;k<loss_h;k++){
            for(l=0;l<loss_w;l++){
                elt1 = b[IDX4C(n1,j,k,l,loss_c,loss_h,loss_w)];
                k1 = st_h*k;
                l1 = st_w*l;
                b1[IDX4C(n1,j,k1,l1,loss_c,loss_h1,loss_w1)] = elt1;
            }
        }
    }
    //convolute input tensor with dilated loss tensor. cuation stride is always 1. 
    for(c1=0;c1<filt_c;c1++){
    //h1,w1 is index of filter
        for(h1=0;h1<filt_h;h1++){
            for(w1=0;w1<filt_w;w1++){
                //h2,w2 is index of loss tensor
                sum = 0.0;
                for(h2=0;h2<loss_h1;h2++){
                    for(w2=0;w2<loss_w1;w2++){
                        //h3,w3 is index of input tensor
                        h3 = h1 - pad + h2;
                        w3 = w1 - pad + w2;
                        if(h3>=0 && h3<in_h && w3>=0 && w3<in_w){
                            elt1 = a[IDX4C(n1,c1,h3,w3,in_c,in_h,in_w)];    //input tensor
                            elt2 = b1[IDX4C(n1,c2,h2,w2,loss_c,loss_h1,loss_w1)]; //loss tensor
                            sum = sum + elt1*elt2;
                        }
                    }
                }
                //set filter tensor
                c[IDX5C(n1,c2,c1,h1,w1,filt_n,filt_c,filt_h,filt_w)] = + sum;
            }
        }
    } 
        
}

/*
dilate loss tensor 
e.g.

|1.0,2.0|
|3.0,4.0|

dilated stride=2
|1.0,0.0,2.0|
|0.0,0.0,0.0|
|3.0,0.0,4.0|


*/

/*
gradfilter2 is for stride >= 2. This one requires dilate
1st arg in_n of input tensor
2nd arg in_c of input tensor
3rd arg in_h of input tensor
4th arg in_w of input tensor
5th arg filt_n of filter tensor
6th arg filt_c of filter tensor
7th arg filt_h of filter tensor
8th arg filt_w of filter tensor
9th arg loss_c of loss tensor
10th arg loss_h of loss tensor
11th arg loss_w of loss tensor
12th arg filter tensor
13th arg loss tensor
14th arg output tensor
15th arg stride hight
16th arg stride width
17th arg padding  

*/
void cuda_gradfilter2(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w, 
                 int loss_c, int loss_h, int loss_w, float *a, float *b, float *d, int st_h, int st_w, int pad){
    int n1,n2,n3,n4,n5,i,j,k,l,m;
    float *b1,*c;
    float *dev_a, *dev_b, *dev_b1, *dev_c;
    float elt;
  
    n1 = in_n * in_c * in_h * in_w;
    n2 = in_n * loss_c * loss_h * loss_w;
    n3 = in_n * filt_n * filt_c * filt_h * filt_w;
    n4 = filt_n * filt_c * filt_h * filt_w;
    n5 = in_n * loss_c * (loss_h+(loss_h-1)*(st_h-1)) * (loss_w+(loss_w-1)*(st_w-1));  // dilated loss tensor size  
    b1 = (float *)malloc (n5 * sizeof (float));  // dilate loss tensor area
    c = (float *)malloc (n3 * sizeof (float));

    //initialize c
    for(i=0;i<n3;i++){
        c[i] = 0.0;
    }
    //initialize b1
    for(i=0;i<n5;i++){
        b1[i] = 0.0;
    }
  
    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n1 * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n2 * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b1, n5 * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_c, n3 * sizeof(float)));

    
    // copy from host a,b,c to GPU dev_a, dev_b, dev_c
    CHECK(cudaMemcpy(dev_a, a, n1 * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n2 * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b1, b1, n5 * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_c, c, n3 * sizeof(float), cudaMemcpyHostToDevice));

    dim3 blocks(in_n,1,1);
    dim3 threads(filt_n,1,1);
    gradfilter2_kernel <<<blocks, threads>> >(dev_a, dev_b1, dev_b, dev_c, filt_n, filt_c, filt_h, filt_w, loss_c, loss_h, loss_w, st_h, st_w, pad, in_c, in_h, in_w, in_n);
  
    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(c, dev_c, n3 * sizeof(float), cudaMemcpyDeviceToHost));

    //average
    // clear d
    for(i=0;i<n4;i++){
        d[i] = 0.0;
    }
    // copy from c to d and compute sum
    for(i=0;i<in_n;i++){
        for(j=0;j<filt_n;j++){
            for(k=0;k<filt_c;k++){
                for(l=0;l<filt_h;l++){
                    for(m=0;m<filt_w;m++){
                        elt = c[IDX5C(i,j,k,l,m,filt_n,filt_c,filt_h,filt_w)];
                        d[IDX4C(j,k,l,m,filt_c,filt_h,filt_w)] = d[IDX4C(j,k,l,m,filt_c,filt_h,filt_w)] + elt;
                    }
                }
            }
        }
    }
    // average
    for(i=0;i<n4;i++){
        d[i] = d[i] / (float)in_n;
    }
     
    
    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_b1);
    cudaFree(dev_c);
    free(b1);
    free(c);
}



__global__ void full_kernel(float *a, float *b, int in_n, int in_c, int in_h, int in_w, int n)
{
    int tid = threadIdx.x;
    int n1,i,j,k;
    float elt;
    if(tid < n)
    {   
        n1 = tid;
        for(i=0;i<in_c;i++){
            for(j=0;j<in_h;j++){
                for(k=0;k<in_w;k++){
                    elt = a[IDX4C(n1,i,j,k,in_c,in_h,in_w)];
                    b[IDX2C(n1,i*in_h*in_w + j*in_w + k,in_n)] = elt;
                }
            }
        }
    }
}
  
/*
1st arg in_n of input tensor 4DIM
2nd arg in_c of input tensor
3rd arg in_h of input tensor
4th arg in_w of input tensor
5th arg input tensor
6th arg output tensor
*/

void cuda_full(int in_n, int in_c, int in_h, int in_w, float *a, float *b){
    int n1,n;
    float *dev_a, *dev_b;
 
    n1 = in_n * in_c * in_h * in_w;
    n = in_n;
      
    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n1 * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n1 * sizeof(float)));
  
    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n1 * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n1 * sizeof(float), cudaMemcpyHostToDevice));

    full_kernel << <1, n>> >(dev_a, dev_b, in_n, in_c, in_h, in_w, n);
  
    // copy to host d from GPU dev_d
    CHECK(cudaMemcpy(b, dev_b, n1 * sizeof(float), cudaMemcpyDeviceToHost));

    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);

}


__global__ void unfull_kernel(float *a, float *b, int in_n, int in_c, int in_h, int in_w, int n)
{
    int tid = threadIdx.x;
    int n1,i,j,k;
    float elt;
    if(tid < n)
    {   
        n1 = tid;
        for(i=0;i<in_c;i++){
            for(j=0;j<in_h;j++){
                for(k=0;k<in_w;k++){
                    elt = a[IDX2C(n1,i*in_h*in_w + j*in_w + k,in_n)];
                    b[IDX4C(n1,i,j,k,in_c,in_h,in_w)] = elt;
                }
            }
        }
    }
}
  
/*
1st arg in_n of input tensor 4DIM
2nd arg in_c of input tensor
3rd arg in_h of input tensor
4th arg in_w of input tensor
5th arg input tensor
6th arg output tensor
*/

void cuda_unfull(int in_n, int in_c, int in_h, int in_w, float *a, float *b){
    int n1,n;
    float *dev_a, *dev_b;
    
    n1 = in_n * in_c * in_h * in_w;
    n = in_n;
      
      // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n1 * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n1 * sizeof(float)));
  
    // copy from host a,b1,c to GPU dev_a, dev_b, dev_c
    CHECK(cudaMemcpy(dev_a, a, n1 * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n1 * sizeof(float), cudaMemcpyHostToDevice));

    unfull_kernel << <1, n>> >(dev_a, dev_b, in_n, in_c, in_h, in_w, n);
  
    // copy to host d from GPU dev_d
    CHECK(cudaMemcpy(b, dev_b, n1 * sizeof(float), cudaMemcpyDeviceToHost));

    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);

}

__global__ void emult1_kernel(float *a, float *b, float *c, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {
        c[tid] = a[tid] * b[tid];
        tid += blockDim.x * gridDim.x;
    }
}


void cuda_emult(int n, float *a, float *b,float *c){
    float *dev_a, *dev_b, *dev_c;

    
    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

    emult1_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(c, dev_c, n * sizeof(float), cudaMemcpyDeviceToHost));

    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
}




__global__ void sigmoid_kernel(float *a, float *b, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {   
        b[tid] = SIGMOID(a[tid]);
        tid += blockDim.x * gridDim.x;
    }
}

void cuda_activate_sigmoid(int n, float *a, float *b){
    float *dev_a, *dev_b;

   
    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

    sigmoid_kernel << <128, 128 >> >(dev_a, dev_b, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(b, dev_b, n * sizeof(float), cudaMemcpyDeviceToHost));
    
    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);

}

  
__global__ void tanh_kernel(float *a, float *b, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {
        b[tid] = tanh(a[tid]);
        tid += blockDim.x * gridDim.x;
    }
}


void cuda_activate_tanh(int n, float *a, float *b){
    float *dev_a, *dev_b;

    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

    tanh_kernel << <128, 128 >> >(dev_a, dev_b, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(b, dev_b, n * sizeof(float), cudaMemcpyDeviceToHost));
    
    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);
}


  
__global__ void relu_kernel(float *a, float *b, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {   
        if(a[tid] >= 0)
            b[tid] = a[tid];
        else 
            b[tid] = 0.0;
        tid += blockDim.x * gridDim.x;
    }
}


void cuda_activate_relu(int n, float *a, float *b){
    float *dev_a, *dev_b;

    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

    relu_kernel << <128, 128 >> >(dev_a, dev_b, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(b, dev_b, n * sizeof(float), cudaMemcpyDeviceToHost));
    
    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);
}

void cuda_activate_softmax(int r1, int c1, float *a, float *b){
    int i, j, k;
    float max,sum,delta;

    
    //calculate softmax
    delta = 0.01;
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++){
            max = -3.402823e38;
            for(k=0;k<c1;k++){
                if(a[IDX2C(i,k,r1)] > max)
                    max = a[IDX2C(i,k,r1)];
            }
            sum = 0.0;
            for(k=0;k<c1;k++){
                sum = sum + exp(a[IDX2C(i,k,r1)] - max);
            }
            b[IDX2C(i,j,r1)] = exp(a[IDX2C(i,j,r1)] - max) / (sum+delta);
            
        }
    }

}



__global__ void differ_sigmoid_kernel(float *a, float *b, float *c, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {   
        
        c[tid] = a[tid] * ((1 - SIGMOID(b[tid])) * SIGMOID(b[tid]));
        tid += blockDim.x * gridDim.x;
    }
}


void cuda_differ_sigmoid(int n, float *a, float *b, float *c){
    float *dev_a, *dev_b, *dev_c;

    
    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

    differ_sigmoid_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(c, dev_c, n * sizeof(float), cudaMemcpyDeviceToHost));

    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

}


__global__ void differ_tanh_kernel(float *a, float *b, float *c, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {   
        c[tid] = a[tid] * (1/(cosh(b[tid]) * cosh(b[tid])));
        tid += blockDim.x * gridDim.x;
    }
}


void cuda_differ_tanh(int n, float *a, float *b, float *c){
    float *dev_a, *dev_b, *dev_c;

    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

    differ_tanh_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(c, dev_c, n * sizeof(float), cudaMemcpyDeviceToHost));

    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
}



__global__ void differ_relu_kernel(float *a, float *b, float *c, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {   
        if(b[tid] >= 0)
            c[tid] = a[tid];
        else 
            c[tid] = 0.0;
        tid += blockDim.x * gridDim.x;
    }
}


void cuda_differ_relu(int n, float *a, float *b, float *c){
    float *dev_a, *dev_b, *dev_c;

    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

    differ_relu_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(c, dev_c, n * sizeof(float), cudaMemcpyDeviceToHost));

    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

}



void add_diff1(int r1, int c1, float *a, float *b, int x, int y, float val) {
    int i, j;
    
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++){
            if(i==x && j==y)
                b[IDX2C(i,j,r1)] = a[IDX2C(i,j,r1)] + (float)val;
            else 
                b[IDX2C(i,j,r1)] = a[IDX2C(i,j,r1)];
        }
    }

}


void add_diff2(int n1, int c1, int h1, int w1, float *a, float *b, int n2, int c2, int h2, int w2,float val){
    int i, j, k, l;
    
    for(i=0;i<n1;i++){
        for(j=0;j<c1;j++){
            for(k=0;k<h1;k++){
                for(l=0;l<w1;l++){
                    if(i==n2 && j==c2 && k==h2 && l==w2){
                        b[IDX4C(i,j,k,l,c1,h1,w1)] = a[IDX4C(i,j,k,l,c1,h1,w1)] + (float)val;
                    }
                    else {
                        b[IDX4C(i,j,k,l,c1,h1,w1)] = a[IDX4C(i,j,k,l,c1,h1,w1)];
                    }
                }
            }
        }
    }


}




__global__ void dropout1_kernel(float *a, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {
        a[tid] = 1.0;
        tid += blockDim.x * gridDim.x;
    }
}

/*
1st arg size of mask tensor
2nd arg rate of dropout

return mask tensor
element of mask tensor is basicaly 1.0.
element of dropout rate is 0.0.
when forward and backward, generate Hadamard product with mask tensor
*/

void cuda_dropout(int n, float dropout_rate, float *a){ 
    int count,i,j;
    float *dev_a;


    // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));

    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));

    dropout1_kernel << <128, 128 >> >(dev_a, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(a, dev_a, n * sizeof(float), cudaMemcpyDeviceToHost));


    // dropout
    count = (int)(double(n)*dropout_rate);
    for(i=0;i<count;i++){
        j = rand() % n;
        a[j] = 0.0;
    }

    // free 
    cudaFree(dev_a);
}


__global__ void sgd1_kernel(float *a, float *b, float *c, float lr, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < n)
    {
        c[tid] = a[tid] - b[tid]*lr;
        tid += blockDim.x * gridDim.x;
    }
}
/*
w - g*lr
w is weight matrix.
g is gradient matrix.
when element of w is zero result is zero. This means dropout.
return updated weight matrix.

1st arg is size of vectorized matrix
2nd arg is weight matrix or tensor
3rd arg is gradient matrix or tensor
4th arg is output tensor
5th arg is learning rate
*/

void sgd1(int n, float *a, float *b, float *c, float lr){
    float *dev_a, *dev_b, *dev_c;


        // Allocate for GPU
    CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
    CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));


    // copy from host a,b to GPU dev_a, dev_b
    CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));

    sgd1_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, lr, n);

    // copy to host c from GPU dev_c
    CHECK(cudaMemcpy(c, dev_c, n * sizeof(float), cudaMemcpyDeviceToHost));


    // free 
    cudaFree(dev_a);
    cudaFree(dev_b);    
    cudaFree(dev_c);

}

  
  /*
	def momentum(v, g, lr) do
	  Matrex.apply(v, g, fn v, g -> 0.5 * v - lr * g end)
	end
  */
  __global__ void momentum_kernel(float *a, float *b, float *c, float *d, float *e, float lr, int n)
  {
	  int tid = threadIdx.x + blockIdx.x * blockDim.x;
	  while (tid < n)
	  {   
		  
		  d[tid] = ((0.9 * b[tid]) - (lr * c[tid]));
		  e[tid] = a[tid] + d[tid];
		  
		  tid += blockDim.x * gridDim.x;
	  }
  }
  
  /*
  1st arg row-size of vectorized each-matrix
  2nd arg wight-matrix    (a)
  3rd arg v-matrix        (b)
  4th arg gradient-matrix (c)
  5th arg output next_v-matrix (d)
  6th arg output weight_matrix (e)
  7th arg learning rate
  
  */
  
  void momentum1(int n, float *a, float *b, float *c, float *d, float *e, float lr){
	  float *dev_a, *dev_b, *dev_c ,*dev_d, *dev_e;
	
	 
	  // Allocate for GPU
	  CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_d, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_e, n * sizeof(float)));
	
	  // copy from host a,b to GPU dev_a, dev_b
	  CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_c, c, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_d, d, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_e, e, n * sizeof(float), cudaMemcpyHostToDevice));
	
	  momentum_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, dev_d, dev_e, lr, n);
	
	  // copy to host d from GPU dev_d
	  CHECK(cudaMemcpy(d, dev_d, n * sizeof(float), cudaMemcpyDeviceToHost));
	  CHECK(cudaMemcpy(e, dev_e, n * sizeof(float), cudaMemcpyDeviceToHost));
  
	  
	  // free 
	  cudaFree(dev_a);
	  cudaFree(dev_b);
	  cudaFree(dev_c);
	  cudaFree(dev_d);
	  cudaFree(dev_e);
	  
  }
  

  /* ADAGRAD
	  h1 = h + grad*grad
	  lr1 = lr/(sqrt(h1))
	  w1 = w - lr1 * grad 
  
	  a[] = w
	  b[] = h
	  c[] = grad
	  d[] = h1
	  e[] = w1
  */
	
  __global__ void adagrad_kernel(float *a, float *b, float *c, float *d, float *e, float lr, int n)
  {
	  int tid = threadIdx.x + blockIdx.x * blockDim.x;
	  float lr1;
	  while (tid < n)
	  {   
		  d[tid] = b[tid] + c[tid]*c[tid];
		  if(d[tid] != 0.0)
			  lr1 = lr/(sqrt(d[tid]));
		  else
			  lr1 = lr;
		  e[tid] = a[tid] - lr1 * c[tid];
  
		  tid += blockDim.x * gridDim.x;
	  }
  }
   
  /*
  1st arg row-size of vectorized each-matrix
  2nd arg wight-matrix (a)
  3rd arg h-matrix     (b)
  4th arg grad-matrix  (c)
  5th arg output new-h (d)
  6th arg output new-w (e)
  7th arg learning rate
  */
  
  void adagrad1(int n, float *a, float *b, float *c, float *d, float *e, float lr){
	  float *dev_a, *dev_b, *dev_c, *dev_d, *dev_e;
	  
	  
	  // Allocate for GPU
	  CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_d, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_e, n * sizeof(float)));
	
	  // copy from host a,b to GPU dev_a, dev_b
	  CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_c, c, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_d, d, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_e, e, n * sizeof(float), cudaMemcpyHostToDevice));
	
	  adagrad_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, dev_d, dev_e, lr, n);
	
	  // copy to host d,e from GPU dev_d,dev_e
	  CHECK(cudaMemcpy(d, dev_d, n * sizeof(float), cudaMemcpyDeviceToHost));
	  CHECK(cudaMemcpy(e, dev_e, n * sizeof(float), cudaMemcpyDeviceToHost));
  
	  
  
	  // free 
	  cudaFree(dev_a);
	  cudaFree(dev_b);
	  cudaFree(dev_c);
	  cudaFree(dev_d);
	  cudaFree(dev_e);
	  
  }
  


  /* RMSprop
	  h1 = alpha * h + (1 - alpha) * grad*grad
	  lr1 = lr /(sqrt(h) + epsilon)
	  w1 = w - lr1 * grad 
  
	  a[] = w
	  b[] = h
	  c[] = grad
	  d[] = h1
	  e[] = w1
  */
	
  __global__ void rms_kernel(float *a, float *b, float *c, float *d, float *e, float lr, int n)
  {
	  int tid = threadIdx.x + blockIdx.x * blockDim.x;
	  float lr1,alpha,epsilon;
	  alpha = 0.99;
	  epsilon = 10.0e-7;
	  while (tid < n)
	  {   
		  d[tid] = alpha * b[tid] + (1-alpha)*c[tid]*c[tid];
		  lr1 = lr/(sqrt(d[tid])+epsilon);
		  e[tid] = a[tid] - lr1*c[tid];
  
		  tid += blockDim.x * gridDim.x;
	  }
  }
   
  /*
  1st arg row-size of vectorized each-matrix
  2nd arg wight-matrix (a)
  3rd arg h-matrix     (b)
  4th arg grad-matrix  (c)
  5th arg output new-h (d)
  6th arg output new-w (e)
  7th arg learning rate
  */
  
  void rms1(int n, float *a, float *b, float *c, float *d, float *e, float  lr){
	  float *dev_a, *dev_b, *dev_c, *dev_d, *dev_e;
	  
	 
	  // Allocate for GPU
	  CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_d, n * sizeof(float)));
	  CHECK(cudaMalloc((void**)&dev_e, n * sizeof(float)));
	
	  // copy from host a,b to GPU dev_a, dev_b
	  CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_c, c, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_d, d, n * sizeof(float), cudaMemcpyHostToDevice));
	  CHECK(cudaMemcpy(dev_e, e, n * sizeof(float), cudaMemcpyHostToDevice));
	
	  rms_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, dev_d, dev_e, lr, n);
	
	  // copy to host d,e from GPU dev_d,dev_e
	  CHECK(cudaMemcpy(d, dev_d, n * sizeof(float), cudaMemcpyDeviceToHost));
	  CHECK(cudaMemcpy(e, dev_e, n * sizeof(float), cudaMemcpyDeviceToHost));
  
	  
  
	  // free 
	  cudaFree(dev_a);
	  cudaFree(dev_b);
	  cudaFree(dev_c);
	  cudaFree(dev_d);
	  cudaFree(dev_e);
	  
  }
  


  /* ADAM
	  beta1 = 0.9
	  beta2 = 0.999
	  epsilon = 10.0e-7
	  alpha = 0.001
	  m1 = beta1 * m + (1 - beta1) * grad
	  v1 = beta2 * v + (1 - beta2) * grad^2
	  m2 = m1/(1 - beta1)
	  v2 = v1/(1 - beta2)
	  w1 = w - alpha * m2/(sqrt(v2)+epsilon)
  
	  a[] is w
	  b[] is m
	  c[] is v
	  d[] is grad
	  e[] is m1
	  f[] is v1
	  g[] is w1
   */
	
   __global__ void adam_kernel(float *a, float *b, float *c, float *d, float *e, float *f, float *g, float lr, int n)
   {
       int tid = threadIdx.x + blockIdx.x * blockDim.x;
       float beta1,beta2,epsilon,m2,v2;
       beta1 = 0.9;
       beta2 = 0.999;
       epsilon = 10.0e-7;
       //alpha = 0.001;
   
       while (tid < n){   
           e[tid] = beta1 * b[tid] + (1 - beta1) * d[tid];
           f[tid] = beta2 * c[tid] + (1 - beta2) * d[tid]*d[tid];
           m2 = e[tid]/(1-beta1);
           v2 = f[tid]/(1-beta2);
           g[tid] = a[tid] - lr * (m2/(sqrt(v2)+epsilon));
            
           tid += blockDim.x * gridDim.x;
       }
   }
      
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
   void adam1(int n, float *a, float *b, float *c, float *d, float *e, float *f, float *g, float lr){
       float *dev_a, *dev_b, *dev_c, *dev_d, *dev_e, *dev_f, *dev_g;
       
       // Allocate for GPU
       CHECK(cudaMalloc((void**)&dev_a, n * sizeof(float)));
       CHECK(cudaMalloc((void**)&dev_b, n * sizeof(float)));
       CHECK(cudaMalloc((void**)&dev_c, n * sizeof(float)));
       CHECK(cudaMalloc((void**)&dev_d, n * sizeof(float)));
       CHECK(cudaMalloc((void**)&dev_e, n * sizeof(float)));
       CHECK(cudaMalloc((void**)&dev_f, n * sizeof(float)));
       CHECK(cudaMalloc((void**)&dev_g, n * sizeof(float)));
   
       // copy from host a,b to GPU dev_a, dev_b
       CHECK(cudaMemcpy(dev_a, a, n * sizeof(float), cudaMemcpyHostToDevice));
       CHECK(cudaMemcpy(dev_b, b, n * sizeof(float), cudaMemcpyHostToDevice));
       CHECK(cudaMemcpy(dev_c, c, n * sizeof(float), cudaMemcpyHostToDevice));
       CHECK(cudaMemcpy(dev_d, d, n * sizeof(float), cudaMemcpyHostToDevice));
       CHECK(cudaMemcpy(dev_e, e, n * sizeof(float), cudaMemcpyHostToDevice));
       CHECK(cudaMemcpy(dev_f, f, n * sizeof(float), cudaMemcpyHostToDevice));
       CHECK(cudaMemcpy(dev_g, g, n * sizeof(float), cudaMemcpyHostToDevice));
       
       adam_kernel << <128, 128 >> >(dev_a, dev_b, dev_c, dev_d, dev_e, dev_f, dev_g, lr, n);
       
       // copy to host d,e from GPU dev_d,dev_e
       CHECK(cudaMemcpy(e, dev_e, n * sizeof(float), cudaMemcpyDeviceToHost));
       CHECK(cudaMemcpy(f, dev_f, n * sizeof(float), cudaMemcpyDeviceToHost));
       CHECK(cudaMemcpy(g, dev_g, n * sizeof(float), cudaMemcpyDeviceToHost));
         
     
       // free 
       cudaFree(dev_a);
       cudaFree(dev_b);
       cudaFree(dev_c);
       cudaFree(dev_d);
       cudaFree(dev_e);
       cudaFree(dev_f);
       cudaFree(dev_g);
       
       
   }
     
     
   
  