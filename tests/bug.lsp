(import "macro")

(defun rpn (xs)
  (let ((zs nil))
    (dolist (x xs (if (and (consp zs) (null (cdr zs)))  ; (singlep zs) を使ってもよい
                      (car zs)
                    "invalid expression"))
      (if (numberp x)
          (push x zs)
        (let ((b (pop zs)) (a (pop zs)))
          (if (or (null b) (null a))
              (return "stack underflow"))
          (case
           x
           ((+) (push (+ a b) zs))
           ((-) (push (- a b) zs))
           ((*) (push (* a b) zs))
           ((/) (push (quotient a b) zs))
           (t (return "invalid operation"))))))))

