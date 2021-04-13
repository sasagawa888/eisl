

(defun foo (x y)
    (+ x y) )

(defun bar (x y)
    (* x y) )

(defun boo (x y)
    (- x y) )

(defun uoo (x)
    (pipe x |> (foo 1) |> (bar 2) |> (boo 3)))
