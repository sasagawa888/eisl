;; example for C wrapper

(c-include "<stdio.h>")

;;bit shift 
(defun ash (n m)
  (if (>= m 0)
      (c-lang "res = INT_FLAG | ((INT_MASK & N) << (INT_MASK & M));")
      (let ((m1 (- m)))
        (c-lang "res = INT_FLAG | ((INT_MASK & N) >> (INT_MASK & M1));"))))
