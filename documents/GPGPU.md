# GPGPU

# Install
You can also compile EISL with nvcc(CUDA) instead of gcc.

On linux terminal type "make -f cudamake" and "sudo make install"

Now, I am adding function using CUDA

see tests/gpu.lsp
extended array for float.
```
(defglobal a #2f((1.0 2.0)(3.0 4.0)))
(defglobal b #2f((1.0 2.0)(3.0 4.0)))
(gpu-mult a b)
(gpu-add a b)
```
# Extend
extended create-array builtin-function.
it can generate array for float. e.g.
```
(create-array '(3000 3000) 'rand 'float)
```

# Bench

```
(defglobal z (create-array '(3000 3000) 'rand 'float))

(defun test1 ()
    (gpu-mult z z) )

(defun test2 (n)
  (for ((i n (- i 1)))
       ((< i 0) t)
       (test1)))

Easy-ISLisp Ver1.77
> (time (test1))
Elapsed Time(second)=0.074256
<undef>
> (time (test1))
Elapsed Time(second)=0.059127
<undef>
> (time (test2 10))
Elapsed Time(second)=0.582411
<undef>
> (time (test2 10))
Elapsed Time(second)=0.540693
<undef>
> 

```



# Specification

(gpu-accuracy mt1 ls)

return accuracy rate as float number. mt1 is set of row-vector.Each row-vector is onehot. ls is list each element is label integer number.

(gpu-activate mt fun) 

apply fun to mt. fun is symbol(sigmoid, tanh, relu softmax)

(gpu-adagrad weight,h,grad,lr) 

adagrad optimizer return list (h,w)

(gpu-adam w m v grad lr) 

adam optimizer return list (m1,v1,w1)

(gpu-add mt1,mt2) 

generate matrix mt1+mt2. if mt1 or mt2 is row vector, expand size to matrix. This function is for bias add in DL.

(analizer ts,id) 

display id-number,max-element,min-element,average. for debug.

(gpu-average mt) 

caluculate average of row-vector and generate row-vector that each element is average. For Deep-Learning.

(gpu-convolute ts1 ts2 (st_h st_w) pad) 

convolution with input-tensor(ts1), filter-tensor(ts2), stride(st_h,st_w), padding(pad)

(gpu-correct mt1 ls) 

return correct number as integer number. mt1 is set of row-vector.Each row-vector is onehot. ls is list each element is label integer number.

(gpu-deconvolute ts1 ts2 (st_h st_w) pad) 

deconvolution with input-tensor(ts1), filter-tensor(ts2), stride(st_h,st_w), padding(pad) 1st arg loss-tensor 2nd arg filter-tesnor

(gpu-diff mt1 mt2 fun)

for each element multiply differntial of mt2 and mt1. fun is symbol (sigmoid tanh relu).

(gpu-dropout ts, dropout-rate)

generate mask matrix or tensor for dropout

(gpu-emult mt1 mt2)

generate Hadamard matrix.

(gpu-full ts)

transfer from 4 DIM tensor to matrix.

(gpu-gradfilter ts1 ts2 ts3 (st_h st_w) pad) 

gradient by backpropagation. ts1 is input-tesor, ts2 is filter-tensor, ts3 is loss-tensor, st_h and st_w are stride size, pad is padding size. calculate gradient of filter.

(gpu-ident n) 

generate ident matrix of size n.

(gpu-loss mt1 mt2 fun)

generate float that is average of loss. fun is symbol square or cross. square means mean_square function, and cross means cross_entropy function. mt1 is calculated data matrix , mt2 is train data matrix. each data is row vector.


(gpu-momentum mt1 mt2 mt3 lr) 

for each element v = 0.5 mt2(x,y) - lr mt3(x,y). w = mt1 + v. return list (v w) 

(gpu-mult mt1 mt2)

generate matrix product of mt1 and mt2 with cuBLAS. 

(gpu-pooling tensor (st_h st_w)) 

pooling with stride st_w st_w. size of H and W must be less 1000. max 999*999. 
return list (tensor-for-forward tensor-for-backward)


(gpu-random_select mt1 mt2 n) 

select same row data from matrix(mt1) and matrix(mt2)
reshape(x, i)


(gpu-rms weight h grad lr) 

RMSprop optimizer return list (h w)


(gpu-sgd mt1 mt2 lr dr) 

element of mt1 - element of mt2*lr. and dropout with rate dr.


(gpu-normalizer ts) 

calculate average of nth data and sub each elemet the average. when matrix , nothing to do

(gpu-sub mt1 mt2) 

generate matrix mt1-mt2. It is possible to adapt tensor

(gpu-sum mt) 

return sum of elements


(gpu-trace mt) 

return float number. It is trace of matrix.


(gpu-transpose mt) 

generate transposed matrix

(gpu-unfull mt h w) 

transfer from matrix to 4 DIM tensor. tensor(N,C,H,W). N is row size of matrix. C is 1.


(gpu-unpooing ts1 ts2 (st_h st_w)) 

unpooling with stride st. ts1 is sparse tensor that save index of max element. ts2 is loss tensor.

(gpu-copy ts)

return copy of ts
