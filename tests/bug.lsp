
(defun test-let*-shadow1 (n)
  (let* ((x (+ n 1))
         (x (+ x 10)))
    (+ x 1)))
