
(defun test-labels9 (n)
  ;; labels body has multiple forms
  (labels ((f (x)
             (+ x 1)))
    (f n)
    (f (+ n 10))))