(defun foo (x)
   (bar y "abc")
   (+ x 1))

(defun bar (x y)
   (string-append x y))


(defglobal y 1)