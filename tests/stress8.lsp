;; stress8.lsp
;; Stress test for frequent forms: for, let, lambda, mapcar, labels, setq

(defun test1 ()
  ;; simple for accumulation
  (let ((sum 0))
    (for ((i 0 (+ i 1)))
         ((>= i 5))
         (setq sum (+ sum i)))
    sum))


(defun test2 ()
  ;; for with outer let variable
  (let ((a 10)
        (sum 0))
    (for ((i 0 (+ i 1)))
         ((>= i 3))
         (setq sum (+ sum i a)))
    sum))

(defun test3 ()
  ;; nested for
  (let ((sum 0))
    (for ((i 0 (+ i 1)))
         ((>= i 3))
         (for ((j 0 (+ j 1)))
              ((>= j 3))
              (setq sum (+ sum i j))))
    sum))

(defun test4 ()
  ;; for inside lambda
  (mapcar
   (lambda (x)
     (let ((sum 0))
       (for ((i 0 (+ i 1)))
            ((>= i 3))
            (setq sum (+ sum x i)))
       sum))
   '(1 2 3)))


(defun test5 ()
  ;; lambda inside for
  (let ((a 100)
        (res nil))
    (for ((i 0 (+ i 1)))
         ((>= i 3))
         (setq res
               (cons ((lambda (x) (+ x a)) i)
                     res)))
    (reverse res)))

(defun test6 ()
  ;; nested lambda inside for
  (let ((a 100)
        (res nil))
    (for ((i 0 (+ i 1)))
         ((>= i 3))
         (setq res
               (cons ((lambda (x)
                        ((lambda (y) (+ x y a)) 10))
                      i)
                     res)))
    (reverse res)))

(defun test7 ()
  ;; for inside labels
  (labels ((foo (n)
             (let ((sum 0))
               (for ((i 0 (+ i 1)))
                    ((>= i n))
                    (setq sum (+ sum i)))
               sum)))
    (foo 5)))

(defun test8 ()
  ;; labels + lambda + for
  (labels ((foo (x)
             (let ((sum 0))
               (for ((i 0 (+ i 1)))
                    ((>= i 3))
                    (setq sum (+ sum x i)))
               sum)))
    (mapcar (lambda (n) (foo n)) '(10 20 30))))

(defun test9 ()
  ;; for variable should not capture outer same-name incorrectly
  (let ((i 100)
        (sum 0))
    (for ((i 0 (+ i 1)))
         ((>= i 3))
         (setq sum (+ sum i)))
    (list i sum)))

(defun test10 ()
  ;; multiple loop variables
  (let ((sum 0))
    (for ((i 0 (+ i 1))
          (j 10 (+ j 10)))
         ((>= i 3))
         (setq sum (+ sum i j)))
    sum))

(defun test11 ()
  ;; for + cond
  (let ((pos 0)
        (zero 0))
    (for ((i -2 (+ i 1)))
         ((> i 2))
         (cond ((= i 0) (setq zero (+ zero 1)))
               ((> i 0) (setq pos (+ pos 1)))
               (t nil)))
    (list pos zero)))

(defun test12 ()
  ;; for + case
  (let ((a 0)
        (b 0)
        (c 0))
    (for ((x 0 (+ x 1)))
         ((>= x 5))
         (case x
           ((0 1) (setq a (+ a 1)))
           ((2 3) (setq b (+ b 1)))
           (t     (setq c (+ c 1)))))
    (list a b c)))

(defun run-all ()
  (list (test1)
        (test2)
        (test3)
        (test4)
        (test5)
        (test6)
        (test7)
        (test8)
        (test9)
        (test10)
        (test11)
        (test12)))
    