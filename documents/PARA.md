# Parallel functions


| Function              | Description                                    |
| --------------------- | ---------------------------------------------- |
| (mp-create n)         | create n processes. see PARA.md                |   
| (mp-call fun a1 .. an)| apply fun args with multi-process. see PARA.md |
| (mp-exec s1 ... sn)   | progn with multi-process. see PARA.md          |
| (mp-and s1 ... sn)    | parallel and with multi-process. see PARA.md   |    
| (mp-or s1 ... sn)     | parallel and with multi-process. see PARA.md   | 
| (mp-eval n exp)       | evaluate exp in nth child Lisp                 |
| (mp-close)            | close all process. see PARA.md                 |
| (mt-create n)         | create n threads. see PARA1.md                 |
| (mt-call fun a1 .. an)| apply fun args with multi-thread.see PARA1.md  |
| (mt-exec s1 ... sn)   | progn with multi-thread. see PARA1.md          |
| (mt-lock s1 ... sn)   | progn with mutex multi-thread. see PARA1.md    |
| (mt-close)            | close all threads. see PARA1.md                |
| (dp-create n)         | create n distributions. see PARA2.md           |
| (dp-call fun a1 .. an)| apply fun args with distributed. see PARA2.md  |
| (dp-exec s1 ... sn)   | progn with distributed. see PARA2.md           |
| (dp-and s1 ... sn)    | parallel and with distributed. see PARA2.md    |
| (dp-or s1 ... sn)     | parallel or with distributed. see PARA2.md     |
| (dp-transfer fn)      | transfer file to all child Lisp. see PARA2.md  |
| (dp-compile fn)       | compile file in all child Lisp. see PARA2md    |
| (dp-load fn)          | load file to parent and all child Lisp.PARA2.md|
| (dp-close)            | close all distributions. see PARA2.md          |
| (dp-halt)             | close all childs and shutdown see PARA2.md     |



# Multi Process Parallel functions
Easy-ISLisp supports parallel processing with multiprocessing.

# Spec

- (mp-create n) 
Launches n child Lisps.

- (mp-call fun arg1 ... argn) 
Executes arg1 to argn in parallel in child Lisps, then executes function fun with the results and returns the result.

- (mp-exec arg1 ... argn)
Executes arg1 to argn in parallel in child Lisps and returns the result of the argn execution.

- (mp-part sw arg1 ... argn)
Executes arg1 to argn in parallel in child Lisps.
sw == nil
If one of arg returns nil stops exections and return nil,
else  returns the result of the last execution.

sw == t
If one of arg returns non-nil stops exections and return result,
else  returns the result of the last execution.

On macOS mp-part is not available. 

- (mp-let ((sym1 (exp1)) ... (symn (expn))) body) 
Evaluates each exp in parallel in child Lisps, binds its value to sym, executes body, and returns the final result.

- (mp-eval n exp)
Evaluates exp in nth child Lisp.

- (mp-report str)
Display string on parent terminal.

- (mp-close) 
Terminates all child Lisps.


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

# Usage of mp-report function

```
(defun bar (x y)
    (mp-exec (uoo x) (uoo y)))

(defun uoo (x) 
    (let ((stm (create-string-output-stream)))
        (format stm "test1 ~A ~%" x)
        (mp-report (get-output-stream-string stm))
        (sleep 1)
        (format stm "test2 ~A ~%" x)
        (mp-report (get-output-stream-string stm))
        (sleep 1)
        t))

```

# Example of mp-part

```
;(primep* 100000000000031)
(defun primep* (n)
    (if (= (mod n 2) 0)
        nil
        (let* ((limit (isqrt n))
               (span (div limit 5)))
            (mp-part nil (coprimep n 3 span)
                         (coprimep n (near-odd span) (* 2 span ))
                         (coprimep n (near-odd (* 2 span)) (* 3 span))
                         (coprimep n (near-odd (* 3 span)) (* 4 span))
                         (coprimep n (near-odd (* 4 span)) limit)))))

(defun near-odd (n)
    (if (= (mod n 2) 0)
        (- n 1)
        n))


(defun coprimep (n s e)
    (cond ((> s e) t)
          ((= (mod n s) 0) nil)
          (t (coprimep n (+ s 2) e))))

```

# Thread Parallel functions

# Spec

- (mt-create n) create n threads.

- (mt-close) close all threads.

- (mt-call fun arg ...)
eval (fun arg ...) with paralell

- (mt-exec arg ...)
execute (progn arg ...) with paralell

- (mt-lock arg ...)
execute (prgn arg ...) with mutex. 

```
pthread_mutex_lock()
execute arg ...
pthread_mutex_unlock()
```

