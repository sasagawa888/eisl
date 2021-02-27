(import "test")

(defglobal array0 (create-array () 19))
(defglobal array2 #2a((0 1)))
(defglobal array3 #3a(((0 1 2) (3 4 5))))
(test (mapcar (lambda (x) (list (basic-array-p x) (basic-array*-p x) (general-array*-p x)))
         '((a b c) "abc" #(a b c) #1a(a b c) #2a((a) (b) (c))))
 ((nil nil nil ) (t nil nil ) (t nil nil) (t nil nil) (t t t))
 equal)

(test (create-array '(2 3) 0.0) #2a((0.0 0.0 0.0) (0.0 0.0 0.0)) equal)
(test (create-array '(2) 0.0) #(0.0 0.0) equal)

(test (basic-array*-p (create-array '() 'z)) t)
(test (create-array '(0) 'z) #1a() equal)
(test (create-array '(1) 'z) #1a(z) equal)
(test (create-array '(5) 'z) #1a(z z z z z) equal)
(test (basic-array*-p (create-array '(0 0) 'z)) t)
(test (basic-array*-p (create-array '(0 1) 'z)) t)
(test (create-array '(1 0) 'z) #2a(()) equal)
(test (create-array '(1 1) 'z) #2a((z)) equal)
(test (create-array '(1 5) 'z) #2a((z z z z z)) equal)
(test (create-array '(5 0) 'z) #2a(() () () () ()) equal)
(test (create-array '(5 1) 'z) #2a((z) (z) (z) (z) (z)) equal)
(test (create-array '(5 5) 'z) #2a((z z z z z) (z z z z z) (z z z z z) (z z z z z) (z z z z z)) equal)
(test (create-array '(1 2 3) 'z) #3a(((z z z) (z z z))) equal)


(defglobal array1 (create-array '(3 3 3) 0))
(test (list (aref array1 0 1 2)
       (setf (aref array1 0 1 2) 3.14)
       (aref array1 0 1 2))
 (0 3.14 3.14)
 equal)
(test (aref (create-array '(8 8) 6) 1 1) 6 eql)
(test (aref (create-array '() 19)) 19 eql)

;;;

(test (aref "abc" 0) #\a eql)
(test (aref "abc" 2) #\c eql)

(test (aref (create-string 1000 #\a) 999) #\a eql)
;;; Vector

(test (aref #(a b c) 0) a)
(test (aref #(a b c) 2) c)

(test (aref (create-vector 1000 19) 999) 19 eql)
;;; Array0
(test (aref array0) 19 eql)

(test (aref array2 0 0) 0 eql)
(test (aref array2 0 1) 1 eql)

(test (aref (create-array '(1000 1000) 19) 999 999) 19 eql)
;;; Array3

(test (aref array3 0 0 0) 0 eql)
(test (aref array3 0 0 1) 1 eql)
(test (aref array3 0 0 2) 2 eql)
(test (aref array3 0 1 0) 3 eql)
(test (aref array3 0 1 1) 4 eql)
(test (aref array3 0 1 2) 5 eql)

;;; (GAREF general-array z*) --> <object>
;;;

(test (garef #(a b c) 0) a)
(test (garef #(a b c) 2) c)

(test (garef (create-vector 1000 19) 999) 19 eql)
;;; Array0
(test (garef array0) 19 eql)

(test (garef array2 0 0) 0 eql)
(test (garef array2 0 1) 1 eql)


(test (garef (create-array '(1000 1000) 19) 999 999) 19 eql)

;;; Array3

(test (garef array3 0 0 0) 0 eql)
(test (garef array3 0 0 1) 1 eql)
(test (garef array3 0 0 2) 2 eql)
(test (garef array3 0 1 0) 3 eql)
(test (garef array3 0 1 1) 4 eql)
(test (garef array3 0 1 2) 5 eql)


(test (setf (aref array1 0 1 2) 3.15) 3.15 eql)
(test (set-aref 51.3 array1 0 1 2) 51.3 eql)
;;;

(test (let ((x "abc")) (list (setf (aref x 0) #\A) x)) (#\A "Abc") equal)
(test (let ((x "abc")) (list (setf (aref x 2) #\C) x)) (#\C "abC") equal)
(test (let ((x "abc")) (list (set-aref #\A x 0) x)) (#\A "Abc") equal)
(test (let ((x "abc")) (list (set-aref #\C x 2) x)) (#\C "abC") equal)

(test (let ((x (create-string 1000 #\a))) (list (setf (aref x 999) #\Z) (aref x 999)))
 (#\Z #\Z)
 equal)
(test (let ((x (create-string 1000 #\a))) (list (set-aref #\Z x 999) (aref x 999)))
 (#\Z #\Z)
 equal)
;;; Vector

(test (let ((x #(a b c))) (list (setf (aref x 0) 'z) x)) (z #(z b c)) equal)
(test (let ((x #(a b c))) (list (setf (aref x 2) 'z) x)) (z #(a b z)) equal)
(test (let ((x #(a b c))) (list (set-aref 'z x 0) x)) (z #(z b c)) equal)
(test (let ((x #(a b c))) (list (set-aref 'z x 2) x)) (z #(a b z)) equal)

(test (let ((x (create-vector 1000 'a))) (list (setf (aref x 999) 'z) (aref x 999)))
 (z z)
 equal)
(test (let ((x (create-vector 1000 'a))) (list (set-aref 'z x 999) (aref x 999)))
 (z z)
 equal)
;;; Array0
(test (let ((x (create-array () 'a))) (list (setf (aref x) 'z) (aref x)))
 (z z)
 equal)
(test (let ((x (create-array () 'a))) (list (set-aref 'z x) (aref x)))
 (z z)
 equal)

(test (let ((x #2a((0 1)))) (list (setf (aref x 0 0) 9) x)) (9 #2a((9 1))) equal)
(test (let ((x #2a((0 1)))) (list (setf (aref x 0 1) 9) x)) (9 #2a((0 9))) equal)
(test (let ((x #2a((0 1)))) (list (set-aref 9 x 0 0) x)) (9 #2a((9 1))) equal)
(test (let ((x #2a((0 1)))) (list (set-aref 9 x 0 1) x)) (9 #2a((0 9))) equal)

(test (let ((x (create-array '(1000 1000) 'a)))
   (list (setf (aref x 999 999) 'z) (aref x 999 999)))
 (z z)
 equal)
(test (let ((x (create-array '(1000 1000) 'a)))
   (list (set-aref 'z x 999 999) (aref x 999 999)))
 (z z)
 equal)
;;; Array3

(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (aref x 0 0 0) 9) x))
 (9 #3a(((9 1 2) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (aref x 0 0 1) 9) x))
 (9 #3a(((0 9 2) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (aref x 0 0 2) 9) x))
 (9 #3a(((0 1 9) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (aref x 0 1 0) 9) x))
 (9 #3a(((0 1 2) (9 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (aref x 0 1 1) 9) x))
 (9 #3a(((0 1 2) (3 9 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (aref x 0 1 2) 9) x))
 (9 #3a(((0 1 2) (3 4 9))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-aref 9 x 0 0 0) x))
 (9 #3a(((9 1 2) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-aref 9 x 0 0 1) x))
 (9 #3a(((0 9 2) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-aref 9 x 0 0 2) x))
 (9 #3a(((0 1 9) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-aref 9 x 0 1 0) x))
 (9 #3a(((0 1 2) (9 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-aref 9 x 0 1 1) x))
 (9 #3a(((0 1 2) (3 9 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-aref 9 x 0 1 2) x))
 (9 #3a(((0 1 2) (3 4 9))))
 equal)


;;;
;;; (SET-GAREF obj general-array z*) --> <object>
;;;

(test (let ((x #(a b c))) (list (setf (garef x 0) 'z) x)) (z #(z b c)) equal)
(test (let ((x #(a b c))) (list (setf (garef x 2) 'z) x)) (z #(a b z)) equal)
(test (let ((x #(a b c))) (list (set-garef 'z x 0) x)) (z #(z b c)) equal)
(test (let ((x #(a b c))) (list (set-garef 'z x 2) x)) (z #(a b z)) equal)
(test (let ((x (create-vector 1000 'a))) (list (setf (garef x 999) 'z) (garef x 999)))
 (z z)
 equal)
(test (let ((x (create-vector 1000 'a))) (list (set-garef 'z x 999) (garef x 999)))
 (z z)
 equal)
;;; Array0
(test (let ((x (create-array () 'a))) (list (setf (garef x) 'z) (garef x)))
 (z z)
 equal)
(test (let ((x (create-array () 'a))) (list (set-garef 'z x) (garef x)))
 (z z)
 equal)

(test (let ((x #2a((0 1)))) (list (setf (garef x 0 0) 9) x)) (9 #2a((9 1))) equal)
(test (let ((x #2a((0 1)))) (list (setf (garef x 0 1) 9) x)) (9 #2a((0 9))) equal)
(test (let ((x #2a((0 1)))) (list (set-garef 9 x 0 0) x)) (9 #2a((9 1))) equal)
(test (let ((x #2a((0 1)))) (list (set-garef 9 x 0 1) x)) (9 #2a((0 9))) equal)

(test (let ((x (create-array '(1000 1000) 'a)))
   (list (setf (garef x 999 999) 'z) (garef x 999 999)))
 (z z)
 equal)
(test (let ((x (create-array '(1000 1000) 'a)))
   (list (set-garef 'z x 999 999) (garef x 999 999)))
 (z z)
 equal)
;;; Array3

(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (garef x 0 0 0) 9) x))
 (9 #3a(((9 1 2) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (garef x 0 0 1) 9) x))
 (9 #3a(((0 9 2) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (garef x 0 0 2) 9) x))
 (9 #3a(((0 1 9) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (garef x 0 1 0) 9) x))
 (9 #3a(((0 1 2) (9 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (garef x 0 1 1) 9) x))
 (9 #3a(((0 1 2) (3 9 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (setf (garef x 0 1 2) 9) x))
 (9 #3a(((0 1 2) (3 4 9))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-garef 9 x 0 0 0) x))
 (9 #3a(((9 1 2) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-garef 9 x 0 0 1) x))
 (9 #3a(((0 9 2) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-garef 9 x 0 0 2) x))
 (9 #3a(((0 1 9) (3 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-garef 9 x 0 1 0) x))
 (9 #3a(((0 1 2) (9 4 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-garef 9 x 0 1 1) x))
 (9 #3a(((0 1 2) (3 9 5))))
 equal)
(test (let ((x #3a(((0 1 2) (3 4 5))))) (list (set-garef 9 x 0 1 2) x))
 (9 #3a(((0 1 2) (3 4 9))))
 equal)


(test (array-dimensions (create-array '(2 2) 0)) (2 2) equal)
(test (array-dimensions (vector 'a 'b)) (2) equal)
(test (array-dimensions "foo") (3) equal)
;;;

(test (array-dimensions array0) ())
(test (array-dimensions "") (0) equal)
(test (array-dimensions (create-string 1000)) (1000) equal)
(test (array-dimensions #()) (0) equal)
(test (array-dimensions (create-vector 1000)) (1000) equal)
(test (array-dimensions array2) (1 2) equal)
(test (array-dimensions (create-array '(1000 1000))) (1000 1000) equal)
(test (array-dimensions array3) (1 2 3) equal)
(test (array-dimensions (create-array '(100 100 100))) (100 100 100) equal)
