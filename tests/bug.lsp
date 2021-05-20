(import "test")

;; ((x <integer>) (y <integer>)) (a b) -> ((a <integer>) (b <integer>))
(defun alpha-conv-varlis (x y)
  (if (null x)
      nil 
      (cons (list (car y) (elt (car x) 1))
            (alpha-conv-varlis (cdr x) (cdr y)))))


;; ((x <integer>) (y <integer>)) (a b) -> ((x . a) (y . b))
(defun method-varlis-to-substlist (x y)
  (if (null x)
      nil 
      (cons (cons (car (car x)) (car y))
            (method-varlis-to-substlist (cdr x) (cdr y)))))

;; (COND ((= N 1) 1) ((= N 2) 1) (T (+ (GFIB (- N 1)) (GFIB (- N 2)))))) ((n . a)) -> 
;; (COND ((= a 1) 1) ((= a 2) 1) (T (+ (GFIB (- a 1)) (GFIB (- a 2))))))
(defun alpha-conv-method (x y)
  (cond ((null x) nil)
        ((and (symbolp x) (alpha-var x y)) (alpha-var x y))
        ((atom x) x)
        (t (cons (alpha-conv-method (car x) y)
                 (alpha-conv-method (cdr x) y)))))

(defun alpha-var (x y)
  (cond ((null y) nil)
        ((eq x (car (car y))) (cdr (car y)))
        (t (alpha-var x (cdr y)))))

(test (alpha-conv-method '((COND ((= N 1) 1) ((= N 2) 1) (T (+ (GFIB (- N 1)) (GFIB (- N 2)))))) '((n . a)))
                           ((COND ((= a 1) 1) ((= a 2) 1) (T (+ (GFIB (- a 1)) (GFIB (- a 2)))))))