;; limits of mathematics G.J.chaitin

(defun size (s)
    (cond ((symbolp s) (length (convert s <string>)))
          ((stringp s) (+ 2 (length s)))
          ((numberp s) (length (convert s <string>)))
          ((characterp s) 2)
          ((eq (class-of s) (class <general-vector>)) (size (convert s <list>)))
          ((consp s) (size-list s)))
)

(defun size-list (ls)
    (cond ((null ls) 1)
          (t (+ (size (car ls))  1 (size-list (cdr ls))))))

;;; try is eval with time limit.
(defun try (option sexp binary)
    (cond ((and (symbolp option) (eq option 'no-time-limit)) (eval sexp))
          ((integerp option) (eval sexp option))))

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
(defun sexp-to-bin (s)
    (let ((stream (create-string-output-stream))
          (str nil))
        (format stream "~A" s)
        (setq str (get-output-stream-string stream))
        (for ((i 0 (+ i 1))
              (limit (length str))
              (bin nil (append (char-to-bin (elt str i)) bin)))
             ((>= i limit) bin))))

;;; make list of binaly. reverse ascii code. 
(defun int-to-bin (n m)
    (cond ((= m 0) nil) 
          ((< n 2) (cons n (int-to-bin n (- m 1))))
          (t (cons (mod n 2) (int-to-bin (div n 2) (- m 1))))))

;;; make binaly list of charactor c
(defun char-to-bin (c)
    (int-to-bin (convert c <integer>) 8))
