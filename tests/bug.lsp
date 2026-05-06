


(defun test8 ()
  ;; labels + lambda + for
  (labels ((foo (x)
             (let ((sum 0))
               (for ((i 0 (+ i 1)))
                    ((>= i 3))
                    (setq sum (+ sum x i)))
               sum)))
    (mapcar (lambda (n) (foo n)) '(10 20 30))))
