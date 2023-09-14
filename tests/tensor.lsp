;;;;;;;;;;;;;;;;;
;; project to understand Riemannian geometry and general theory of relativity.
;;;  since 2021/5
;;;

(defglobal g (* 6.67430 (expt 10 -11)))
(defglobal m (* 1.0 (expt 10 10)))

(defun / (x y) (quotient x y))

(defun make-metric (r theta)
    (let ((tensor (create-tensor '(4 4))))
        (setf (aref tensor 0 0) (- (- 1 (/ (* 2 G M) r))))
        (setf (aref tensor 1 1) (/  1 (- 1 (/ (* 2 G M) r))))
        (setf (aref tensor 2 2) (expt r 2))
        (setf (aref tensor 3 3) (* (expt r 2) (expt (sin theta) 2)))
        tensor))

(defun create-tensor (dimension)
    (create-array dimension 0))

(defglobal a (make-metric 10 0.3))

(defun tmul (scalar ten)
    (let* ((dim (array-dimensions ten))
           (r (elt dim 0))
           (c (elt dim 1))
           (ten1 (create-tensor dim)))
        (for ((i 0 (+ i 1)))
             ((= i r) ten1)
             (for ((j 0 (+ j 1)))
                  ((= j c) nil)
                  (setf (aref ten1 i j) (* scalar (aref ten i j)))))))


(defun test ()
    (tmul (* 8 *pi* g) a))

    





