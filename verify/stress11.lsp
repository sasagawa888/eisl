;; stress11 
;; tests shadowing in let*

(defun test-let*-shadow1 (n)
    (let* ((x (+ n 1))
           (x (+ x 10)) )
        (+ x 1)))

(defun test-let*-shadow2 (n)
    (let* ((x n)
           (y x)
           (x (+ y 1)) )
        (+ x y)))

(defun test-let*-shadow3 (n)
   (let* ((x 10))
       ((lambda (x) (+ x 1)) 20)))
;; => 21
(defun test-let*-shadow4 (n)
   (let* ((a 10))
       ((lambda (x y) (+ a x y)) 1 2)))
;; => 13