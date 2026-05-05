

(defun test-lambda-nested1 (n)
  ((lambda (x)
     ((lambda (y)
        (+ x y))
      10))
   n))


(defun difference (xs ys)
  (cond ((null xs) nil)
        ((member (car xs) ys)
         (difference (cdr xs) ys))
        (t (cons (car xs)
                 (difference (cdr xs) ys)))))