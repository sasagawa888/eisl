;; stress5.lsp
;; mapcar + lambda stress tests

(defun test-map-lambda1 (lst)
  (mapcar (lambda (x) (+ x 1)) lst))

(defun test-map-lambda2 (lst)
  (mapcar (lambda (x)
            (+ x 1)
            (+ x 2))
          lst))

(defun test-map-lambda3 (lst)
  (let ((a 10))
    (mapcar (lambda (x) (+ x a)) lst)))

(defun test-map-lambda4 (lst)
  (let ((a 10))
    (setq a 20)
    (mapcar (lambda (x) (+ x a)) lst)))

(defun test-map-lambda5 (lst)
  (mapcar (lambda (x)
            (let ((y (+ x 10)))
              (+ y 1)))
          lst))

(defun test-map-lambda6 (lst)
  (mapcar (lambda (x)
            (cond ((= x 0) 100)
                  ((= x 1) 200)
                  (t (+ x 10))))
          lst))

(defun test-map-lambda7 (lst)
  (mapcar (lambda (x)
            (case x
              ((a) 10)
              ((b) 20)
              (t 99)))
          lst))

(defun test-map-lambda8 (lst)
  (mapcar (lambda (x)
            ((lambda (y) (+ x y)) 10))
          lst))

(defun test-map-lambda9 (lst)
  (let ((a 100))
    (mapcar (lambda (x)
              ((lambda (y) (+ x y a)) 10))
            lst)))

(defun test-map-lambda10 (lst)
  (mapcar (lambda (x)
            (let ((y x))
              (setq y (+ y 1))
              y))
          lst))

(defun test-map-lambda11 (lst)
  (mapcar (lambda (x)
            (progn
              (+ x 1)
              (+ x 2)
              (+ x 3)))
          lst))

(defun test-map-lambda12 (lst)
  (let ((k 5))
    (mapcar (lambda (x)
              (let ((k (+ k x)))
                (+ k 1)))
            lst)))

(defun run-all ()
  (list
   (test-map-lambda1 '(1 2 3))   ;; (2 3 4)
   (test-map-lambda2 '(1 2 3))   ;; (3 4 5)
   (test-map-lambda3 '(1 2 3))   ;; (11 12 13)
   (test-map-lambda4 '(1 2 3))   ;; (21 22 23)
   (test-map-lambda5 '(1 2 3))   ;; (12 13 14)
   (test-map-lambda6 '(0 1 2))   ;; (100 200 12)
   (test-map-lambda7 '(a b c))   ;; (10 20 99)
   (test-map-lambda8 '(1 2 3))   ;; (11 12 13)
   ;(test-map-lambda9 '(1 2 3))   ;; (111 112 113)
   (test-map-lambda10 '(1 2 3))  ;; (2 3 4)
   (test-map-lambda11 '(1 2 3))  ;; (4 5 6)
   (test-map-lambda12 '(1 2 3))  ;; (7 8 9)
   ))