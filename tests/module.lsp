(defmodule foo
    (defglobal a 3)

    (defpub bar (x)
        (boo x))
 
    (defun boo (x)
        (+ x a))
        
)

