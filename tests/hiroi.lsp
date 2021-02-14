;; test from M.Hiroi home page

(defun factor-sub (n m)
    (for ((i 0 (+ i 1))
          (n n) )
         ((/= (mod n m) 0)
          (cons i n) )
         (setq n (quotient n m))))

(defun factorization (n)
    (let* ((xs (factor-sub n 2))
           (c (car xs)) )
        (setq n (cdr xs))
        (for ((i 3 (+ i 2))
              (a (if (= c 0)
                    nil
                    (list (cons 2 c)))) )
             ((or (= n 1) (< n (* i i)))
              (nreverse (if (= n 1)
                           a
                           (cons (cons n 1) a))) )
             (setq xs (factor-sub n i))
             (setq c (car xs))
             (setq n (cdr xs))
             (if (< 0 (car xs))
                 (setq a (cons (cons i c) a))))))

