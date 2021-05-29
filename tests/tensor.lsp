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