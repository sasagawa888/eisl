(defun foo (x)
    (bar y "abc")
    (+ x 1) )

;;; asdf
(defun bar (x y)
    (string-append x y) )


#|
漢字φψ＋＋
(cons (eval (read-exp)) (cons (eval (read-exp)) nil) -> it make pair of x and y.
|#


(defglobal y 1)
