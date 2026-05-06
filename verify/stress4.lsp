;; lambda + let + setq stress tests

(defun test-lambda-let1 (n)
  ((lambda (x)
     (let ((a (+ x 1)))
       (+ a 10)))
   n))

(defun test-lambda-let2 (n)
  ((lambda (x)
     (let ((a (+ x 1)))
       (+ a 10)
       (+ a 20)))
   n))

(defun test-lambda-setq1 (n)
  ((lambda (x)
     (let ((a x))
       (setq a (+ a 10))
       a))
   n))

(defun test-lambda-setq2 (n)
  ((lambda (x)
     (let ((a x)
           (b 1))
       (setq a (+ a b))
       (setq b (+ a 10))
       (+ a b)))
   n))

(defun test-lambda-nested1 (n)
  ((lambda (x)
     ((lambda (y)
        (+ x y))
      10))
   n))

(defun test-lambda-nested2 (n)
  ((lambda (x)
     ((lambda (y)
        (let ((z (+ x y)))
          (+ z 1)))
      10))
   n))

(defun test-lambda-let-setq1 (n)
  ((lambda (x)
     (let ((a x))
       (setq a (+ a 1))
       (setq a (+ a 2))
       a))
   n))

(defun test-lambda-let-setq2 (n)
  ((lambda (x)
     (let ((a x)
           (b (+ x 1)))
       (setq a (+ a b))
       (+ a b)))
   n))

(defun test-lambda-shadow1 (n)
  ;; variable shadowing
  ((lambda (x)
     (let ((x (+ x 10)))
       (+ x 1)))
   n))

(defun test-lambda-shadow2 (n)
  ;; deeper shadow
  ((lambda (x)
     (let ((x (+ x 10)))
       (let ((x (+ x 20)))
         (+ x 1))))
   n))

(defun test-lambda-multi-body (n)
  ((lambda (x)
     (+ x 1)
     (+ x 2)
     (+ x 3))
   n))

(defun test-lambda-let-nested (n)
  ((lambda (x)
     (let ((a (+ x 1)))
       (let ((b (+ a 2)))
         (+ a b))))
   n))

(defun test-lambda-mix1 (n)
  ((lambda (x)
     (let ((a x))
       (setq a (+ a 10))
       ((lambda (y)
          (+ a y))
        5)))
   n))

(defun test-lambda-mix2 (n)
  ((lambda (x)
     ((lambda (y)
        (let ((z (+ x y)))
          (setq z (+ z 1))
          z))
      5))
   n))

(defun run-all ()
  (list
   (test-lambda-let1 10)        ;; 21
   (test-lambda-let2 10)        ;; 31
   (test-lambda-setq1 10)       ;; 20
   (test-lambda-setq2 10)       ;; 32
   ;(test-lambda-nested1 10)     ;; 20
   ;(test-lambda-nested2 10)     ;; 21
   (test-lambda-let-setq1 10)   ;; 13
   (test-lambda-let-setq2 10)   ;; 32
   ;(test-lambda-shadow1 10)     ;; 21
   ;test-lambda-shadow2 10)     ;; 41
   (test-lambda-multi-body 10)  ;; 13
   (test-lambda-let-nested 10)  ;; 24
   ;(test-lambda-mix1 10)        ;; 25
   ;(test-lambda-mix2 10)        ;; 16
   ))