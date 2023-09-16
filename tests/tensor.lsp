;;;;;;;;;;;;;;;;;
;; project to understand Riemannian geometry and general theory of relativity.
;;;  since 2021/5
;;; calculating   Schwarzschild 

(defglobal G 6.67430e-11)
(defglobal M 5.972e24)
(defglobal C 2.99792458e8)

(defun / (x y) (quotient x y))

(defun make-metric (r theta)
    (let ((tensor (create-tensor '(4 4))))
        (setf (aref tensor 0 0) (- 1 (/ (* 2 G M) (* r (expt c 2)))))
        (setf (aref tensor 1 1) (- (/  1 (- 1 (/ (* 2 G M) (* r (expt c 2)))))))
        (setf (aref tensor 2 2) (- (expt r 2)))
        (setf (aref tensor 3 3) (- (* (expt r 2) (expt (sin theta) 2))))
        tensor))

(defun create-tensor (dimension)
    (create-array dimension 0))



(defun distance (ten dx)
    (let* ((dim (array-dimensions ten))
           (r (elt dim 0))
           (c (elt dim 1))
           (result 0))
        (for ((i 0 (+ i 1)))
             ((= i r) result)
             (for ((j 0 (+ j 1)))
                  ((= j c) nil)
                  (setq result (+ result (* (aref ten i j) (elt dx i) (elt dx j))))))))

(defglobal a (make-metric 10 0.3))

(defun test ()
    (tmul (* 8 *pi* g) a))

    





