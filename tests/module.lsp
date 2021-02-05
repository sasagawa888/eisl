;; test defmodule syntax

(defmodule foo
    (defglobal a 3)
    (defpublic bar (x)
        (+ (boo x) a (gfib x)) )
    
    (defun boo (x)
        (+ x 1) )
    
    (defpublic baz (x)
        (uoo x) )
    
    (defmacro uoo (x)
        `(+ ,x ,x) )

    (defgeneric gfib (n)
        (:method
         ((n <integer>))
         (cond ((= n 1) 1)
               ((= n 2) 1)
               (t (+ (gfib (- n 1)) (gfib (- n 2)))))))
    
    (defpublic fact (n)
        (if (= n 0)
            1
            (* n (fact (- n 1)))))
    
    (defpublic goo (x)
        (if (= x 0)
            t
            (goo (- x 1))))
)

