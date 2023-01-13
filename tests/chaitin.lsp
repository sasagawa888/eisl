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

          