;;; bug compiled code

(defun sum (xs)
  (let ((a 0))
    (mapc (lambda (x) (setq a (+ a x)) (print a)) xs)
    a))

(defun sum-a (xs)
  (let ((a 0))
    (print (mapcar (lambda (x) (setq a (+ a x)) a) xs))
    a))

