

(defun test-lambda-shadow1 (n)
  ;; variable shadowing
  ((lambda (x)
     (let ((x (+ x 10)))
       (+ x 1)))
   n))


(defun test-lambda-shadow2 (n)
  ;; deeper shadow
  ((lambda (x)
     (let ((x (+ x 10)))
       (let ((x (+ x 20)))
         (+ x 1))))
   n))

(defun test-let-parallel (x)
  (let ((x (+ x 1))
        (y x))
    (+ x y)))