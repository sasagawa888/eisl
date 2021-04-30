;;; match macro tests

(import "elixir")

(defpattern deriv
    (((^ _x _n) _x) `(* ,_x ,(- _n 1))))

(defpattern fib
    ((0) 1)
    ((1) 1)
    ((_n) (+ (fib (- _n 1)) (fib (- _n 2)))))

(defpattern sum
    ((nil) 0)
    (((_a :rest _b)) (+ _a (sum _b))))

(defpattern talk
    (((I love _a)) (list _a 'love 'me))
    (((hello _a)) (list 'good-by _a))
    (else (list 'I 'do 'not 'know)))

(defpattern foo
    (((a _a)) (pipe _a |> (cos) |> (sin)))
    (((b _b)) (pipe _b |> (tan) |> (abs))))


(defun uoo (x y)
    (match x
        (nil y)
        ((0 :rest _x) (uoo _x (+ y 1)))
        ((1 :rest _x) (uoo _x (+ y 2)))))

(defun fib* (n)
    (cond ((= n 0) 1)
          ((= n 1) 1)
          (t (+ (fib* (- n 1)) (fib* (- n 2))))))


(defpattern find
    ((nil) nil)
    (((3 (4 6) :rest _x)) (format (standard-output) "~A~%" _x))
    (((_a :rest _b)) (find _b)))



