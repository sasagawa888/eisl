;;;;;;;;;;;;;;;;;
;; project to understand Riemannian geometry and general theory of relativity.
;;;  since 2021/5
;;;

(defun create-tensor (dimension)
    (create-array dimension 0.0))

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