## example

```
(defun ptarai (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (mt-call #'ptarai (tarai (- x 1) y z)
                          (tarai (- y 1) z x)
                          (tarai (- z 1) x y))))

(defun tarai (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (tarai (tarai (- x 1) y z)
               (tarai (- y 1) z x)
               (tarai (- z 1) x y))))

(defun pcount (n)
    (mt-exec (count1 1 (div n 2))
             (count1 (+ (div n 2) 1) n)))

(defun count (n)
    (count1 1 n))

(defun count1 (m n)
    (for ((i m (+ i 1)))
         ((= i n) t)
         (sin (cos (tan i)))))

```

# Thread pooling
source code parallel.c 

mt-call.. f_mt_call
mt-exec.. f_mt_exec
mp-lock.. f_mt_lock

queue[] = 1,2,3,... worker_count

worker_count = core_count - 1(main + GC);

core_count is count of CPU's multicores
e.g. icore5 hexa core => 6

initital
queue  [1,2,3,4]  hexa core
queue_pt = 4;

eval_para(arg)
dequeue [2,3,4]
queue_pt = 3
main thread send signal to worker1 thread.
worker1 eval(arg) -> para_output[1]=result.
worker1 send signal to main thread.
enqueue [2,3,4,1]
queue_pt = 4

![GC](para1.png)

![parallel](para1.png)

## Example
see example/mandelbrot.lsp

![mandelbrot](mandelbrot.png)


# Distributed Parallel functions


# Invoke 
eisl -n on child machine terminal.
EISL runs with network mode. 


eisl on parent machine terminal.
and (dp-create ) to establish TCP/IP between child Lisp.

# Spec

- eisl -n: Launches child Lisps in network mode with the -n option.

- (dp-create c0 c1 …cn): Provides IP addresses of child machines to establish TCP/IP communication with the parent Lisp.

- (dp-call fun a0 a1 ... an): Distributed parallel version of the call syntax.

- (dp-exec a0 a1 ... an): Distributed parallel version of progn

- (dp-and a0 a1 ... an): Paralle version and.
Executes arg1 to argn in parallel in child Lisps.
If one of arg returns nil stops exections and return nil,
else  returns the result of the first execution.

- (dp-or a0 a1 ... an): Paralle version or.
If one of arg returns non-nil stops exections and return result,
else  returns the result of the first execution.

- (dp-transfer fn): Transfers file fn to all child machines from the parent machine.

- (dp-compile fn): Compiles file fn on both parent and child machines.

- (dp-load fn): Loads file fn on both parent and child machines.

- (dp-eval n sexp): Evaluates S-expression sexp on the nth child Lisp for testing.

- (dp-close): Sends termination command to child machines and closes communication.

- (dp-halt): Sends termination command to child machines and closes communication.
  Shutdown OS in child machine.

- (dp-trace): Display received data from child.  

- (dp-untrace): Not display received data from child.

## example

```
(defun ptarai (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (dp-call #'ptarai (tarai (- x 1) y z)
                          (tarai (- y 1) z x)
                          (tarai (- z 1) x y))))

(defun tarai (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (tarai (tarai (- x 1) y z)
               (tarai (- y 1) z x)
               (tarai (- z 1) x y))))

(defun pcount (n)
    (dp-exec (count1 1 (div n 2))
             (count1 (+ (div n 2) 1) n)))

(defun count (n)
    (count1 1 n))

(defun count1 (m n)
    (for ((i m (+ i 1)))
         ((= i n) t)
         (sin (cos (tan i)))))


;(dp-create "xxx.xxx.xxx.xxx" "yyy.yyy.yyy.yyy")
;(primep* 100000000000031)
(defun primep* (n)
    (cond ((= n 2) t)
          ((= (mod n 2) 0) nil)
          (t (let* ((limit (isqrt n))
                    (span (div limit 2)))
                 (dp-and (coprimep n 3 span)
                         (coprimep n (near-odd span) limit))))))

(defun near-odd (n)
    (if (= (mod n 2) 0)
        (- n 1)
        n))


(defun coprimep (n s e)
    (cond ((> s e) t)
          ((= (mod n s) 0) nil)
          (t (coprimep n (+ s 2) e))))

(defun primep (n)
    (cond ((= n 2) t)
          ((= (mod n 2) 0) nil)
          (t (coprimep n 3 (isqrt n)))))



```

![Child-Lisp](para22.png)
![Parent-Lisp](para23.png)
![Create](para24.png)
![Transfer](para25.png)
![Compile](para26.png)
![Code](para27.png)
![Time](para28.png)
![Close](para29.png)



