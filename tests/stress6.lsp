;; stress6.lsp
;; compiled / interpreted mixed call stress tests

(defun interp-add (x y)
  (+ x y))

(defun interp-inc (x)
  (+ x 1))

(defun interp-pred (x)
  (> x 0))

(defun interp-list (x)
  (cons x '(a b)))

(defun test-mixed1 (n)
  ;; compiled -> interpreted simple call
  (interp-inc n))

(defun test-mixed2 (n)
  ;; compiled -> interpreted with multiple args
  (interp-add n 10))

(defun test-mixed3 (n)
  ;; interpreted call inside let
  (let ((a (interp-inc n)))
    (+ a 10)))

(defun test-mixed4 (n)
  ;; interpreted call inside cond
  (cond ((interp-pred n) (interp-add n 100))
        (t 0)))

(defun test-mixed5 (n)
  ;; interpreted call inside if
  (if (interp-pred n)
      (interp-add n 1)
      (interp-add n 2)))

(defun test-mixed6 (n)
  ;; interpreted returns list
  (car (interp-list n)))

(defun test-mixed7 (lst)
  ;; compiled function using interpreted helper through mapcar
  (mapcar #'interp-inc lst))

(defun test-mixed8 (n)
  ;; interpreted call result used as argument
  (interp-add (interp-inc n) (interp-inc 10)))

(defun test-mixed9 (n)
  ;; recursive compiled function calling interpreted helper
  (if (= n 0)
      0
      (interp-add n (test-mixed9 (- n 1)))))

(defun test-mixed10 (n)
  ;; tail-style compiled recursion with interpreted arithmetic
  (test-mixed10-aux n 0))

(defun test-mixed10-aux (n acc)
  (if (= n 0)
      acc
      (test-mixed10-aux (- n 1) (interp-add acc n))))

(defun run-all ()
  (list
   (test-mixed1 10)       ;; 11
   (test-mixed2 10)       ;; 20
   (test-mixed3 10)       ;; 21
   (test-mixed4 5)        ;; 105
   (test-mixed4 -1)       ;; 0
   (test-mixed5 5)        ;; 6
   (test-mixed5 -1)       ;; 1
   (test-mixed6 99)       ;; 99
   (test-mixed7 '(1 2 3)) ;; (2 3 4)
   (test-mixed8 5)        ;; 17
   (test-mixed9 10)       ;; 55
   (test-mixed10 10)))    ;; 55