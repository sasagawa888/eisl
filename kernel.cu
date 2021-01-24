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
  extern "C" void pooling1(int in_n, int in_c, int in_h, int in_w, float *a, float *b, float *c, int st_h, int st_w);
  void pooling1(int in_n, int in_c, int in_h, int in_w, float *a, float *b, float *c, int st_h, int st_w){
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
  extern "C" void unpooling1(int in_n, int in_c, int in_h, int in_w, float *a, float *b, float *c,int st_h, int st_w);
  void unpooling1(int in_n, int in_c, int in_h, int in_w, float *a, float *b, float *c,int st_h, int st_w){
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
extern "C" void convolute1(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w, float *a, float *b, float *c,
	int st_h, int st_w, int pad);

void convolute1(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w, float *a, float *b, float *c,
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
void deconvolute1(int in_n, int in_c, int in_h, int in_w, int filt_n, int filt_c, int filt_h, int filt_w,
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

void deconvolute2(int in_n, int in_c, int loss_h, int loss_w, int filt_n, int filt_c, int filt_h,int filt_w,
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

