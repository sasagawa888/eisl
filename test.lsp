(c-include "<stdio.h>")

(defun ma (a x b)
  (c-lang "res=INT_FLAG | ((INT_MASK & A) * (INT_MASK & X) + (INT_MASK & B));"))

(defun ash (n m)
  (if (>= m 0)
      (c-lang "res = INT_FLAG | ((INT_MASK & N) << (INT_MASK & M));")
      (let ((m1 (- m)))
           (c-lang "res = INT_FLAG | ((INT_MASK & N) >> (INT_MASK & M1));"))))

    
