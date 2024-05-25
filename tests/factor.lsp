;; factorize
;; n = p*q. p <> q, p and q is near prime number.
;; e.g. 100000007 * 100000039 = 10000004600000273
;; 1000037 * 100000039 = 100003739001443
;; 1000000009 * 1000000063 = 1000000072000000567
;; 10000000033 * 10000000019 = 100000000520000000627
;;para
(defun factors* (n)
    (let ((r (sieve (factors1* n))))
        (if (= (length r) 1)
            (list (elt r 0) (div n (elt r 0)))
            r)))

(defun factors1* (n)
    (let* ((limit (isqrt n))
           (span (+ (div limit 5) 1)))
        (mp-let ((r0 (cofactor n 3 span))
                 (r1 (cofactor n (near-odd span) (* 2 span)))
                 (r2 (cofactor n (near-odd (* 2 span)) (* 3 span)))
                 (r3 (cofactor n (near-odd (* 3 span)) (* 4 span)))
                 (r4 (cofactor n (near-odd (* 4 span)) (* 5 span))))
            (append r0 r1 r2 r3 r4))))

(defun cofactor (n s e)
    (cond ((> s e) nil)
          ((= (mod n s) 0) (cons s (cofactor n (+ s 2) e)))
          (t (cofactor n (+ s 2) e))))


(defun near-odd (n)
    (if (= (mod n 2) 0)
        (- n 1)
        n))

(defun sieve (ls)
    (sieve1 (car ls) (cdr ls)))

(defun sieve1 (n ls)
    (cond ((null ls) (cons n ls))
          (t (let ((ls1 (remove n ls)))
                (cons n (sieve1 (car ls1) (cdr ls1)))))))

(defun remove (n ls)
    (cond ((null ls) ls)  
          ((= (mod (car ls) n) 0) (remove n (cdr ls)))
          (t (cons (car ls) (remove n (cdr ls))))))



;; sequence
(defun factors (n)
    (cond ((= (mod n 2) 0) (cons 2 (factors1 (div n 2) 3 (isqrt (div n 2)))))
          (t (factors1 n 3 (isqrt n)))))

(defun factors1 (n s e)
    (cond ((> s e) (list n))
          ((= (mod n s) 0) (cons s (factors1 (div n s) s (isqrt (div n s)))))
          (t (factors1 n (+ s 2) e))))
