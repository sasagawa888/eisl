;;; match macro tests

(import "match")
(import "test")


(test (variablep '_a) t)
(test (variablep '_asdf) t)
(test (variablep 1) nil)

(test (extract-variable '(+ _a _b)) ((_a nil)(_b nil)))

(test (extract-variables '(((+ _a _b)(* _a 1)) ((* _b 2)(l _b))) nil nil) ((_a nil)(_b nil)))


(defun foo (x)
    (match x
        ((+ _a _b) (+ _a 2))
        ((- _a _a) (* _a 2))
        ((^ _c _b) (expt _c _b))
        ((asdf _z _y) (list _y _z))
        ((e 1 :rest _a) (list _a))))


(test (foo '(+ 2 3)) 4)
(test (foo '(- 10 10)) 20)
(test (foo '(^ 3 3)) 27)
(test (foo '(asdf 2 3)) (3 2))
(test (foo '(e 1 2 3)) ((2 3)))