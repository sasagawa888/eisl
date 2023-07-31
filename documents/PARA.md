# Parallel functions

# Spec

- (plet form body)  

```
form   ((var1 sexp1)(var2 sexp2)...)
```
- (pcall fun arg ...)
eval (fun arg ...) with paralell

- (pexec arg ...)
execute (progn arg ...) with paralell

- (plock arg ...)
execute (prgn arg ...) with mutex. 

```
pthread_mutex_lock()
arg ...
pthread_mutex_unlock()
```

## example

```
(defun pfib (n)
    (plet ((a (fib (- n 1)))
           (b (fib (- n 2))))
        (+ a b)))

(defun fib (n)
    (the <fixnum> n) 
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (fib (- n 2))))))

(defun ptarai (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (pcall ptarai (ptarai (- x 1) y z)
                      (ptarai (- y 1) z x)
                      (ptarai (- z 1) x y))))

(defun tarai (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
        (tarai (tarai (- x 1) y z)
               (tarai (- y 1) z x)
               (tarai (- z 1) x y))))

(defun pcount (n)
    (pexec (count1 1 (div n 2))
           (count1 (+ (div n 2) 1) n)))

(defun count (n)
    (count1 1 n))

(defun count1 (m n)
    (for ((i m (+ i 1)))
         ((= i n) t)
         (sin (cos (tan i)))))

```

# Thread pooling

queue[] = 1,2,3,... worker_count

worker_count = core_count - 2(main + GC);




