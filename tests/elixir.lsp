;;; match macro tests

(import "elixir")
(import "test")


(test (variablep '_a) t)
(test (variablep '_asdf) t)
(test (variablep 1) nil)

(test (extract-variable '(+ _a _b)) ((_a nil)(_b nil)))

(test (extract-variables '(((+ _a _b)(* _a 1)) ((* _b 2)(l _b))) nil nil) ((_a nil)(_b nil)))


(defpattern fib
    (0 1)
    (1 1)
    (_n (+ (fib (- _n 1)) (fib (- _n 2)))))

(defpattern foo
    ((+ _a _b) (+ _a 2))
    ((- _a _a) (* _a 2))
    ((^ _c _b) (expt _c _b))
    ((asdf _z _y) (list _y _z))
    ((e 1 :rest _a) (list _a)))


(defpattern boo
    ((* (* _a _b) _c) (list _a _b _c))
    ((e 1 :rest _a) (list _a))
    (else 1))

(test (foo '(+ 2 3)) 4)
(test (foo '(- 10 10)) 20)
(test (foo '(^ 3 3)) 27)
(test (foo '(asdf 2 3)) (3 2))
(test (foo '(e 1 2 3)) ((2 3)))

(defpattern uoo
    ((a _a) (pipe _a |> (cos) |> (sin)))
    ((b _b) (pipe _b |> (tan) |> (abs))))