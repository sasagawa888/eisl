(defmodule foo
    (defglobal a 3)

    (defpub a (x)
        (b x))
 
    (defun b (x)
        (+ x a))
        
)
