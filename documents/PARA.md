# Parallel
We are planning to add parallel processing capabilities for Easy-ISLisp ver4.

# Spec

```
(defun fib (n)
    (plet ((a (fib (- n 1)))
           (b (fib (- n 2))))
        (+ a b)))

(defun fib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (+ fib (- n 2))))))

```

# idea memo
We will implement parallel processing using the thread-based approach using pthread. It is necessary to manage pointers such as ep that hold the environment for each thread. Prepare ep[PARASIZE] for each thread. If it operates sequentially, the index is 0. If it operates in a thread, indices 1 and above are used.

To avoid conflicts in cell supply from the free list while operating in parallel, we will add a mutex.

Functions like eval and apply will operate independently for each thread. Add arguments and assign the thread number to them. For example, eval(x,1).

## debugging
Now small fibonacci is OK.
#define DEBUG -> print process. env(main) env(th1) env(th2) thread=N

```
> (fib 6)
NILNILNILthread=0
((N( . (N . 6))((N . 66)))((N . )6))((N . 6))((N . thread=2
((N . 6))((N . 6))((N . 4))thread=2
((N . 6))((N . 6))((N . 3))thread=2
((N . 6))((N . 6))((N . 2))thread=2
((N . 6))thread=1
((N . 6))((N . 5))((N . 2))thread=1
((N . 6))((N . 4))((N . 2))thread=1
((N . 6))((N . 3))((N . 2))thread=1
((N . 6))((N . 2))((N . 2))thread=1
((N . 6))((N . 2))((N . 2))thread=1
((N . 6))((N . 3))((N . 2))thread=1
((N . 6))((N . 4))((N . 2))thread=1
((N . 6))((N . 2))((N . 2))thread=1
((N . 6))((N . 2))((N . 2))thread=1
((N . 6))((N . 5))((N . 2))thread=1
((N . 6))((N . 3))((N . 2))thread=1
((N . 6))((N . 2))((N . 2))thread=1
((N . 6))((N . 2))((N . 2))thread=1
((N . 6))((N . 3))((N . 2))thread=1
6))((N . 6))((N . 2))thread=2
((N . 6))((N . 6))((N . 3))thread=2
((N . 6))((N . 6))((N . 4))thread=2
((N . 6))((N . 6))((N . 2))thread=2
((N . 6))((N . 6))((N . 2))thread=2
8
> (quit)

```