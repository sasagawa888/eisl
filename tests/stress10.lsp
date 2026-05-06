;; stress10.lsp
;; Stress test for practical ordinary code:
;; recursion, tail recursion, labels, list processing,
;; mapcar, lambda, for, while, member, append, reverse.

(defun test1 ()
  ;; tail recursion: sum 1..10
  (labels ((iter (n acc)
             (if (= n 0)
                 acc
                 (iter (- n 1) (+ acc n)))))
    (iter 10 0)))

(defun test2 ()
  ;; recursive list sum
  (labels ((sum-list (lst)
             (if (null lst)
                 0
                 (+ (car lst)
                    (sum-list (cdr lst))))))
    (sum-list '(1 2 3 4 5))))

(defun test3 ()
  ;; mapcar + lambda + outer variable
  (let ((a 100))
    (mapcar (lambda (x) (+ x a))
            '(1 2 3))))

(defun test4 ()
  ;; append + reverse
  (reverse
   (append '(1 2 3)
           '(4 5 6))))

(defun test5 ()
  ;; member
  (list (member 3 '(1 2 3 4))
        (member 5 '(1 2 3 4))))

(defun test6 ()
  ;; labels: local function calling another local function
  (labels ((f (x)
             (+ x 1))
           (g (x)
             (+ (f x) 10)))
    (g 5)))

(defun test7 ()
  ;; labels + tail recursion
  (labels ((iter (i sum)
             (if (= i 5)
                 sum
                 (iter (+ i 1)
                       (+ sum i)))))
    (iter 0 0)))

(defun test8 ()
  ;; mapcar + lambda + cond
  (mapcar
   (lambda (x)
     (cond ((< x 0) 'neg)
           ((= x 0) 'zero)
           (t 'pos)))
   '(-1 0 1)))

(defun test9 ()
  ;; nested lambda + outer variable
  (let ((a 10))
    (mapcar
     (lambda (x)
       ((lambda (y)
          (+ x y a))
        100))
     '(1 2 3))))

(defun test10 ()
  ;; labels + mapcar, but no lambda calls labels-local function
  (labels ((square (x)
             (* x x)))
    (mapcar #'square '(1 2 3 4))))

(defun test11 ()
  ;; while + list construction
  (let ((i 0)
        (res nil))
    (while (< i 5)
      (setq res (cons i res))
      (setq i (+ i 1)))
    (reverse res)))

(defun test12 ()
  ;; for + list construction
  (let ((res nil))
    (for ((i 0 (+ i 1)))
         ((>= i 5))
         (setq res (cons (* i i) res)))
    (reverse res)))

(defun test13 ()
  ;; recursive length
  (labels ((len (lst)
             (if (null lst)
                 0
                 (+ 1 (len (cdr lst))))))
    (len '(a b c d e))))

(defun test14 ()
  ;; recursive map-like function
  (labels ((add1-list (lst)
             (if (null lst)
                 nil
                 (cons (+ (car lst) 1)
                       (add1-list (cdr lst))))))
    (add1-list '(1 2 3 4))))

(defun test15 ()
  ;; simple filter-like recursion
  (labels ((positive-list (lst)
             (cond ((null lst) nil)
                   ((> (car lst) 0)
                    (cons (car lst)
                          (positive-list (cdr lst))))
                   (t
                    (positive-list (cdr lst))))))
    (positive-list '(-2 -1 0 1 2 3))))

(defun test16 ()
  ;; nested let + arithmetic
  (let ((a 10))
    (let ((b 20))
      (let ((c 30))
        (+ a b c)))))

(defun test17 ()
  ;; lambda + while + local list construction
  (mapcar
   (lambda (x)
     (let ((i 0)
           (res nil))
       (while (< i 3)
         (setq res (cons (+ x i) res))
         (setq i (+ i 1)))
       (reverse res)))
   '(10 20 30)))

(defun test18 ()
  ;; lambda + for + local list construction
  (mapcar
   (lambda (x)
     (let ((res nil))
       (for ((i 0 (+ i 1)))
            ((>= i 3))
            (setq res (cons (+ x i) res)))
       (reverse res)))
   '(10 20 30)))

(defun test19 ()
  ;; mixed append / reverse / mapcar
  (append
   (reverse '(3 2 1))
   (mapcar (lambda (x) (+ x 10)) '(1 2 3))))

(defun test20 ()
  ;; simple AtCoder-like counting
  (let ((lst '(1 2 3 4 5 6))
        (cnt 0))
    (while (not (null lst))
      (if (= (mod (car lst) 2) 0)
          (setq cnt (+ cnt 1))
          nil)
      (setq lst (cdr lst)))
    cnt))

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
        (test12)
        (test13)
        (test14)
        (test15)
        (test16)
        (test17)
        (test18)
        (test19)
        (test20)))