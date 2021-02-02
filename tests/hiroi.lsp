;; test from M.Hiroi home page

(defun pascal (n)
    (for ((n n (- n 1))
          (xs
          '(1)
          (maplist (lambda (xs)
                      (if (singlep xs)
                          (car xs)
                          (+ (car xs) (cadr xs)))) (cons 0 xs))) )
         ((= n 0))
         (format (standard-output) "~A~%" xs)))

(defun singlep (xs)
    (and xs (null (cdr xs))) )

(defun cadr (x)
    (car (cdr x)) )
