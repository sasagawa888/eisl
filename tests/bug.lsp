
(defun test-let*-shadow1 (n)
  (let* ((x (+ n 1))
         (x1 (+ x 10)))
    (+ x1 1)))

