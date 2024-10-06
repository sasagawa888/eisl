(import "test")

($assert `(1 2) (list 1 2))
($assert `(1 ,2) (list 1 2))
($assert `(1 ,(+ 1 2)) (list 1 3))
($assert `#(1 ,(+ 1 2)) (vector 1 3))
($assert `#(1 ,@(progn '(2 3))) (vector 1 2 3))

;; nested quasiquote representation seems to be underspecified,
;; use a macro defining macro to portably test nested quasiquote behavior.
(defmacro m1 (a)
  `(defmacro m2 (b)
      `(list ,,a ,b)))

(m1 1)
($assert (m2 2) (list 1 2))

