;; stress9.lsp
;; Stress test for ordinary forms:
;; while, for, if, cond, case, and, or, let*, lambda, mapcar, setq

(defun test1 ()
  ;; while + setq
  (let ((i 0)
        (sum 0))
    (while (< i 5)
      (setq sum (+ sum i))
      (setq i (+ i 1)))
    sum))

(defun test2 ()
  ;; while + if
  (let ((i 0)
        (sum 0))
    (while (< i 6)
      (if (= (mod i 2) 0)
          (setq sum (+ sum i))
          nil)
      (setq i (+ i 1)))
    sum))

(defun test3 ()
  ;; while + cond
  (let ((i -2)
        (neg 0)
        (zero 0)
        (pos 0))
    (while (<= i 2)
      (cond ((< i 0) (setq neg (+ neg 1)))
            ((= i 0) (setq zero (+ zero 1)))
            (t       (setq pos (+ pos 1))))
      (setq i (+ i 1)))
    (list neg zero pos)))

(defun test4 ()
  ;; mapcar + lambda + if
  (mapcar
   (lambda (x)
     (if (> x 2)
         (+ x 10)
         (+ x 100)))
   '(1 2 3 4)))

(defun test5 ()
  ;; mapcar + lambda + cond
  (mapcar
   (lambda (x)
     (cond ((< x 0) 'negative)
           ((= x 0) 'zero)
           (t       'positive)))
   '(-1 0 1)))

(defun test6 ()
  ;; mapcar + lambda + case
  (mapcar
   (lambda (x)
     (case x
       ((1) 'one)
       ((2) 'two)
       (t   'other)))
   '(1 2 3)))

(defun test7 ()
  ;; lambda + let* + outer variable
  (let ((a 10))
    (mapcar
     (lambda (x)
       (let* ((b (+ x a))
              (c (+ b 1)))
         c))
     '(1 2 3))))

(defun test8 ()
  ;; lambda + while + local accumulation
  (mapcar
   (lambda (x)
     (let ((i 0)
           (sum 0))
       (while (< i 3)
         (setq sum (+ sum x i))
         (setq i (+ i 1)))
       sum))
   '(1 2 3)))

(defun test9 ()
  ;; lambda + for + if
  (mapcar
   (lambda (x)
     (let ((sum 0))
       (for ((i 0 (+ i 1)))
            ((>= i 5))
            (if (= (mod i 2) 0)
                (setq sum (+ sum x i))
                nil))
       sum))
   '(1 2 3)))

(defun test10 ()
  ;; and / or in lambda
  (mapcar
   (lambda (x)
     (cond ((and (> x 0) (< x 3)) 'small)
           ((or (= x 3) (= x 4)) 'middle)
           (t 'other)))
   '(0 1 2 3 4 5)))

(defun test11 ()
  ;; labels without lambda: supported case
  (labels ((foo (x)
             (+ x 1))
           (bar (y)
             (+ (foo y) 10)))
    (list (foo 1)
          (bar 1)
          (bar 10))))

(defun test12 ()
  ;; labels + for, but no lambda calls labels-local function
  (labels ((sum-to (n)
             (let ((sum 0))
               (for ((i 0 (+ i 1)))
                    ((> i n))
                    (setq sum (+ sum i)))
               sum)))
    (list (sum-to 3)
          (sum-to 5))))

(defun test13 ()
  ;; nested lambda, no labels
  (let ((a 100))
    (mapcar
     (lambda (x)
       ((lambda (y)
          (+ x y a))
        10))
     '(1 2 3))))

(defun test14 ()
  ;; for + multiple variables
  (let ((sum 0))
    (for ((i 0 (+ i 1))
          (j 10 (+ j 10)))
         ((>= i 3))
         (setq sum (+ sum i j)))
    sum))

(defun test15 ()
  ;; while + nested let
  (let ((i 0)
        (sum 0))
    (while (< i 3)
      (let ((x (+ i 10)))
        (setq sum (+ sum x)))
      (setq i (+ i 1)))
    sum))

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
        (test15)))