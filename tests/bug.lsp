

(import "match")
(import "test")


(test (variablep '_a) t)
(test (variablep '_asdf) t)
(test (variablep 1) nil)

(test (extract-variable '(+ _a _b)) ((_a nil)(_b nil)))

(test (extract-variables '(((+ _a _b)(* _a 1)) ((* _b 2)(l _b))) nil nil) ((_a nil)(_b nil)))

