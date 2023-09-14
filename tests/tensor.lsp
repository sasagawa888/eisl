;;;;;;;;;;;;;;;;;
;; project to understand Riemannian geometry and general theory of relativity.
;;;  since 2021/5
;;;

(defglobal g (formula 6.67430 * 10 ^ -11))
(defglobal m (formula 1.0 * 10 ^ 10))


(defun make-metric (r theta)
    (let ((tensor (create-tensor '(4 4))))
        (setf (aref tensor 0 0) (lambda () (formula - (1 - 2 * G * M / r))))
        (setf (aref tensor 1 1) (lambda () (formula 1 / (1 - 2 * G* M / r))))
        (setf (aref tensor 2 2) (lambda () (formula r ^ 2)))
        (setf (aref tensor 3 3) (lambda () (formula r ^ 2 * sin(theta) ^ 2)))
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
                  (setf (aref ten1 i j) (* scalar (funcall (aref ten i j))))))))


(defun test ()
    (tmul (* 8 *pi* g) a))

    





