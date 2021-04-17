;;; match macro tests

(import "elixir")

(defpattern fib
    (0 1)
    (1 1)
    (_n (+ (fib (- _n 1)) (fib (- _n 2)))))

(defpattern uoo
    ((a _a) (pipe _a |> (cos) |> (sin)))
    ((b _b) (pipe _b |> (tan) |> (abs))))