;;; match macro tests

(import "elixir")

(defpattern fib
    (0 1)
    (1 1)
    (_n (+ (fib (- _n 1)) (fib (- _n 2)))))

(defun fib* (n)
    (cond ((= n 0) 1)
          ((= n 1) 1)
          (t (+ (fib* (- n 1)) (fib* (- n 2))))))

(defpattern bar
    (nil nil)
    ((_a :rest _b) (print _a) (bar _b)))

(defpattern foo
    ((a _a) (pipe _a |> (cos) |> (sin)))
    ((b _b) (pipe _b |> (tan) |> (abs))))