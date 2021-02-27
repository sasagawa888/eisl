(import "test")
;;;
;;;  Vectors
;;;
;;;
;;; (BASIC-VECTOR-P obj) --> boolean
;;;
;;;
;;; (GENERAL-VECTOR-P obj) --> boolean
;;;
(test (mapcar (lambda (x) (list (basic-vector-p x) (general-vector-p x)))
   '((a b c) "abc" #(a b c) #1a(a b c) #2a((a) (b) (c))))
 ((nil nil) (t nil) (t t) (t t) (nil nil))
 equal)
;;;
;;; (CREATE-VECTOR i [initial-element]) --> <general-vector>
;;;
(test (create-vector 3 17) #(17 17 17) equal)
(test (create-vector 2 #\a) #(#\a #\a) equal)
;;;
;;;
(test (create-vector 0) #() equal)
(test (create-vector 0 'a) #() equal)
;($error (create-vector -1) <domain-error>)
;($error (create-vector -1234567890) <domain-error>)
;($error (create-vector 1234567890) <storage-exhausted>)
(test (length (create-vector 1000 'a)) 1000 eql)

;;;
;;; (VECTOR obj*) --> <general-vector>
;;;
(test (vector 'a 'b 'c) #(a b c) equal)
(test (vector) #() equal)
;;;
(test (vector 1 2 3 4 5 6 7 8 9 10) #(1 2 3 4 5 6 7 8 9 10) equal)
