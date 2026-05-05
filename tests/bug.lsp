

(defun test-lambda-nested1 (n)
  ((lambda (x)
     ((lambda (y)
        (+ x y))
      10))
   n))

