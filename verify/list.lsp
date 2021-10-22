(import "test")
;;;
;;;  chapter13  List class
;;;
($ap 1 "List class")

;;;
;;; function (CONSP obj) --> boolean
;;;
($ap 2 "consp" P.83)
($test (consp '(a . b)) t)
($test (consp '(a b c)) t)
($test (consp '()) nil)
($test (consp #(a b)) nil)
;;;
($argc consp 1 0 0)
($predicate consp $cons)
;;;
($test (consp (create-list 1000 'a)) t)

;;;
;;; function (CONS obj1 obj2) --> <cons>
;;;
($ap 2 "cons" P.84)
($test (cons 'a '()) (a) equal)
($test (cons '(a) '(b c d)) ((a) b c d) equal)
($test (cons "a" '(b c)) ("a" b c) equal)
($test (cons 'a 3) (a . 3) equal)
($test (cons '(a b) 'c) ((a b) . c) equal)
;;;
($argc cons 2 0 0)
;;;
($test (length (cons (create-list 1000 'a) (create-list 1000 'b))) 1001 eql)

;;;
;;; function (CAR cons) --> <object>
;;;
($ap 2 "car" P.84)
($error (car '()) <domain-error>)
($test (car '(a b c)) a)
($test (car '((a) b c d)) (a) equal)
($test (car '(1 . 2)) 1 eql)
;;;
($argc car 1 0 0)
($type car ($cons) :target)
;;;
($test (car (create-list 1000 'a)) a)

;;;
;;; function (CDR cons) --> <object>
;;;
($ap 2 "cdr" P.84)
($error (cdr '()) <domain-error>)
($test (cdr '((a) b c d)) (b c d) equal)
($test (cdr '(1 . 2)) 2 eql)
;;;
($argc cdr 1 0 0)
($type cdr ($cons) :target)
;;;
($test (length (cdr (create-list 1000 'a))) 999 eql)

;;;
;;; function (SET-CAR obj cons) --> <object>
;;;
($ap 2 "set-car" P.85)
($test (let ((x (list 'apple 'orange)))
   (list x (car x) (setf (car x) 'banana) x (car x)))
 ((banana orange) apple banana (banana orange) banana)
 equal)
($test (let ((x (list 'apple 'orange)))
   (list x (car x) (set-car 'banana x) x (car x)))
 ((banana orange) apple banana (banana orange) banana)
 equal)
;;;
($argc set-car 2 0 0)
($type set-car ($cons) 1 :target)
;;;
($test (let ((x (create-list 1000 'a))) (list (setf (car x) 'b) (car x))) 
 (b b) equal)
($test (let ((x (create-list 1000 'a))) (list (set-car 'b x) (car x))) 
 (b b) equal)

;;;
;;; function (SET-CDR obj cons) --> <object>
;;;
($ap 2 "set-cdr" P.85)
($test (let ((x (list 'apple 'orange)))
   (list x (cdr x) (setf (cdr x) 'banana) x (cdr x)))
 ((apple . banana) (orange) banana (apple . banana) banana)
 equal)
($test (let ((x (list 'apple 'orange)))
   (list x (cdr x) (set-cdr 'banana x) x (cdr x)))
 ((apple . banana) (orange) banana (apple . banana) banana)
 equal)
;;;
($argc set-cdr 2 0 0)
($type set-cdr ($cons) 1 :target)
;;;
($test (let ((x (create-list 1000 'a))) (list (setf (cdr x) 'b) x)) 
 (b (a . b)) equal)
($test (let ((x (create-list 1000 'a))) (list (set-cdr 'b x) x)) 
 (b (a . b)) equal)

;;;
;;; function (NULL obj) --> boolean
;;;
($ap 2 "null" P.85)
($test (null '(a b c)) nil)
($test (null '()) t)
($test (null (list)) t)
;;;
($argc null 1 0 0)
($predicate null $null)
;;;
($test (null (create-list 1000 'a)) nil)

;;;
;;; function (LISTP obj) --> boolean
;;;
($ap 2 "listp" P.86)
($test (listp '(a b c)) t)
($test (listp '()) t)
($test (listp '(a . b)) t)
($test (let ((x (list 'a))) (setf (cdr x) x) (listp x)) t)
($test (listp "abc") nil)
($test (listp #(1 2)) nil)
($test (listp 'jerome) nil)
;;;
($argc listp 1 0 0)
($predicate listp $cons $null)
;;;
($test (listp (create-list 1000 'a)) t)

;;;
;;; function (CREATE-LIST i [initial-element]) --> <list>
;;;
($ap 2 "create-list" P.86)
($test (create-list 3 17) (17 17 17) equal)
($test (create-list 2 #\a) (#\a #\a) equal)
;;;
($argc create-list 1 1 0)
($type create-list ($integer) :target)
;;;
($test (create-list 0) ())
($test (create-list 0 1) ())
($error (create-list -1) <domain-error>)
($error (create-list 1234567890) <storage-exhausted>)
($error (create-list 1000000000000000) <storage-exhausted>)
($test (length (create-list 1000)) 1000 eql)
($test (length (create-list 1000 'a)) 1000 eql)

;;;
;;; function (LIST obj*) --> <list>
;;;
($ap 2 "list" P.87)
($test (list 'a (+ 3 4) 'c) (a 7 c) equal)
($test (list) nil)
;;;
($argc list 0 0 1)
;;;
($test (list 1 2 3 4 5 6 7 8 9 10) (1 2 3 4 5 6 7 8 9 10) equal)

;;;
;;; function (REVERSE list) --> <list>
;;;
($ap 2 "reverse" P.87)
($test (reverse '(a b c d e)) (e d c b a) equal)
($test (reverse '(a)) (a) equal)
($test (reverse '()) ())
;;;
($argc reverse 1 0 0)
($type reverse ($cons $null) :target)
;;;
($test (length (reverse (create-list 1000 'a))) 1000 eql)

;;;
;;; function (NREVERSE list) --> <list>
;;;
($ap 2 "nreverse" P.87)
;;($test (let* ((x (list 'a 'b)) (y (nreverse x))) (equal x y)) nil)	; IDEF
;;;
($argc nreverse 1 0 0)
($type nreverse ($cons $null) :target)
;;;
($test (length (nreverse (create-list 1000 'a))) 1000 eql)

;;;
;;; function (APPEND list*) --> <list>
;;;
($ap 2 "append" P.87)
($test (append '(a b c) '(d e f)) (a b c d e f) equal)
;;;
($argc append 0 0 1)
($type append ($cons $null) :target)
($type append ($cons $null) (quote (a b c)) :target)
($type append ($cons $null) (quote (a b c)) (quote (d e f)) :target)
;;; 0 argument
($test (append) ())
;;; 1 argument
($test (append ()) ())
($test (append '(a b c)) (a b c) equal)
($test (length (append (create-list 1000 'a))) 1000 eql)
;;; 2 argument
($test (append () ()) ())
($test (append () '(a b c)) (a b c) equal)
($test (append '(a b c) ()) (a b c) equal)
($test (length (append (create-list 1000 'a) (create-list 1000 'b))) 2000 eql)
;;; 3 argument
($test (append () () ()) ())
($test (append () () '(a b c)) (a b c) equal)
($test (append () '(a b c) ()) (a b c) equal)
($test (append '(a b c) () ()) (a b c) equal)
($test (append '(a b c) '(d e f) ()) (a b c d e f) equal)
($test (append '(a b c) () '(d e f)) (a b c d e f) equal)
($test (append () '(a b c) '(d e f)) (a b c d e f) equal)
($test (length 
  (append (create-list 1000 'a) (create-list 1000 'b) (create-list 1000 'c)))
 3000 eql)
;;; Share only the last list 
($test (let* ((x (list 'a 'b 'c))
	(y (append x)))
   (eq y x))
 t)
($test (let* ((x (list 'a 'b 'c))
	(y (append '(1 2) x)))
   (eq (cdr (cdr y)) x))
 t)
($test (let* ((x (list 'a 'b 'c))
	(y (append '(1 2) '(3 4) x)))
   (eq (cdr (cdr (cdr (cdr y)))) x))
 t)
($test (let* ((x (list 'a 'b 'c))
	(y (append '(1 2) x '(3 4))))
   (eq (cdr (cdr y)) x))
  nil)

;;;
;;; function (MEMBER obj list) --> <list>
;;;
($ap 2 "member" P.88)
($test (member 'c '(a b c d e f)) (c d e f) equal)
($test (member 'g '(a b c d e f)) nil)
($test (member 'c '(a b c a b c)) (c a b c) equal)
;;;
($argc member 2 0 0)
($type member ($cons $null) (quote a) :target)
;;;
($test (member #\b '(#\a #\b #\c)) (#\b #\c) equal)
($test (member 2 '(1 2 3)) (2 3) equal)
($test (member -2 '(1 -2 3)) (-2 3) equal)
($test (member 2.0 '(1 2.0 3)) (2.0 3) equal)
($test (member -2.0 '(1 -2.0 3)) (-2.0 3) equal)
($test (member 1234567890 '(1 1234567890 3)) (1234567890 3) equal)
($test (member -1234567890 '(1 -1234567890 3)) (-1234567890 3) equal)
($test (member 'a ()) nil)
($test (length (member 'a (create-list 1000 'a))) 1000 eql)
($test (member 'b (create-list 1000 'a)) nil)

;;;
;;; function (MAPCAR function list+) --> <list>
;;;
($ap 2 "mapcar" P.88)
($test (mapcar #'car '((1 a) (2 b) (3 c))) (1 2 3) equal)
($test (mapcar #'abs '(3 -4 2 -5 -6)) (3 4 2 5 6) equal)
($test (mapcar #'cons '(a b c) '(1 2 3)) ((a . 1) (b . 2) (c . 3)) equal)
;;;
($argc mapcar 2 0 1)
($type mapcar ($function $generic) :target nil)
($type mapcar ($cons $null) (function list) :target)
($type mapcar ($cons $null) (function list) (quote (a b)) :target)
;;; 1 argumentfunction
($test (mapcar #'car ()) ())
($test (mapcar (lambda (x) (car 1)) ()) ())
($test (mapcar (lambda (x) (+ x 1)) '(1 2 3 4 5)) (2 3 4 5 6) equal)
;;; 2 argumentfunction
($test (mapcar #'cons () ()) ())
($test (mapcar #'cons () '(a b c)) ())
($test (mapcar #'cons '(a b c) ()) ())
($test (mapcar (lambda (x y) (+ x y)) '(1 2 3 4 5) '(6 7 8 9 10)) 
 (7 9 11 13 15) equal)
;;; rest argumentfunction
($test (mapcar #'list () () () () ()) ())
($test (mapcar #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o))
 ((a d g j m) (b e h k n) (c f i l o))
 equal)
($test (mapcar #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o))
 ((a d g j m))
 equal)
($test (mapcar (lambda (&rest x) x) '(1 2 3) '(4 5 6) '(7 8 9)) 
 ((1 4 7) (2 5 8) (3 6 9)) equal)

;;;
;;; function (MAPC function list+) --> <list>
;;;
($ap 2 "mapc" P.88)
($test (let ((x 0)) (mapc (lambda (v) (setq x (+ x v))) '(3 5)) x) 8 eql)
;;;
($argc mapc 2 0 1)
($type mapc ($function $generic) :target nil)
($type mapc ($cons $null) (function list) :target)
($type mapc ($cons $null) (function list) (quote (a b)) :target)
;;; 1 argumentfunction
($test (mapc #'car ()) ())
($test (mapc (lambda (x) (car 1)) ()) ())
($test (let ((x 0)) (list (mapc (lambda (v) (setq x (+ x v))) '(3 5)) x)) 
 ((3 5) 8) equal)
;;; 2 argumentfunction
($test (mapc #'cons () ()) ())
($test (mapc #'cons () '(a b c)) ())
($test (mapc #'cons '(a b c) ()) (a b c) equal)
($test (let ((ret 0)) 
   (list (mapc (lambda (x y) (setq ret (+ ret x y))) '(1 2 3) '(4 5 6)) ret))
 ((1 2 3) 21)
 equal)
;;; rest argumentfunction
($test (mapc #'list () () () () ()) ())
($test (mapc #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o)) (a b c) equal)
($test (mapc #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o)) (a b c) equal)
($test (let ((ret ()))
   (list (mapc (lambda (&rest x) (setq ret (cons x ret))) '(1 2 3) '(4 5 6) '(7 8 9))
         ret))
 ((1 2 3) ((3 6 9) (2 5 8) (1 4 7)))
 equal)

;;;
;;; function (MAPCAN function list+) --> <list>
;;;
($ap 2 "mapcan" P.88)
($test (mapcan (lambda (x) (if (> x 0) (list x))) '(-3 4 0 5 -2 7)) (4 5 7) equal)
;;;
($argc mapcan 2 0 1)
($type mapcan ($function $generic) :target nil)
($type mapcan ($cons $null) (function list) :target)
($type mapcan ($cons $null) (function list) (quote (a b)) :target)
;;; 1 argumentfunction
($test (mapcan #'car ()) ())
($test (mapcan (lambda (x) (car 1)) ()) ())
($test (mapcan (lambda (x) (list (+ x 1))) '(1 2 3 4 5)) (2 3 4 5 6) equal)
;;; 2 argumentfunction
($test (mapcan #'cons () ()) ())
($test (mapcan #'cons () '(a b c)) ())
($test (mapcan #'cons '(a b c) ()) ())
($test (mapcan (lambda (x y) (list (+ x y))) '(1 2 3 4 5) '(6 7 8 9 10)) (7 9 11 13 15) equal)
;;; rest argumentfunction
($test (mapcan #'list () () () () ()) ())
($test (mapcan #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o))
 (a d g j m b e h k n c f i l o)
 equal)
($test (mapcan #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o))
 (a d g j m)
 equal)
($test (mapcan (lambda (&rest x) x) '(1 2 3) '(4 5 6) '(7 8 9)) (1 4 7 2 5 8 3 6 9) equal)

;;;
;;; function (MAPLIST function list+) --> <list>
;;;
($ap 2 "maplist" P.88)
($test (maplist #'append '(1 2 3 4) '(1 2) '(1 2 3)) ((1 2 3 4 1 2 1 2 3) (2 3 4 2 2 3)) equal)
($test (maplist (lambda (x) (cons 'foo x))
 '(a b c d)) ((foo a b c d ) (foo b c d) (foo c d) (foo d))
 equal)
($test (maplist (lambda (x) (if (member (car x) (cdr x)) 0 1)) '(a b a c d b c))
 (0 0 1 0 1 1 1 )
 equal)
;;;
($argc maplist 2 0 1)
($type maplist ($function $generic) :target nil)
($type maplist ($cons $null) (function list) :target)
($type maplist ($cons $null) (function list) (quote (a b)) :target)
;;; 1 argumentfunction
($test (maplist #'car ()) ())
($test (maplist (lambda (x) (car 1)) ()) ())
($test (maplist (lambda (x) x) '(1 2 3 4 5)) ((1 2 3 4 5) (2 3 4 5) (3 4 5) (4 5) (5)) equal)
;;; 2 argumentfunction
($test (maplist #'cons () ()) ())
($test (maplist #'cons () '(a b c)) ())
($test (maplist #'cons '(a b c) ()) ())
($test (maplist (lambda (x y) (list x y)) '(1 2 3) '(4 5 6))
 (((1 2 3) (4 5 6)) ((2 3) (5 6)) ((3) (6)))
 equal)
;;; rest argumentfunction
($test (maplist #'list () () () () ()) ())
($test (maplist #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o))
 (((a b c) (d e f) (g h i) (j k l) (m n o))
  ((b c) (e f) (h i) (k l) (n o))
  ((c) (f) (i) (l) (o)))
 equal)
($test (maplist #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o))
 (((a b c) (d e f) (g) (j k l) (m n o)))
 equal)
($test (maplist (lambda (&rest x) x) '(1 2 3) '(4 5 6) '(7 8 9))
 (((1 2 3) (4 5 6) (7 8 9))
  ((2 3) (5 6) (8 9))
  ((3) (6) (9)))
 equal)

;;;
;;; function (MAPL function list+) --> <list>
;;;
($ap 2 "mapl" P.88)
($test (let ((k 0))
   (mapl (lambda (x) (setq k (+ k (if (member (car x) (cdr x)) 0 1))))
         '(a b a c d b c))
   k)
 4
 eql)
;;;
($argc mapl 2 0 1)
($type mapl ($function $generic) :target nil)
($type mapl ($cons $null) (function list) :target)
($type mapl ($cons $null) (function list) (quote (a b)) :target)
;;; 1 argumentfunction
($test (mapl #'car ()) ())
($test (mapl (lambda (x) (car 1)) ()) ())
($test (let ((ret ()))
   (list (mapl (lambda (x) (setq ret (cons x ret))) '(1 2 3 4 5))
         (nreverse ret)))
 ((1 2 3 4 5) ((1 2 3 4 5) (2 3 4 5) (3 4 5) (4 5) (5))) equal)
;;; 2 argumentfunction
($test (mapl #'cons () ()) ())
($test (mapl #'cons () '(a b c)) ())
($test (mapl #'cons '(a b c) ()) (a b c) equal)
($test (let ((ret ()))
   (list (mapl (lambda (x y) (setq ret (cons (list x y) ret))) '(1 2 3) '(4 5 6))
         (nreverse ret)))
 ((1 2 3) (((1 2 3) (4 5 6)) ((2 3) (5 6)) ((3) (6))))
 equal)
;;; rest argumentfunction
($test (mapl #'list () () () () ()) ())
($test (let ((ret ()))
   (list (mapl (lambda (&rest x) (setq ret (cons x ret))) '(1 2 3) '(4 5 6) '(7 8 9))
         (nreverse ret)))
 ((1 2 3)
  (((1 2 3) (4 5 6) (7 8 9))
   ((2 3) (5 6) (8 9))
   ((3) (6) (9))))
 equal)

;;;
;;; function (MAPCON function list+) --> <list>
;;;
($argc mapcon 2 0 1)
($test (mapcon (lambda (x) (if (member (car x) (cdr x)) (list (car x)))) '(a b a c d b c b c))
 (a b c b c)
 equal)
($test (mapcon #'list '(1 2 3 4)) ((1 2 3 4) (2 3 4) (3 4) (4)) equal)
;;;
($argc mapcon 2 0 1)
($type mapcon ($function $generic) :target nil)
($type mapcon ($cons $null) (function list) :target)
($type mapcon ($cons $null) (function list) (quote (a b)) :target)
;;; 1 argumentfunction
($test (mapcon #'car ()) ())
($test (mapcon (lambda (x) (car 1)) ()) ())
($test (mapcon (lambda (x) (list x)) '(1 2 3 4 5)) ((1 2 3 4 5) (2 3 4 5) (3 4 5) (4 5) (5)) equal)
;;; 2 argumentfunction
($test (mapcon #'cons () ()) ())
($test (mapcon #'cons () '(a b c)) ())
($test (mapcon #'cons '(a b c) ()) ())
($test (mapcon (lambda (x y) (list (list x y))) '(1 2 3) '(4 5 6))
 (((1 2 3) (4 5 6)) ((2 3) (5 6)) ((3) (6)))
 equal)
;;; rest argumentfunction
($test (mapcon #'list () () () () ()) ())
($test (mapcon #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o))
 ((a b c) (d e f) (g h i) (j k l) (m n o)
  (b c) (e f) (h i) (k l) (n o)
  (c) (f) (i) (l) (o))
 equal)
($test (mapcon #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o))
 ((a b c) (d e f) (g) (j k l) (m n o))
 equal)
($test (mapcon (lambda (&rest x) (list x)) '(1 2 3) '(4 5 6) '(7 8 9))
 (((1 2 3) (4 5 6) (7 8 9))
  ((2 3) (5 6) (8 9))
  ((3) (6) (9)))
 equal)

;;;
;;; function (ASSOC obj association-list) --> <cons>
;;;
($ap 2 "assoc" P.90)
($test (assoc 'a '((a . 1) (b . 2))) (a . 1) equal)
($test (assoc 'a '((a . 1) (a . 2))) (a . 1) equal)
($test (assoc 'c '((a . 1) (b . 2))) nil)
;;;
($argc assoc 2 0 0)
;;;
($test (assoc 'a ()) nil)
($test (assoc 'b '((a) (b) (c))) (b) equal)
($test (assoc 'b '((a 1) (b 2) (c 3))) (b 2) equal)
($test (assoc #\b '((#\a . 1) (#\b . 2) (#\c . 3))) (#\b . 2) equal)
($test (assoc 2 '((1 . 1) (2 . 2) (3 . 3))) (2 . 2) equal)
($test (assoc -2 '((1 . 1) (-2 . 2) (3 . 3))) (-2 . 2) equal)
($test (assoc 2.0 '((1 . 1) (2.0 . 2) (3 . 3))) (2.0 . 2) equal)
($test (assoc -2.0 '((1 . 1) (-2.0 . 2) (3 . 3))) (-2.0 . 2) equal)
($test (assoc 1234567890 '((1 . 1) (1234567890 . 2) (3 . 3))) (1234567890 . 2) equal)
($test (assoc -1234567890 '((1 . 1) (-1234567890 . 2) (3 . 3))) (-1234567890 . 2) equal)
($error (assoc 'a '(a)) <error>)
($error (assoc 'a '(a b c)) <error>)
($test (assoc 'a '((a . b) ())) (a . b) equal)
($test (assoc 'a (create-list 1000 '(a . b))) (a . b) equal)
($test (assoc 'b (create-list 1000 '(a . b))) nil)
