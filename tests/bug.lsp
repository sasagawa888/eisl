(import "elixir")

(defun uoo (x y)
    (match x
        (nil y)
        ((0 :rest _x) (uoo _x (+ y 1)))
        ((1 :rest _x) (uoo _x (+ y 2)))))