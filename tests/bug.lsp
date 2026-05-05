


(defun test-map-lambda9 (lst)
  (let ((a 100))
    (mapcar (lambda (x)
              ((lambda (y) (+ x y a)) 10))
            lst)))
