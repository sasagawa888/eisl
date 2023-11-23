(defmacro foo (a) `(list #(1 ,a)))

;(foo 2)
;return (#(1 2))

(defmacro bar (a) `(list #2a((1 ,a)(2 , a))))
;(bar 3)
;(#2a((1 3) (2 3)))

