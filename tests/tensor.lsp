;;;;;;;;;;;;;;;;;
;; project to understand Riemannian geometry and general theory of relativity.
;;;  since 2021/5
;;;


;; make 4D vector
(defun make-vector (x1 x2 x3 x4)
    (let ((vector (create-vector 4 0)))
        (setf (elt vector 0) x1)
        (setf (elt vector 1) x2)
        (setf (elt vector 2) x3)
        (setf (elt vector 3) x4)
        vector))

(defun make-metric (v1 v2)
    (let ((tensor (create-tensor '(4 4))))
        (for ((i 0 (+ i 1)))
             ((> i 3) tensor)
             (for ((j 0 (+ j 1)))
                  ((> j 3) t)
                  (setf (aref tensor i j) (* (elt v1 i) (elt v2 j)))))
        tensor))

(defun create-tensor (dimension)
    (create-array dimension 0))

(defun symmetricp (tensor)
    (block exit
        (for ((i 0 (+ i 1)))
             ((> i 3) t)
             (for ((j 0 (+ j 1)))
                  ((> j 3) t)
                  (if (not (= (aref tensor i j)
                              (aref tensor j i)))
                      (progn
                      (print i)
                      (print j)        
                      (return-from exit nil)))))))

(defglobal a (make-vector 1 2 2 1))
(defglobal b (make-vector 2 1 1 2))
(defglobal c (make-metric a a))

#|
(defun rank (x)
    (length (array-dimensions x)))

(defun metric-tensor (n)
    (create-tensor `(,n ,n)))

;;e.g. p203 tashiro
(defglobal g 
    (#2a((1 0 0) 
         (0 (lambda (r) (* r r)) 0)
         (0 0 (lambda (r sita) (* (^ r 2)(^ (sin sita) 2)))))))
         
(defun ^ (base expo)
    (expt base exp))

(defun gamma (i j k)
    (* 0.5 (+ (round (g i j) (x k)) (round (g i k) (x i)) (round (g k j) (x i)))))

(defun r (i j k l)
    (+ (- (round (gamma i j l) (x k)) (round (gamma i j k) (x l)))
       (- (* (gamma m j l) (gamma i m k)) (* (gamma m j k) (gamma i m l))))) 

(defmacro sum (x y)
    (let ((dim1 (array-dimensions x))
          (dim2 (array-dimensions y)))
        (cond ((= (length dim1) 2) (sum2 x y dim1))
              ((= (length dim1) 3) (sum3 x y dim1))
              ((= (length dim1) 4) (sum3 x y dim1)))))

(defmacro sum4 (x y dim))

|#

