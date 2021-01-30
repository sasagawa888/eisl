
(defmacro uoo (x)
    `(+ ,x ,x))


(defmodule foo
    (defglobal a 3)

    (defpublic bar (x)
        (+ (boo x) (gfib 5)))
 
    (defun boo (x)
        (+ x a))
    
    (defpublic baz (x)
        (uoo x))

    (defgeneric gfib (n)
    (:method ((n <integer>)) (cond ((= n 1) 1)
                                   ((= n 2) 1)
                                   (t (+ (gfib (- n 1)) (gfib (- n 2)))) )))

)

 
