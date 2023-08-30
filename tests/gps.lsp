;;; GPS(General problem Solver) PAIP

(defun gps (goal state)
    (cond ((achieve goal state) t)
          (t (gps goal (apply-op goal state)))))

(defun achieve (goal state)
    (if (member goal state) t nil))

(defun apply-op (goal state)
    (apply-op1 goal state *school-ops*))
    
(defun apply-op1 (goal state ops)
    (cond ((null ops) (error "cant apply"))
          ((member goal (op-add-list (car ops)))
           (print (op-action (car ops)))
           (union (set-difference state (op-del-list (car ops))) (op-add-list (car ops))))
          (t (apply-op1 goal state (cdr ops)))))
          
(defun union (x y)
    (cond ((null x) y)
          ((member (car x) y) (union (cdr x) y))
          (t (cons (car x) (union (cdr x) y)))))

(defun set-difference (x y)
    (append (set-difference1 x y)
            (set-difference1 y x)))

(defun set-difference1 (x y)
    (cond ((null x) nil)
          ((member (car x) y) (set-difference1 (cdr x) y))
          (t (cons (car x) (set-difference1 (cdr x) y)))))

(defun make-op (action precond add-list del-list)
    (list action precond add-list del-list))

(defun op-action (x) (elt x 0))

(defun op-precond (x) (elt x 1))

(defun op-add-list (x) (elt x 2))

(defun op-del-list (x) (elt x 3))

;;; test
(defglobal *school-ops*
    (list
        (make-op 'drive-son-to-school
                 '(son-at-home car-works)
                 '(son-at-school)
                 '(son-at-home))
        (make-op 'shop-installs-battery
                 '(car-needs-battery shop-knows-problem shop-has-money)
                 '(car-works)
                 nil)
        (make-op '(tell-shop-problem)
                 `(in-communication-with-shop)
                 '(shop-knows-problem)
                 nil)
        (make-op 'telephone-shop
                 '(know-phone-number)
                 '(in-comunication-with-shop)
                 nil)
        (make-op 'look-up-number
                 '(have-phone-book)
                 '(know-phone-number)
                 nil)
        (make-op 'give-shop-money
                 '(have-money)
                 '(shop-has-money)
                 '(have-mone))))

(defun test ()
    (gps 'son-at-school
         '(son-at-home car-needs-batttery have-money have-phone-book)))

(import "test")
(defglobal *tests-op* (make-op 'drive-son-to-school
                               '(son-at-home car-works)
                               '(son-at-school)
                               '(son-at-home)))

($test (op-add-list *tests-op*) (son-at-school))
($test (op-del-list *tests-op*) (son-at-home))
($test (achieve 'son-at-home (op-precond *tests-op*)) t)