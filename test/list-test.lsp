(defmacro test(form1 form2 :rest pred)
  (if (null pred)
      `(if (equal ,form1 ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad~%" ',form1))
      `(if (,@pred ,form1 ',form2)
           (format (standard-output) "" ',form1)
           (format (standard-output) "~S is bad~%" ',form1))))


;;; (CONSP obj) --> boolean
;;;
(test (consp '(a . b)) t)
(test (consp '(a b c)) t)
(test (consp '()) nil)
(test (consp #(a b)) nil)

(test (consp (create-list 1000 'a)) t)

;;;
;;; (CONS obj1 obj2) --> <cons>
;;;

(test (cons 'a '()) (a) equal)
(test (cons '(a) '(b c d)) ((a) b c d) equal)
(test (cons "a" '(b c)) ("a" b c) equal)
(test (cons 'a 3) (a . 3) equal)
(test (cons '(a b) 'c) ((a b) . c) equal)
;;;


;;;
(test (length (cons (create-list 1000 'a) (create-list 1000 'b))) 1001 eql)

;;;
;;; (CAR cons) --> <object>
;;;

(test (car '(a b c)) a)
(test (car '((a) b c d)) (a) equal)
(test (car '(1 . 2)) 1 eql)
;;;

;;;
(test (car (create-list 1000 'a)) a)

;;;
;;; (CDR cons) --> <object>
;;;
(test (cdr '((a) b c d)) (b c d) equal)
(test (cdr '(1 . 2)) 2 eql)
;;;

;;;
(test (length (cdr (create-list 1000 'a))) 999 eql)

;;;
;;; (SET-CAR obj cons) --> <object>
;;;
(test (let ((x (list 'apple 'orange)))
   (list x (car x) (setf (car x) 'banana) x (car x)))
 ((banana orange) apple banana (banana orange) banana)
 equal)
(test (let ((x (list 'apple 'orange)))
   (list x (car x) (set-car 'banana x) x (car x)))
 ((banana orange) apple banana (banana orange) banana)
 equal)
;;;
;;;
(test (let ((x (create-list 1000 'a))) (list (setf (car x) 'b) (car x)))
 (b b) equal)
(test (let ((x (create-list 1000 'a))) (list (set-car 'b x) (car x)))
 (b b) equal)

;;;
;;; (SET-CDR obj cons) --> <object>
;;;
(test (let ((x (list 'apple 'orange)))
   (list x (cdr x) (setf (cdr x) 'banana) x (cdr x)))
 ((apple . banana) (orange) banana (apple . banana) banana)
 equal)
(test (let ((x (list 'apple 'orange)))
   (list x (cdr x) (set-cdr 'banana x) x (cdr x)))
 ((apple . banana) (orange) banana (apple . banana) banana)
 equal)
;;;

(test (let ((x (create-list 1000 'a))) (list (setf (cdr x) 'b) x))
 (b (a . b)) equal)
(test (let ((x (create-list 1000 'a))) (list (set-cdr 'b x) x))
 (b (a . b)) equal)

;;;
;;; (NULL obj) --> boolean
;;;

(test (null '(a b c)) nil)
(test (null '()) t)
(test (null (list)) t)
;;;

;;;
(test (null (create-list 1000 'a)) nil)

;;;
;;; LISTP obj) --> boolean
;;;
(test (listp '(a b c)) t)
(test (listp '()) t)
(test (listp '(a . b)) t)
;;caution
;(test (let ((x (list 'a))) (setf (cdr x) x) (listp x)) t)
(test (listp "abc") nil)
(test (listp #(1 2)) nil)
(test (listp 'jerome) nil)
;;;
(test (listp (create-list 1000 'a)) t)
;;;
;;; (CREATE-LIST i [initial-element]) --> <list>
;;;

(test (create-list 3 17) (17 17 17) equal)
(test (create-list 2 #\a) (#\a #\a) equal)
;;;
;;;
(test (create-list 0) ())
(test (create-list 0 1) ())
(test (length (create-list 1000)) 1000 eql)
(test (length (create-list 1000 'a)) 1000 eql)
;;;
;;; (LIST obj*) --> <list>
;;;
(test (list 'a (+ 3 4) 'c) (a 7 c) equal)
(test (list) nil)
;;;
;;;
(test (list 1 2 3 4 5 6 7 8 9 10) (1 2 3 4 5 6 7 8 9 10) equal)
;;;
;;; (REVERSE list) --> <list>
;;;
(test (reverse '(a b c d e)) (e d c b a) equal)
(test (reverse '(a)) (a) equal)
(test (reverse '()) ())
;;;
;;;
(test (length (reverse (create-list 1000 'a))) 1000 eql)

;;;
;;; (NREVERSE list) --> <list>
;;;
;;((let* ((x (list 'a 'b)) (y (nreverse x))) (equal x y)) nil)  ; IDEF
;;;
;;;
(test (length (nreverse (create-list 1000 'a))) 1000 eql)
;;;
;;; (APPEND list*) --> <list>
;;;
(test (append '(a b c) '(d e f)) (a b c d e f) equal)
;;;
;;; 0 arument
(test (append) ())
;;; 1 argument
(test (append ()) ())
(test (append '(a b c)) (a b c) equal)
(test (length (append (create-list 1000 'a))) 1000 eql)
;;; 2 arguments
(test (append () ()) ())
(test (append () '(a b c)) (a b c) equal)
(test (append '(a b c) ()) (a b c) equal)
(test (length (append (create-list 1000 'a) (create-list 1000 'b))) 2000 eql)
;;; 3 arguments
(test (append () () ()) ())
(test (append () () '(a b c)) (a b c) equal)
(test (append () '(a b c) ()) (a b c) equal)
(test (append '(a b c) () ()) (a b c) equal)
(test (append '(a b c) '(d e f) ()) (a b c d e f) equal)
(test (append '(a b c) () '(d e f)) (a b c d e f) equal)
(test (append () '(a b c) '(d e f)) (a b c d e f) equal)
(test (length
  (append (create-list 1000 'a) (create-list 1000 'b) (create-list 1000 'c)))
 3000 eql)
;;; last list
(test (let* ((x (list 'a 'b 'c))
    (y (append x)))
   (eq y x))
 t)
(test (let* ((x (list 'a 'b 'c))
    (y (append '(1 2) x)))
   (eq (cdr (cdr y)) x))
 t)
(test (let* ((x (list 'a 'b 'c))
    (y (append '(1 2) '(3 4) x)))
   (eq (cdr (cdr (cdr (cdr y)))) x))
 t)
(test (let* ((x (list 'a 'b 'c))
    (y (append '(1 2) x '(3 4))))
   (eq (cdr (cdr y)) x))
  nil)

;;;
;;; (MEMBER obj list) --> <list>
;;;
(test (member 'c '(a b c d e f)) (c d e f) equal)
(test (member 'g '(a b c d e f)) nil)
(test (member 'c '(a b c a b c)) (c a b c) equal)
;;;
;;;
(test (member #\b '(#\a #\b #\c)) (#\b #\c) equal)
(test (member 2 '(1 2 3)) (2 3) equal)
(test (member -2 '(1 -2 3)) (-2 3) equal)
(test (member 2.0 '(1 2.0 3)) (2.0 3) equal)
(test (member -2.0 '(1 -2.0 3)) (-2.0 3) equal)
(test (member 1234567890 '(1 1234567890 3)) (1234567890 3) equal)
(test (member -1234567890 '(1 -1234567890 3)) (-1234567890 3) equal)
(test (member 'a ()) nil)
(test (length (member 'a (create-list 1000 'a))) 1000 eql)
(test (member 'b (create-list 1000 'a)) nil)

;;;
;;; (MAPCAR function list+) --> <list>
;;;
(test (mapcar #'car '((1 a) (2 b) (3 c))) (1 2 3) equal)
(test (mapcar #'abs '(3 -4 2 -5 -6)) (3 4 2 5 6) equal)
(test (mapcar #'cons '(a b c) '(1 2 3)) ((a . 1) (b . 2) (c . 3)) equal)
;;;
;;; 1 high order
(test (mapcar #'car ()) ())
(test (mapcar (lambda (x) (car 1)) ()) ())
(test (mapcar (lambda (x) (+ x 1)) '(1 2 3 4 5)) (2 3 4 5 6) equal)
;;; 2 high order

(test (mapcar #'cons () ()) ())
(test (mapcar #'cons () '(a b c)) ())
(test (mapcar #'cons '(a b c) ()) ())
(test (mapcar (lambda (x y) (+ x y)) '(1 2 3 4 5) '(6 7 8 9 10))
 (7 9 11 13 15) equal)
;;; rest high order
(test (mapcar #'list () () () () ()) ())
(test (mapcar #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o))
 ((a d g j m) (b e h k n) (c f i l o))
 equal)
(test (mapcar #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o))
 ((a d g j m))
 equal)
(test (mapcar (lambda (&rest x) x) '(1 2 3) '(4 5 6) '(7 8 9))
 ((1 4 7) (2 5 8) (3 6 9)) equal)

;;;
;;; (MAPC function list+) --> <list>
;;;
(test (let ((x 0)) (mapc (lambda (v) (setq x (+ x v))) '(3 5)) x) 8 eql)
;;;

;;; 1 high order
(test (mapc #'car ()) ())
(test (mapc (lambda (x) (car 1)) ()) ())
(test (let ((x 0)) (list (mapc (lambda (v) (setq x (+ x v))) '(3 5)) x))
 ((3 5) 8) equal)
;;; 2 high order
(test (mapc #'cons () ()) ())
(test (mapc #'cons () '(a b c)) ())
(test (mapc #'cons '(a b c) ()) (a b c) equal)
(test(let ((ret 0))
   (list (mapc (lambda (x y) (setq ret (+ ret x y))) '(1 2 3) '(4 5 6)) ret))
 ((1 2 3) 21)
 equal)
;;; rest high order
(test (mapc #'list () () () () ()) ())
(test (mapc #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o)) (a b c) equal)
(test (mapc #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o)) (a b c) equal)
(test (let ((ret ()))
   (list (mapc (lambda (&rest x) (setq ret (cons x ret))) '(1 2 3) '(4 5 6) '(7 8 9))
         ret))
 ((1 2 3) ((3 6 9) (2 5 8) (1 4 7)))
 equal)

;;;
;;; (MAPCAN function list+) --> <list>
;;;
(test (mapcan (lambda (x) (if (> x 0) (list x))) '(-3 4 0 5 -2 7)) (4 5 7) equal)

;;;

;;; 1 high order
(test (mapcan #'car ()) ())
(test (mapcan (lambda (x) (car 1)) ()) ())
(test (mapcan (lambda (x) (list (+ x 1))) '(1 2 3 4 5)) (2 3 4 5 6) equal)
;;; 2 high order
(test (mapcan #'cons () ()) ())
(test (mapcan #'cons () '(a b c)) ())
(test (mapcan #'cons '(a b c) ()) ())
(test (mapcan (lambda (x y) (list (+ x y))) '(1 2 3 4 5) '(6 7 8 9 10)) (7 9 11 13 15) equal)
;;; rest high order
(test (mapcan #'list () () () () ()) ())
(test (mapcan #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o))
 (a d g j m b e h k n c f i l o)
 equal)
(test (mapcan #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o))
 (a d g j m)
 equal)
(test (mapcan (lambda (&rest x) x) '(1 2 3) '(4 5 6) '(7 8 9)) (1 4 7 2 5 8 3 6 9) equal)


;;;
;;; (MAPLIST function list+) --> <list>
;;;
(test (maplist #'append '(1 2 3 4) '(1 2) '(1 2 3)) ((1 2 3 4 1 2 1 2 3) (2 3 4 2 2 3)) equal)
(test (maplist (lambda (x) (cons 'foo x))
 '(a b c d)) ((foo a b c d ) (foo b c d) (foo c d) (foo d))
 equal)
(test (maplist (lambda (x) (if (member (car x) (cdr x)) 0 1)) '(a b a c d b c))
 (0 0 1 0 1 1 1 )
 equal)


;;; 1 high order
(test (maplist #'car ()) ())
(test (maplist (lambda (x) (car 1)) ()) ())
(test (maplist (lambda (x) x) '(1 2 3 4 5)) ((1 2 3 4 5) (2 3 4 5) (3 4 5) (4 5) (5)) equal)
;;; 2 high order
(test (maplist #'cons () ()) ())
(test (maplist #'cons () '(a b c)) ())
(test (maplist #'cons '(a b c) ()) ())
(test (maplist (lambda (x y) (list x y)) '(1 2 3) '(4 5 6))
 (((1 2 3) (4 5 6)) ((2 3) (5 6)) ((3) (6)))
 equal)


;;; rest high order
(test (maplist #'list () () () () ()) ())
(test (maplist #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o))
 (((a b c) (d e f) (g h i) (j k l) (m n o))
  ((b c) (e f) (h i) (k l) (n o))
  ((c) (f) (i) (l) (o)))
 equal)

(test (maplist #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o))
 (((a b c) (d e f) (g) (j k l) (m n o)))
 equal)
(test (maplist (lambda (&rest x) x) '(1 2 3) '(4 5 6) '(7 8 9))
 (((1 2 3) (4 5 6) (7 8 9))
  ((2 3) (5 6) (8 9))
  ((3) (6) (9)))
 equal)

;;;
;;; (MAPL function list+) --> <list>
;;;
(test (let ((k 0))
   (mapl (lambda (x) (setq k (+ k (if (member (car x) (cdr x)) 0 1))))
         '(a b a c d b c))
   k)
 4
 eql)
;;;
;;; 1 high order
(test (mapl #'car ()) ())
(test (mapl (lambda (x) (car 1)) ()) ())
(test (let ((ret ()))
   (list (mapl (lambda (x) (setq ret (cons x ret))) '(1 2 3 4 5))
         (nreverse ret)))
 ((1 2 3 4 5) ((1 2 3 4 5) (2 3 4 5) (3 4 5) (4 5) (5))) equal)
;;; 2 high ordr
(test (mapl #'cons () ()) ())
(test (mapl #'cons () '(a b c)) ())
(test (mapl #'cons '(a b c) ()) (a b c) equal)
(test (let ((ret ()))
   (list (mapl (lambda (x y) (setq ret (cons (list x y) ret))) '(1 2 3) '(4 5 6))
         (nreverse ret)))
 ((1 2 3) (((1 2 3) (4 5 6)) ((2 3) (5 6)) ((3) (6))))
 equal)
;;; rest high order
(test (mapl #'list () () () () ()) ())
(test (let ((ret ()))
   (list (mapl (lambda (&rest x) (setq ret (cons x ret))) '(1 2 3) '(4 5 6) '(7 8 9))
         (nreverse ret)))
 ((1 2 3)
  (((1 2 3) (4 5 6) (7 8 9))
   ((2 3) (5 6) (8 9))
   ((3) (6) (9))))
 equal)

;;;
;;; (MAPCON function list+) --> <list>
;;;

(test (mapcon (lambda (x) (if (member (car x) (cdr x)) (list (car x)))) '(a b a c d b c b c))
 (a b c b c)
 equal)
(test (mapcon #'list '(1 2 3 4)) ((1 2 3 4) (2 3 4) (3 4) (4)) equal)

;;;

;;; 1 high order
(test (mapcon #'car ()) ())
(test (mapcon (lambda (x) (car 1)) ()) ())
(test (mapcon (lambda (x) (list x)) '(1 2 3 4 5)) ((1 2 3 4 5) (2 3 4 5) (3 4 5) (4 5) (5)) equal)

;;; 2 high order
(test (mapcon #'cons () ()) ())
(test (mapcon #'cons () '(a b c)) ())
(test (mapcon #'cons '(a b c) ()) ())
(test (mapcon (lambda (x y) (list (list x y))) '(1 2 3) '(4 5 6))
 (((1 2 3) (4 5 6)) ((2 3) (5 6)) ((3) (6)))
 equal)
;;; rest high order
(test (mapcon #'list () () () () ()) ())
(test (mapcon #'list '(a b c) '(d e f) '(g h i) '(j k l) '(m n o))
 ((a b c) (d e f) (g h i) (j k l) (m n o)
  (b c) (e f) (h i) (k l) (n o)
  (c) (f) (i) (l) (o))
 equal)
(test (mapcon #'list '(a b c) '(d e f) '(g) '(j k l) '(m n o))
 ((a b c) (d e f) (g) (j k l) (m n o))
 equal)
(test (mapcon (lambda (&rest x) (list x)) '(1 2 3) '(4 5 6) '(7 8 9))
 (((1 2 3) (4 5 6) (7 8 9))
  ((2 3) (5 6) (8 9))
  ((3) (6) (9)))
 equal)

;;;
;;; (ASSOC obj association-list) --> <cons>
;;;

(test (assoc 'a '((a . 1) (b . 2))) (a . 1) equal)
(test (assoc 'a '((a . 1) (a . 2))) (a . 1) equal)
(test (assoc 'c '((a . 1) (b . 2))) nil)
;;;
;;;
(test (assoc 'a ()) nil)
(test (assoc 'b '((a) (b) (c))) (b) equal)
(test (assoc 'b '((a 1) (b 2) (c 3))) (b 2) equal)
(test (assoc #\b '((#\a . 1) (#\b . 2) (#\c . 3))) (#\b . 2) equal)
(test (assoc 2 '((1 . 1) (2 . 2) (3 . 3))) (2 . 2) equal)
(test (assoc -2 '((1 . 1) (-2 . 2) (3 . 3))) (-2 . 2) equal)
(test (assoc 2.0 '((1 . 1) (2.0 . 2) (3 . 3))) (2.0 . 2) equal)
(test (assoc -2.0 '((1 . 1) (-2.0 . 2) (3 . 3))) (-2.0 . 2) equal)
(test (assoc 1234567890 '((1 . 1) (1234567890 . 2) (3 . 3))) (1234567890 . 2) equal)
(test (assoc -1234567890 '((1 . 1) (-1234567890 . 2) (3 . 3))) (-1234567890 . 2) equal)

(test (assoc 'a '((a . b) ())) (a . b) equal)
(test (assoc 'a (create-list 1000 '(a . b))) (a . b) equal)
(test (assoc 'b (create-list 1000 '(a . b))) nil)
