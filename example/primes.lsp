;;; Sieve of Eratosthenes
;;; primes(n) returns count of prime number in 2~n

(import "list")

(defun sieve (ls n)
  (cond ((null ls) nil)
        ((= (mod (car ls) n) 0) (sieve (cdr ls) n))
        (t (cons (car ls) (sieve (cdr ls) n)))))

(defun primes (n)
  (primes1 (iota 2 n) nil (isqrt n)))

(defun primes1 (ls p limit)
  (cond ((null ls) (length p))
        ((> (car ls) limit) (+ (length p) (length ls)))
        (t (primes1 (sieve (cdr ls) (car ls)) (cons (car ls) p) limit))))