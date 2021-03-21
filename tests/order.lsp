
(defun foo ()
    (bar (format (standard-output) "~A " 1)
         (format (standard-output) "~A " 2)
         (format (standard-output) "~A " 3)))

(defun bar (x y z) nil)

#|
> (compile-file "tests/order.lsp")
> (load "tests/order.o")
T
> (foo)
3 2 1 NIL
> 
|#
