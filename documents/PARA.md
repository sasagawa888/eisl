# Multi Process Parallel functions
Easy-ISLisp supports parallel processing with multiprocessing.

# Spec

```
(mp-create n) Launches n child Lisps.

(mp-call fun arg1 ... argn) Executes arg1 to argn in parallel in child Lisps, then executes function fun with the results and returns the result.

(mp-exec arg1 ... argn) Executes arg1 to argn in parallel in child Lisps and returns the result of the last execution.

(mp-let ((sym1 (exp1)) ... (symn (expn))) body) Evaluates each exp in parallel in child Lisps, binds its value to sym, executes body, and returns the final result.

(mp-close) Terminates all child Lisps.

```

# example

```
(defun tarai* (x y z)
    (if (<= x y)
        y
        (mp-call #'tarai* (tarai (- x 1) y z) 
                          (tarai (- y 1) z x)
                          (tarai (- z 1) x y))))

(defun tarai (x y z)
    (if (<= x y)
        y
        (tarai (tarai (- x 1) y z)
               (tarai (- y 1) z x)
               (tarai (- z 1) x y))))



(defun fib* (n)
    (mp-call #'+ (fib (- n 1))
                 (fib (- n 2))))


(defun fib (n)
    (cond ((= n 1) 1)
          ((= n 2) 1)
          (t (+ (fib (- n 1)) (fib (- n 2)))) ))


Easy-ISLisp Ver3.90
> (mp-create 3)
T
> (load "./tests/para.lsp")
T
> (tarai* 12 6 0)
12
> (time (tarai* 12 6 0))
Elapsed Time(second)=4.165187
<undef>
> (time (tarai 12 6 0))
Elapsed Time(second)=5.146046
<undef>
> (time (fib* 32))
Elapsed Time(second)=1.092517
<undef>
> (time (fib 32))
Elapsed Time(second)=1.786850
<undef>
> 

```

# Compile

```
Easy-ISLisp Ver3.90
> (compile-file "./tests/para.lsp")
type inference
warning TARAI numerical argument type mismatch (- X 1)
warning TARAI type mismatch (IF (<= X Y) Y (TARAI (TARAI (- X 1) Y Z) (TARAI (- Y 1) Z X) (TARAI (- Z 1) X Y)))
initialize
pass1
pass2 
compiling TARAI* 
compiling TARAI 
compiling FIB* 
compiling FIB 
finalize
invoke CC
T
> (mp-create 3)
T
> (load "./tests/para.o")
T
> (time (tarai* 12 6 0))
Elapsed Time(second)=0.314902
<undef>
> (time (tarai 12 6 0))
Elapsed Time(second)=0.432586
<undef>
> (time (fib* 32))
Elapsed Time(second)=0.092356
<undef>
> (time (fib 32))
Elapsed Time(second)=0.156763
<undef>
> (mp-close)
T
> 

```
