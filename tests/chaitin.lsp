;; limits of mathematics G.J.chaitin
(import "test")

;;; string of program
;;; eval convert binary-list to string and save to program
(defglobal program nil)

(defun size (s)
   (length (sexp-to-bin s)))

;;; try is eval with time limit.
(defun try (option sexp binary)
    (setq program (create-string-input-stream (bin-to-string binary)))
    (cond ((and (symbolp option) (eq option 'no-time-limit)) (eval sexp))
          ((integerp option) (eval sexp option))))

;;; read sexp from string-input-stream
(defun read-exp ()
    (read program nil nil))

;;; UTM universal turing machine 
(defun U (p)
    (try 'no-time-limit
         (read)
         p))

#|
H(x,y) <= H(x)+H(y)+c
H(x) x means sexp.
H(x) means bit size of minimum UTM that calculate x.
H(y) means bit size of minimum UTM that calculate x.

φc x* y* 
x* means minimum size program of x
y* means minimum size program of y
φc is prefix for constant c

(cons (eval read) (cons (eval read))) -> it make pair of x and y.
|#          

(defglobal s '(cons (eval (read-exp)) (cons (eval (read-exp)) nil)))

;;; make binaly list of s-expression
;;; add newline to sexp 
(defun sexp-to-bin (s)
    (let ((stream (create-string-output-stream))
          (str nil))
        (format stream "~A~%" s)
        (setq str (get-output-stream-string stream))
        (for ((i 0 (+ i 1))
              (limit (length str))
              (bin nil (append bin (char-to-bin (elt str i)))))
             ((>= i limit) bin))))

;;; make list of binaly. reverse ascii code. 
(defun int-to-bin (n m)
    (cond ((= m 0) nil) 
          ((< n 2) (cons n (int-to-bin 0 (- m 1))))
          (t (cons (mod n 2) (int-to-bin (div n 2) (- m 1))))))

;;; make binaly list of charactor c
(defun char-to-bin (c)
    (int-to-bin (convert c <integer>) 8))

;;; make string from binaly
(defun bin-to-string (ls)
    (charlist-to-string (bin-to-charlist ls)))

(defun charlist-to-string (ls)
    (if (null ls)
        ""
        (string-append (convert (car ls) <string>)
                       (charlist-to-string (cdr ls)))))

(defun bin-to-charlist (ls)
    (if (null ls)
        nil
        (cons (convert (bin-to-int (get-8 ls)) <character>)
              (bin-to-charlist (rest-8 ls)))))

(defun bin-to-int (ls)
    (if (null ls)
        0
        (+ (car ls) (* 2 (bin-to-int (cdr ls))))))

(defun get-8 (ls)
    (list (elt ls 0) (elt ls 1) (elt ls 2) (elt ls 3)
          (elt ls 4) (elt ls 5) (elt ls 6) (elt ls 7)))

(defun rest-8 (ls)
    (cdr (cdr (cdr (cdr (cdr (cdr (cdr (cdr ls)))))))))

;;; test
($test (size '(+ 1 2)) 64)
($test (size '(cons (eval (read-exp)) (cons (eval (read-exp)) nil))) 432)