;;multi-process

(defun pfib (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (mp-call #'+ (fib (- n 1)) (fib (- n 2))))))


(defun fib1 (n)
    (mp-let ((a (fib (- n 1)))
             (b (fib (- n 2))))
        (+ a b)))

(defun fib (n)
    ;(the <fixnum> n) 
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib (- n 1)) (fib (- n 2))))))


;(mp-create 5)
;(primep* 100000000000031)
(defun primep* (n)
    (cond ((= n 2) t)
          ((= (mod n 2) 0) nil)
          (t (let* ((limit (isqrt n))
                    (span (div limit 5)))
                 (mp-part nil (coprimep n 3 span)
                              (coprimep n (near-odd span) (* 2 span ))
                              (coprimep n (near-odd (* 2 span)) (* 3 span))
                              (coprimep n (near-odd (* 3 span)) (* 4 span))
                              (coprimep n (near-odd (* 4 span)) limit))))))

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

(import "unistd")

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
