
(test (bits '(+ 1 2))
      (0 0 1 0 1 0 0 0 0 0 1 0 1 0 1 1 0 0 1 0 0 0 0 0 0 0 1 1 0 0 0 1 0 0 1 0 0))

(test (+ 1 2)
      (0 0 0 0 0 0 0 0 0 0 0 0 00 0 0 0 0 0 1 2 3 4 5 1 3 4 2 2 3 3 3 3))


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

(tests aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
       aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa)
(test 1 2)
