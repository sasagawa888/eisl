;; nested control stress tests

(defun test-nest1 (n)
  ;; let inside let
  (let ((a (+ n 1)))
    (let ((b (+ a 2)))
      (+ a b))))

(defun test-nest2 (n)
  ;; let + cond
  (let ((a (+ n 1)))
    (cond ((= a 0) 0)
          ((= a 1) 10)
          (t (+ a 100)))))

(defun test-nest3 (n)
  ;; cond + let
  (cond ((= n 0)
         (let ((x 10))
           (+ x 1)))
        (t
         (let ((y 20))
           (+ y 2)))))

(defun test-nest4 (x)
  ;; case + let
  (case x
    ((a)
     (let ((v 10))
       (+ v 1)))
    ((b)
     (let ((v 20))
       (+ v 2)))
    (t
     (let ((v 30))
       (+ v 3)))))

(defun test-nest5 (n)
  ;; let* + cond (dependency)
  (let* ((a (+ n 1))
         (b (+ a 2)))
    (cond ((= b 0) 0)
          ((= b 1) 10)
          (t (+ a b)))))

(defun test-nest6 (n)
  ;; nested cond
  (cond ((= n 0)
         (cond ((= n 0) 100)
               (t 200)))
        (t
         (cond ((= n 1) 300)
               (t 400)))))

(defun test-nest7 (x)
  ;; nested case
  (case x
    ((a)
     (case x
       ((a) 10)
       (t 20)))
    ((b)
     (case x
       ((b) 30)
       (t 40)))
    (t 50)))

(defun test-nest8 (n)
  ;; cond with multiple body forms + let
  (cond ((= n 0)
         (+ n 1)
         (let ((x 10))
           (+ x 1)))
        (t
         (+ n 2)
         (let ((y 20))
           (+ y 2)))))

(defun test-nest9 (n)
  ;; let body with nested cond
  (let ((a (+ n 1)))
    (+ a 10)
    (cond ((= a 0) 0)
          (t (+ a 100)))))

(defun test-nest10 (n)
  ;; deep nesting
  (let ((a (+ n 1)))
    (cond ((= a 0)
           (let ((b 10))
             (case b
               ((10) (+ b 1))
               (t 0))))
          (t
           (let ((c 20))
             (case c
               ((20) (+ c 2))
               (t 0)))))))

(defun run-all ()
  (list
   (test-nest1 10)   ;;  (a=11 b=13) => 24
   (test-nest2 0)    ;; 101
   (test-nest3 0)    ;; 11
   (test-nest3 5)    ;; 22
   (test-nest4 'a)   ;; 11
   (test-nest4 'b)   ;; 22
   (test-nest4 'z)   ;; 33
   (test-nest5 10)   ;; a=11 b=13 => 24
   (test-nest6 0)    ;; 100
   (test-nest6 1)    ;; 300
   (test-nest6 5)    ;; 400
   (test-nest7 'a)   ;; 10
   (test-nest7 'b)   ;; 30
   (test-nest7 'z)   ;; 50
   (test-nest8 0)    ;; 11
   (test-nest8 5)    ;; 22
   (test-nest9 0)    ;; a=1 => 101
   (test-nest10 0)   ;; 21
   ))