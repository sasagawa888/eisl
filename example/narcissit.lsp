;;; narcissist-number
;;; e.g.  153 = 1^3 + 5^3 + 3^3 
;;;       1634 = 1^4 + 6^4 + 3^4 + 4^4
;;;       54748 = 5^5 + 4^5 + 7^5 + 4^5 + 8^5

(import "combination")

(defglobal ans nil)

(defun narcissist (n)
    (setq ans nil)
    (combination-with-repetition #'check n '(0 1 2 3 4 5 6 7 8 9)))

(defun check (ls)
    (permutation #'check1 (length ls) ls))

(defun check1 (ls)
    (cond ((and (= (list-to-nar ls (length ls))
                   (list-to-num ls))
                (/= (car ls) 0)
                (not (member ls ans)))
            (print ls) (setq ans (cons ls ans)))))

(defun list-to-nar (ls n)
    (if (null ls)
        0
        (+ (expt (car ls) n) (list-to-nar (cdr ls) n))))

(defun list-to-num (ls)
    (list-to-num1 ls 0))

(defun list-to-num1 (ls num)
    (if (null ls)
        num
        (list-to-num1 (cdr ls) (+ (* num 10) (car ls)))))