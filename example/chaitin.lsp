#|
limits of mathematics G.J.chaitin
H(x,y) <= H(x)+H(y)+c
in H(x) x means sexp.
H(x) means bit size of minimum UTM that calculate x.
H(y) means bit size of minimum UTM that calculate y.

φc x* y* 
x* means minimum size program of x
y* means minimum size program of y
φc is prefix for constant c

(cons (eval (read-exp)) (cons (eval (read-exp)) nil) -> it make pair of x and y.
|#          

(import "test")

;;; input-string-stream of program
;;; try function convert binary-list to string-stream and save it to var program
(defglobal program nil)

;;; try is eval with time limit.
;;; if error occurs, try function ignore error and return nil.
;;; if eval can't calculate in limited time, return (failse nil intermediate-result)
;;; if eval can calcurate int limited time, return (success val intermediate-result)
;;; if option is 'no-time-limit, eval calculate with no-time-limit.
(defun try (time sexp binary)
    (setq program (create-string-input-stream (bin-to-str binary)))
    ;; need syntax check. if program has syntax error, avoid the binary
    (cond ((and (symbolp time) (eq time 'no-time-limit)) (ignore-errors (eval sexp)))
          ((integerp time) (let ((result (ignore-errors (eval sexp time))))
                                (if (null result)
                                    '(failse nil error)
                                    result)))
          (t (error "try: improper limit" time))))

;;; read sexp from string-input-stream
(defun read-exp ()
    (read program nil nil))

;;; UTM universal turing machine 
(defun U (p)
    (try 'no-time-limit
         '(eval (read-exp))
         p))

;;; make binary list of s-expression
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

;;; make list of binary. reverse ascii code. 
(defun int-to-bin (n m)
    (cond ((= m 0) nil) 
          ((< n 2) (cons n (int-to-bin 0 (- m 1))))
          (t (cons (mod n 2) (int-to-bin (div n 2) (- m 1))))))

;;; make binary list of charactor c
(defun char-to-bin (c)
    (int-to-bin (convert c <integer>) 8))

;;; make string from binary
(defun bin-to-str (ls)
    (charlist-to-str (bin-to-charlist ls)))

;;; help function for bin-to-str
(defun charlist-to-str (ls)
    (if (null ls)
        ""
        (string-append (char-to-str (car ls))
                       (charlist-to-str (cdr ls)))))

(defun char-to-str (c)
    (cond ((char< c #\space) "")
          ((char> c #\z) "")
          ;((char= c #\") "")
          (t (convert c <string>))))

;;; help function for bin-to-str
(defun bin-to-charlist (ls)
    (if (null ls)
        nil
        (cons (convert (bin-to-int (get-8 ls)) <character>)
              (bin-to-charlist (rest-8 ls)))))

;;; help function for bin-to-str
;;; e.g. (1 1 0 0 0 0 0 0) -> 3
(defun bin-to-int (ls)
    (if (null ls)
        0
        (+ (car ls) (* 2 (bin-to-int (cdr ls))))))

;;; help function for bin-to-str
;;; get first 8 bit
(defun get-8 (ls)
    (list (elt ls 0) (elt ls 1) (elt ls 2) (elt ls 3)
          (elt ls 4) (elt ls 5) (elt ls 6) (elt ls 7)))

;;; help function for bin-to-str
;;; get rest binary
(defun rest-8 (ls)
    (cdr (cdr (cdr (cdr (cdr (cdr (cdr (cdr ls)))))))))


;;; size of s-exp in binary
(defun size (s)
   (length (sexp-to-bin s)))

;;; loop function
;;; eval can't calculate foo function.
(defun foo ()
    (foo))

#|
if generated s-exp occures error. control is but.
bit list generate many syntax error. so, before (read-exp) need to check syntax.
memo
(read-exp) is user defiend function. so, apply push ep(environment) and pop ep.
but if occures error, igonore-errors dose not restore ep. problem is this one.
idea ignore-errors check s-exp. if s-exp is user-defined-function and occures error, pop ep.
e.g. (eval (read-exp)) eval is subr, read-exp is user-defined. How solve it.
idea apply user-defined-function  begining set flag execute_flag and ending reset execute_flag.
igonore-errors check execute_flag and if it is on pop ep. 
|#
(defun count-halt (time prefix bit-left)
    (if (= bit-left 0)
        (check prefix)
        (+ (count-halt time (cons 0 prefix) (- bit-left 1))
           (count-halt time (cons 1 prefix) (- bit-left 1)))))

(defun check (prefix)
     (break)
     (try 100 '(eval (read-exp)) '(0 1 0 0 0 1 0 0))
     ;; try destry environment ep why?
     ;; try function must save environment ep. 
     ;; need to use C-wrapper for try. 
     (break)
     (print prefix) 
     1)
    ;(if (eq 'success (try 100 '(eval (read-exp)) '(0 1 0 0 0 1 0 0)))
    ;        1 
    ;        0))

;;; test
($test (size '(+ 1 2)) 64)
($test (size '(cons (eval (read-exp)) (cons (eval (read-exp)) nil))) 432)
($test (bin-to-int '(1 1 0 0 0 0 0 0)) 3)
($test (sexp-to-bin '(+ 1 2))
  (0 0 0 1 0 1 0 0 1 1 0 1 0 1 0 0 0 0 0 0 0 1 0 0 1 0 0 0 1 1 0 0 0 0 0 0 0 1 0 0 0 1 0 0 1 1 0 0 1 0 0 1 0 1 0 0 0 1 0 1 0 0 0 0))
($test (u (sexp-to-bin '(+ 1 2))) 3)
($test (u (sexp-to-bin '(+ g 2))) nil)
($test (car (try 100 '(eval (read-exp)) (sexp-to-bin '(foo)))) failse)
($test (car (try 100 '(eval (read-exp)) (sexp-to-bin '(+ 1 2)))) success)
($test (car (try 100 '(eval (read-exp)) (sexp-to-bin '(+ h 2)))) failse)