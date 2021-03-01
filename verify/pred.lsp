(import "test")
;;;
;;;  chapter5  Predicates
;;;

($ap 1 "Predicates")

;;;
;;; function EQ
;;;
($ap 2 "eq" P.26)
(test (eq () ()) t)
(test (eq '() '()) t)
(test (eq 'a 'a) t)
(test (eq 'a 'A) t)
(test (eq 'a 'b) nil)
(test (eq 'f 'nil) nil)
;;(test (eq 2 2) t)						; nil or t (IDEF)
(test (eq 2 2.0) nil)
;;(test (eq 100000000 100000000) nil)			; nil or t (IDEF)
;;(test (eq 10.00000 10.0) nil)				; nil or t (IDEF)
(test (eq (cons 1 2) (cons 1 2)) nil)
(test (let ((x '(a))) (eq x x)) t)
;;(test (eq '(a) '(a)) nil)					; nil or t (IDEF)
;;(test (let ((x '(b)) (y '(a b))) (eq x (cdr y))) nil)	; nil or t (IDEF)
;;(test (eq '(b) (cdr '(a b))) nil)				; nil or t (IDEF)
(test (let ((p (lambda (x) x))) (eq p p)) t)
(test (let ((x "a")) (eq x x)) t)
;;(test (eq "a" "a") nil)					; nil or t (IDEF)
(test (let ((x "")) (eq x x)) t)
;;(test (eq "" "") nil)					; nil or t (IDEF)
(test (eq #\a #\A) nil)
;;(test (eq #\a #\a) t)					; nil or t (IDEF)
;;(test (eq #\space #\Space) t)				; nil or t (IDEF)
;;(test (eq #\space #\space) t)				; nil or t (IDEF)
;;;
($argc eq 2 0 0)

;;;
;;; function (EQL obj1 obj2) --> boolean
;;;
($ap 2 "eql" P.26)
(test (eql () ()) t)
(test (eql '() '()) t)
(test (eql 'a 'a) t)
(test (eql 'a 'A) t)
(test (eql 'a 'b) nil)
(test (eql 'f 'nil) nil)
(test (eql 2 2) t)
(test (eql 2 2.0) nil)
(test (eql 100000000 100000000) t)
(test (eql 10.00000 10.0) t)
(test (eql (cons 1 2) (cons 1 2)) nil)
(test (let ((x '(a))) (eql x x)) t)
;;(test (eql '(a) '(a)) nil)					; nil or t (IDEF)
;;(test (let ((x '(b)) (y '(a b))) (eql x (cdr y))) nil)	; nil or t (IDEF)
;;(test (eql '(b) (cdr '(a b))) nil)				; nil or t (IDEF)
(test (let ((p (lambda (x) x))) (eql p p)) t)
(test (let ((x "a")) (eql x x)) t)
;;(test (eql "a" "a") nil)					; nil or t (IDEF)
(test (let ((x "")) (eql x x)) t)
;;(test (eql "" "") nil)					; nil or t (IDEF)
(test (eql #\a #\A) nil)
(test (eql #\a #\a) t)
(test (eql #\space #\Space) t)
(test (eql #\space #\space) t)
;;;
($argc eql 2 0 0)
;;;
(test (eql *most-negative-float* *most-negative-float*) t)
(test (eql *most-negative-float* *most-positive-float*) nil)

;;;
;;; function (EQUAL obj1 obj2) --> boolean
;;;
($ap 2 "equal" P.28)
(test (equal 'a 'a) t)
(test (equal 2 2) t)
(test (equal 2 2.0) nil)
(test (equal '(a) '(a)) t)
(test (equal '(a (b) c) '(a (b) c)) t)
(test (equal (cons 1 2) (cons 1 2)) t)
(test (equal '(a) (list 'a)) t)
(test (equal "abc" "abc") t)
(test (equal (vector 'a) (vector 'a)) t)
(test (equal #(a b) #(a b)) t)
(test (equal #(a b) #(a c)) nil)
(test (equal "a" "A") nil)
;;;
($argc equal 2 0 0)
;;;
(test (equal 2.0 2.0) t)
(test (equal *most-negative-float* *most-negative-float*) t)
(test (equal *most-negative-float* *most-positive-float*) nil)
(test (equal "" "") t)
(test (equal (create-string 1000 #\a) (create-string 1000 #\a)) t)
(test (equal (create-string 1000 #\a) (create-string 1000 #\b)) nil)
(test (equal #() #()) t)
(test (equal #(a #(b) c) #(a #(b) c)) t)
(test (equal #(a #(b) c) #(a #(d) c)) nil)
(test (equal (create-vector 1000 'a) (create-vector 1000 'a)) t)
(test (equal (create-vector 1000 'a) (create-vector 1000 'b)) nil)
(test (equal (create-array () 'a) (create-array () 'a)) t)
(test (equal (create-array () 'a) (create-array () 'b)) nil)
(test (equal (create-array '(1 2 3) 'a) (create-array '(1 2 3) 'a)) t)
(test (equal (create-array '(1 2 3) 'a) (create-array '(1 2 3) 'b)) nil)

;;;
;;; function (NOT obj) --> boolean
;;;
($ap 2 "not" P.29)
(test (not t) nil)
(test (not '()) t)
(test (not 'nil) t)
(test (not nil) t)
(test (not 3) nil)
(test (not (list)) t)
(test (not (list 3)) nil)
;;;
($argc not 1 0 0)
($predicate not $null)

;;;
;;; special form (AND form*) --> <object>
;;;
($ap 2 "and" P.29)
(test (and (= 2 2) (> 2 1)) t)
(test (and (= 2 2) (< 2 1)) nil)
(test (and (eql 'a 'a) (not (> 1 2))) t)
(test (let ((x 'a)) (and x (setq x 'b))) b)
(test (let ((x nil)) (and x (setq x 'b))) nil)

(test (let ((time 10))
   (if (and (< time 24) (> time 12))
       (- time 12) time)) 10 eql)

(test (let ((time 18))
   (if (and (< time 24) (> time 12))
       (- time 12) time)) 6 eql)

;;;
($argc and 0 0 1)
;;;
(test (and) t)
(test (and (cons 1 2)) (1 . 2) equal)
(test (and (cons 1 2) nil (cons 3 4)) nil)
(test (and (cons 1 2) (cons 3 4) nil) nil)
(test (and (cons 1 2) (cons 3 4) (cons 5 6)) (5 . 6) equal)
;;;
;;; special form (OR form*) --> <object>
;;;
($ap 2 "or" P.30)
(test (or (= 2 2) (> 2 1)) t)
(test (or (= 2 2) (< 2 1)) t)
(test (let ((x 'a)) (or x (setq x 'b))) a)
(test (let ((x nil)) (or x (setq x 'b))) b)
;;;
($argc or 0 0 1)
;;;
(test (or) nil)
(test (or (cons 1 2)) (1 . 2) equal)
(test (or nil (cons 1 2) (cons 3 4)) (1 . 2) equal)
(test (or (cons 1 2) (cons 3 4) (cons 5 6)) (1 . 2) equal)
(test (or nil nil nil nil nil) nil)
