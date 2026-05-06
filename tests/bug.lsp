

(defun test4 ()
  ;; for inside lambda
  (mapcar
   (lambda (x)
     (let ((sum 0))
       (for ((i 0 (+ i 1)))
            ((>= i 3))
            (setq sum (+ sum x i)))
       sum))
   '(1 2 3)))