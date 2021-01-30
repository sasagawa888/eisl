
(defmacro uoo (x)
    `(+ ,x ,x))


(defmodule foo
    (defglobal a 3)

    (defpublic bar (x)
        (boo x))
 
    (defun boo (x)
        (+ x a))
    
    (defpublic baz (x)
        (uoo x))
)

 
