;; labels stress tests

(defun test-labels1 (n)
  ;; simple local recursion
  (labels ((fact (n acc)
             (if (= n 0)
                 acc
                 (fact (- n 1) (* n acc)))))
    (fact n 1)))

(defun test-labels2 (n)
  ;; mutual recursion
  (labels ((even? (n)
             (if (= n 0)
                 t
                 (odd? (- n 1))))
           (odd? (n)
             (if (= n 0)
                 nil
                 (even? (- n 1)))))
    (even? n)))

(defun test-labels3 (n)
  ;; mutual recursion, start from odd?
  (labels ((even? (n)
             (if (= n 0)
                 t
                 (odd? (- n 1))))
           (odd? (n)
             (if (= n 0)
                 nil
                 (even? (- n 1)))))
    (odd? n)))

(defun test-labels4 (x)
  ;; local function uses outer variable
  (labels ((addx (y)
             (+ x y)))
    (addx 10)))

(defun test-labels5 (x y)
  ;; multiple local functions, same outer variables
  (labels ((f (a) (+ a x))
           (g (b) (+ b y))
           (h (c) (+ (f c) (g c))))
    (h 10)))

(defun test-labels6 (n)
  ;; three-way mutual recursion
  (labels ((a (n)
             (if (= n 0) 'a (b (- n 1))))
           (b (n)
             (if (= n 0) 'b (c (- n 1))))
           (c (n)
             (if (= n 0) 'c (a (- n 1)))))
    (a n)))
#|
(defun test-labels7 (n)
  ;; nested labels
  (labels ((outer (x)
             (labels ((inner (y)
                        (+ x y)))
               (inner 100))))
    (outer n)))
|#


(defun test-labels8 (n)
  ;; local function name shadows global-like name
  (labels ((+ (x y)
             (* x y)))
    (+ n 10)))

#|
(defun test-labels9 (n)
  ;; labels body has multiple forms
  (labels ((f (x)
             (+ x 1)))
    (f n)
    (f (+ n 10))))
|#

(defun test-labels10 (n)
  ;; local recursive Fibonacci
  (labels ((fib (n)
             (if (< n 2)
                 n
                 (+ (fib (- n 1))
                    (fib (- n 2))))))
    (fib n)))

(defun test-labels11 (n)
  ;; tail recursion + mutual call
  (labels ((down-even (n acc)
             (if (= n 0)
                 acc
                 (down-odd (- n 1) (+ acc 1))))
           (down-odd (n acc)
             (if (= n 0)
                 acc
                 (down-even (- n 1) (+ acc 1)))))
    (down-even n 0)))

(defun test-labels12 (n)
  ;; labels inside conditional
  (if (= n 0)
      0
      (labels ((f (x)
                 (+ x 1)))
        (f n))))

(defun test-labels13 (n)
  ;; function defined later is called earlier
  (labels ((f (x)
             (g x))
           (g (x)
             (+ x 100)))
    (f n)))

(defun test-labels14 (n)
  ;; deeper forward reference chain
  (labels ((f (x) (g x))
           (g (x) (h x))
           (h (x) (+ x 1)))
    (f n)))

(defun test-labels15 (n)
  ;; same local function name in independent labels
  (+ (labels ((f (x) (+ x 1)))
       (f n))
     (labels ((f (x) (+ x 10)))
       (f n))))

(defun run-labels-tests ()
  (list
   (test-labels1 5)      ;; 120
   (test-labels2 10)     ;; T
   (test-labels2 11)     ;; NIL
   (test-labels3 10)     ;; NIL
   (test-labels3 11)     ;; T
   (test-labels4 7)      ;; 17
   (test-labels5 1 2)    ;; 23
   (test-labels6 0)      ;; A
   (test-labels6 1)      ;; B
   (test-labels6 2)      ;; C
   (test-labels6 3)      ;; A
   ;(test-labels7 5)      ;; 105
   (test-labels8 3)      ;; 30
   (test-labels9 1)      ;; 12
   (test-labels10 10)    ;; 55
   (test-labels11 10)    ;; 10
   (test-labels12 0)     ;; 0
   (test-labels12 9)     ;; 10
   (test-labels13 5)     ;; 105
   (test-labels14 5)     ;; 6
   (test-labels15 5)))   ;; 21

