; 再帰版
(defun rlast-pair (xs)
  (if (null (cdr xs))
      xs
      (rlast-pair (cdr xs))))

(defun fact (n)
  (cond ((= n 0) #X1)
         (t (fact (- n 1)))))