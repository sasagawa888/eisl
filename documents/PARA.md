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

Functions like eval and apply will operate independently for each thread. Add arguments and assign the thread number to them. For example, eval(1).