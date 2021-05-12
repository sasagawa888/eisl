# List and cxr

The list library and cxr library was written by M. Hiroi.

# Acknowledgement
Thanks to Mr. Hiroi.

# Usage 

```lisp
(import "list")

(import "cxr")
```

# Specification

See the following test cases:

```lisp
(test (caar '((a b) (c d) (e f))) A)
(test (cadr '((a b) (c d) (e f))) (C D))
(test (cdar '((a b) (c d) (e f))) (B))
(test (cddr '((a b) (c d) (e f))) ((E F)))
;; ommited cXXXr cXXXXr
(test (first '(a b c d e f)) A)
(test (second '(a b c d e f)) B)
(test (third '(a b c d e f)) C)
(test (fourth '(a b c d e f)) D)
(test (fifth '(a b c d e f)) E)
(test (sixth '(a b c d e f g h i j)) F)
(test (seventh '(a b c d e f g h i j)) G)
(test (eigthth '(a b c d e f g h i j)) h)
(test (ninth '(a b c d e f g h i j)) i)
(test (tenth '(a b c d e f g h i j)) j)
(test (last-pair '(a b c d e f)) (F))
(test (last '(a b c d e f)) F)
(test (take '(a b c d e f) 3) (A B C))
(test (drop '(a b c d e f) 3) (D E F))
(test (take '(a b c d e f) 6) (A B C D E F))
(test (drop '(a b c d e f) 6) NIL)
(test (revappend '(a b c) '(d e f)) (C B A D E F))
(test (revappend nil '(d e f)) (D E F))
(test (revappend '(a b c) nil) (C B A))
(test (iota 1 10) (1 2 3 4 5 6 7 8 9 10))
(test (iota 1 1) (1))
(test (iota 1 0) NIL)
(test (remove-duplicates '(a b c a b c d a b c d e)) (A B C D E))
(test (remove-duplicates '(a b c d e f)) (A B C D E F))
(defun evenp (x)
    (= (mod x 2) 0) )

(defun xcons (a b)
    (cons b a) )

(test (member-if (lambda (x) (= (mod x 2) 0)) '(1 2 3 4 5 6 7 8)) (2 3 4 5 6 7 8))
(test (member-if (lambda (x) (= (mod x 2) 0)) '(1 3 5 7 9)) NIL)
(test (member-if-not (lambda (x) (= (mod x 2) 0)) '(1 2 3 4 5 6 7 8)) (1 2 3 4 5 6 7 8))
(test (member-if-not (lambda (x) (= (mod x 2) 1)) '(1 3 5 7 9)) NIL)
(test (fold-left #'+ 0 (iota 1 10)) 55)
(test (fold-right #'+ 0 (iota 1 10)) 55)
(test (fold-left (lambda (a x y) (cons (cons x y) a)) nil '(1 2 3 4) '(5 6 7 8)) ((4 . 8) (3 . 7) (2 . 6) (1 . 5)))
(test (fold-right (lambda (a x y) (cons (cons x y) a)) nil '(1 2 3 4) '(5 6 7 8)) ((1 . 5) (2 . 6) (3 . 7) (4 . 8)))
(test (partition (lambda (x) (= (mod x 2) 0)) (iota 1 10)) ((2 4 6 8 10) (1 3 5 7 9)))
(test (partition (lambda (x) (= (mod x 2) 1)) (iota 1 10)) ((1 3 5 7 9) (2 4 6 8 10)))
(test (partition (lambda (x) (<= x 5)) (iota 1 10)) ((1 2 3 4 5) (6 7 8 9 10)))
(test (partition (lambda (x) (> x 5)) (iota 1 10)) ((6 7 8 9 10) (1 2 3 4 5)))
(test (any #'< '(1 3 5) '(2 1 0)) T)
(test (any #'< '(1 3 5) '(0 1 0)) NIL)
(test (any #'evenp '(1 3 4 5)) T)
(test (any #'evenp '(1 3 5)) NIL)
(test (any (lambda (x) (<= x 5)) '(5 6 7 8 9)) T)
(test (any (lambda (x) (<= x 5)) '(6 7 8 9 10)) NIL)
(test (any #'<= '(5 6 7 8 9) '(5 4 3 2 1)) T)
(test (any #'<= '(5 6 7 8 9) '(4 3 2 1 0)) NIL)
(test (all (lambda (x) (<= 5 x)) '(5 6 7 8 9)) T)
(test (all (lambda (x) (<= 5 x)) '(5 6 7 8 0)) NIL)
(test (all #'<= '(1 2 3 4 5) '(6 7 8 9 10)) T)
(test (all #'<= '(1 2 3 4 5) '(6 7 8 9 0)) NIL)
(test (union '(1 2 3 4) '(3 4 5 6)) (1 2 3 4 5 6))
(test (intersection '(1 2 3 4) '(3 4 5 6)) (3 4))
(test (difference '(1 2 3 4) '(3 4 5 6)) (1 2))
(test (subsetp '(1 2) '(1 2 3 4)) T)
(test (subsetp '(1 2 5) '(1 2 3 4)) NIL)
```
