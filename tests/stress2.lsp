;; compiler-common-stress.lsp
;; labels を除いた頻出構文テスト

(defun test-if1 (n)
  (if (= n 0) 100 200))

(defun test-if2 (n)
  (if (< n 10)
      (+ n 1)
      (- n 1)))

(defun test-cond1 (n)
  (cond ((= n 0) 0)
        ((= n 1) 10)
        ((= n 2) 20)
        (t 99)))

(defun test-cond2 (n)
  ;; cond clause with multiple body forms
  (cond ((= n 0)
         (+ n 1)
         100)
        ((= n 1)
         (+ n 2)
         200)
        (t
         (+ n 3)
         999)))

(defun test-case1 (x)
  (case x
    ((a) 10)
    ((b) 20)
    ((c) 30)
    (t 99)))

(defun test-case2 (x)
  ;; case clause with multiple body forms
  (case x
    ((a)
     (+ 1 2)
     10)
    ((b)
     (+ 3 4)
     20)
    (t
     (+ 5 6)
     99)))

(defun test-progn1 (n)
  (progn
    (+ n 1)
    (+ n 2)
    (+ n 3)))

(defun test-let1 (n)
  (let ((a (+ n 1))
        (b (+ n 2)))
    (+ a b)))

(defun test-let2 (n)
  ;; let body multiple forms
  (let ((a (+ n 1)))
    (+ a 10)
    (+ a 20)))

(defun test-let-star1 (n)
  (let* ((a (+ n 1))
         (b (+ a 2))
         (c (+ b 3)))
    c))

(defun test-let-star2 (n)
  ;; let* body multiple forms
  (let* ((a (+ n 1))
         (b (+ a 10)))
    (+ b 1)
    (+ b 2)))

(defun test-setq1 (n)
  (let ((x n))
    (setq x (+ x 10))
    x))

(defun test-setq2 (n)
  (let ((x n)
        (y 1))
    (setq x (+ x y))
    (setq y (+ x 10))
    (+ x y)))

(defun test-and1 (a b)
  (and a b))

(defun test-and2 (n)
  (and (< n 10)
       (> n 0)
       (+ n 100)))

(defun test-or1 (a b)
  (or a b))

(defun test-or2 (n)
  (or (= n 0)
      (= n 1)
      (+ n 100)))

(defun test-not1 (x)
  (not x))

(defun test-while1 (n)
  ;; if Easy-ISLisp supports while
  (let ((i 0)
        (s 0))
    (while (< i n)
      (setq s (+ s i))
      (setq i (+ i 1)))
    s))

(defun test-for1 (n)
  ;; if Easy-ISLisp supports for as in compiler source
  (let ((s 0))
    (for ((i 0 (+ i 1)))
         ((> i n) s)
         (setq s (+ s i)))))

(defun test-rec1 (n)
  ;; simple recursion
  (if (= n 0)
      0
      (+ n (test-rec1 (- n 1)))))

(defun test-tail1 (n)
  (test-tail1-aux n 0))

(defun test-tail1-aux (n acc)
  (if (= n 0)
      acc
      (test-tail1-aux (- n 1) (+ acc n))))

(defun test-list1 (x y)
  (cons x y))

(defun test-list2 (x)
  (car (cons x '(2 3))))

(defun test-list3 (x)
  (cdr (cons x '(2 3))))

(defun test-list4 (x)
  (append x '(4 5)))

(defun test-equal1 (x)
  (equal x '(1 2 3)))

(defun test-null1 (x)
  (null x))

(defun test-atom1 (x)
  (atom x))

(defun test-number1 (n)
  (+ (* n 2) (- n 3)))

(defun test-number2 (n)
  (quotient (* n 10) 2))

(defun test-float1 (x)
  (+ x 1.5))

(defun test-apply1 (x)
  (apply #'+ (list x 10)))

(defun test-funcall1 (x)
  (funcall #'+ x 10))

(defun test-mapcar1 (lst)
  (mapcar #'car lst))

(defun test-lambda1 (n)
  ((lambda (x) (+ x 10)) n))

(defun test-lambda2 (n)
  (let ((f (lambda (x) (+ x n))))
    (funcall f 10)))

(defun test-block-return1 (n)
  ;; if block/return-from supported
  (block exit
    (if (= n 0)
        (return-from exit 100)
        200)))

(defun run-all ()
  (list
   (test-if1 0)              ;; 100
   (test-if1 1)              ;; 200
   (test-if2 5)              ;; 6
   (test-if2 20)             ;; 19
   (test-cond1 0)            ;; 0
   (test-cond1 1)            ;; 10
   (test-cond1 3)            ;; 99
   (test-cond2 0)            ;; 100
   (test-cond2 1)            ;; 200
   (test-cond2 9)            ;; 999
   (test-case1 'a)           ;; 10
   (test-case1 'b)           ;; 20
   (test-case1 'z)           ;; 99
   (test-case2 'a)           ;; 10
   (test-case2 'b)           ;; 20
   (test-case2 'z)           ;; 99
   (test-progn1 10)          ;; 13
   (test-let1 10)            ;; 23
   (test-let2 10)            ;; 31
   (test-let-star1 10)       ;; 16
   (test-let-star2 10)       ;; 23
   (test-setq1 10)           ;; 20
   (test-setq2 10)           ;; 32
   (test-and1 t nil)         ;; NIL
   (test-and1 t t)           ;; T
   (test-and2 5)             ;; 105
   (test-or1 nil 123)        ;; 123
   (test-or2 0)              ;; T
   (test-or2 5)              ;; 105
   (test-not1 nil)           ;; T
   (test-not1 t)             ;; NIL
   (test-rec1 10)            ;; 55
   (test-tail1 10)           ;; 55
   (test-list1 1 '(2 3))     ;; (1 2 3)
   (test-list2 1)            ;; 1
   (test-list3 1)            ;; (2 3)
   (test-list4 '(1 2 3))     ;; (1 2 3 4 5)
   (test-equal1 '(1 2 3))    ;; T
   (test-null1 nil)          ;; T
   (test-atom1 'a)           ;; T
   (test-number1 10)         ;; 27
   (test-number2 10)         ;; 50
   (test-float1 2.5)         ;; 4.0
   (test-apply1 5)           ;; 15
   (test-funcall1 5)         ;; 15
   (test-mapcar1 '((1 a) (2 b) (3 c))) ;; (1 2 3)
   (test-lambda1 5)          ;; 15
   (test-lambda2 5)          ;; 15
   ))