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