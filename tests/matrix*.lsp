;;; another matrix library

(defun matrixp (x)
  (instancep x (class <matrix>)))

;;;  matrix number
(defclass <matrix> ()
  ((data :accessor data :initform 0 :initarg data)))

;;; constructer
(defun matrix (x)
  (create (class <matrix>) 'data x))    

;;; display matrix
(defun mprint (x)
    (print (data x)))

;;; matrix operator
(defun madd (x y)
  (matrix (madd1 x y)))

(defun madd1 (x y)
    (let* ((x1 (data x)) 
           (y1 (data y))
           (dim (array-dimensions x1))
           (dx (elt dim 0))
           (dy (elt dim 1))
           (z1 (create-array dim)))
        (for ((i 0 (+ i 1)))
             ((>= i dx) z1)
             (for ((j 0 (+ j 1)))
                  ((>= j dy))
                  (set-aref (+ (aref x1 i j) (aref y1 i j)) z1 i j)))))
          

(defun msub (x y)
  (matrix (msub1 x y)))


(defun madd1 (x y)
    (let* ((x1 (data x)) 
           (y1 (data y))
           (dim (array-dimensions x1))
           (dx (elt dim 0))
           (dy (elt dim 1))
           (z1 (create-array dim)))
        (for ((i 0 (+ i 1)))
             ((>= i dx) z1)
             (for ((j 0 (+ j 1)))
                  ((>= j dy))
                  (set-aref (- (aref x1 i j) (aref y1 i j)) z1 i j)))))
          
