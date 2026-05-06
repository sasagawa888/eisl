;; stress7.lsp
;; boundary / edge-case stress tests

(defun test-boundary1 ()
  ;; zero arguments
  123)

(defun test-boundary2 (x)
  ;; nil input
  (if (null x) 'nil-case 'non-nil-case))

(defun test-boundary3 (x)
  ;; empty list
  (length x))

(defun test-boundary4 (x)
  ;; atom/list branching
  (if (atom x) 'atom 'list))

(defun test-boundary5 (n)
  ;; zero recursion
  (if (= n 0)
      0
      (+ 1 (test-boundary5 (- n 1)))))

(defun test-boundary6 (n)
  ;; negative number branch
  (cond ((< n 0) 'negative)
        ((= n 0) 'zero)
        (t 'positive)))

(defun test-boundary7 (x)
  ;; quoted symbols
  (case x
    ((a) 'A)
    ((b) 'B)
    (t 'OTHER)))

(defun test-boundary8 (x)
  ;; nested nil/list
  (if (null (cdr x))
      'single
      'many))

(defun test-boundary9 (x)
  ;; car/cdr after cons
  (cons (car x) (cdr x)))

(defun test-boundary10 (n)
  ;; larger tail recursion
  (test-boundary10-aux n 0))

(defun test-boundary10-aux (n acc)
  (if (= n 0)
      acc
      (test-boundary10-aux (- n 1) (+ acc 1))))

(defun test-boundary11 (x)
  ;; equal with nil
  (equal x nil))

(defun test-boundary12 (x)
  ;; equal with nested list
  (equal x '((1 2) (3 4))))

(defun test-boundary13 (n)
  ;; arithmetic around zero
  (+ (- n n) (* n 0)))

(defun test-boundary14 (n)
  ;; quotient boundary, avoid division by zero
  (if (= n 0)
      0
      (quotient 100 n)))

(defun test-boundary15 (x)
  ;; multiple body in progn with nil result possibility
  (progn
    (+ 1 2)
    (if x x nil)))

(defun run-all ()
  (list
   (test-boundary1)                 ;; 123
   (test-boundary2 nil)             ;; NIL-CASE
   (test-boundary2 '(1))            ;; NON-NIL-CASE
   (test-boundary3 nil)             ;; 0
   (test-boundary3 '(1 2 3))        ;; 3
   (test-boundary4 'a)              ;; ATOM
   (test-boundary4 '(a b))          ;; LIST
   (test-boundary5 0)               ;; 0
   (test-boundary5 5)               ;; 5
   (test-boundary6 -1)              ;; NEGATIVE
   (test-boundary6 0)               ;; ZERO
   (test-boundary6 1)               ;; POSITIVE
   (test-boundary7 'a)              ;; A
   (test-boundary7 'z)              ;; OTHER
   (test-boundary8 '(1))            ;; SINGLE
   (test-boundary8 '(1 2))          ;; MANY
   (test-boundary9 '(1 2 3))        ;; (1 2 3)
   (test-boundary10 100)            ;; 100
   (test-boundary11 nil)            ;; T
   (test-boundary11 'a)             ;; NIL
   (test-boundary12 '((1 2) (3 4))) ;; T
   (test-boundary12 '((1 2)))       ;; NIL
   (test-boundary13 10)             ;; 0
   (test-boundary14 0)              ;; 0
   (test-boundary14 10)             ;; 10
   (test-boundary15 nil)            ;; NIL
   (test-boundary15 'ok)))          ;; OK
