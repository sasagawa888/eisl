(import "test")
;;;
;;;  chapter15  Vectors
;;;

($ap 1 "Vectors")

;;;
;;; function (BASIC-VECTOR-P obj) --> boolean
;;;
($ap 2 "basic-vector-p" P.94)
;;;
($argc basic-vector-p 1 0 0)
($predicate basic-vector-p $string $vector)

;;;
;;; function (GENERAL-VECTOR-P obj) --> boolean
;;;
($ap 2 "general-vector-p" P.94)
(test (mapcar (lambda (x) (list (basic-vector-p x) (general-vector-p x)))
   '((a b c) "abc" #(a b c) #1a(a b c) #2a((a) (b) (c))))
 ((nil nil) (t nil) (t t) (t t) (nil nil))
 equal)
;;;
($argc general-vector-p 1 0 0)
($predicate general-vector-p $vector)

;;;
;;; function (CREATE-VECTOR i [initial-element]) --> <general-vector>
;;;
($ap 2 "create-vector" P.94)
(test (create-vector 3 17) #(17 17 17) equal)
(test (create-vector 2 #\a) #(#\a #\a) equal)
;;;
($argc create-vector 1 1 0)
($type create-vector ($integer) :target)
;;;
(test (create-vector 0) #() equal)
(test (create-vector 0 'a) #() equal)
($error (create-vector -1) <domain-error>)
($error (create-vector -1234567890) <domain-error>)
($error (create-vector 1234567890) <storage-exhausted>)
(test (length (create-vector 1000 'a)) 1000 eql)

;;;
;;; function (VECTOR obj*) --> <general-vector>
;;;
($ap 2 "vector" P.95)
(test (vector 'a 'b 'c) #(a b c) equal)
(test (vector) #() equal)
;;;
($argc vector 0 0 1)
(test (vector 1 2 3 4 5 6 7 8 9 10) #(1 2 3 4 5 6 7 8 9 10) equal)
