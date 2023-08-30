;;; GPS(General problem Solver) PAIP

(defun gps (goal state)
    (cond ((achieve goal state) state)
          (t (gps goal (apply-op goal state)))))

(defun gps-all (goals state)
    (if (null goals)
        state
        (let ((result (gps (car goals) state)))
            (if (not (eq result 'false))
                (gps-all (cdr goals) result)
                result))))


(defun achieve (goal state)
    (if (member goal state) t nil))

(defun apply-op (goal state)
    (apply-op1 goal state *school-ops*))
    
(defun apply-op1 (goal state ops)
    (cond ((null ops) 'false)
          ((not (eq (appropriate-p goal state (car ops)) 'false))
           (format (standard-output) "executing ~A~%" (op-action (car ops)))
           (union (set-difference state (op-del-list (car ops))) (op-add-list (car ops))))
          (t (apply-op1 goal state (cdr ops)))))

(defun appropriate-p (goal state op)
    (if (member goal (op-add-list op))
        (if (subsetp state (op-precond op))
            state
            (gps-all (op-precond op) state))
        'false))
          
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

(defun subsetp (x y)
    (cond ((null x) t)
          ((member (car x) y) (subsetp (cdr x) y))
          (t nil)))

(defun make-op (action precond add-list del-list)
    (list action precond add-list del-list t))

(defun op-action (x) (elt x 0))

(defun op-precond (x) (elt x 1))

(defun op-add-list (x) (elt x 2))

(defun op-del-list (x) (elt x 3))

(defun newp (x) (elt x 4))

(defun used (x) (set-elt nil x 4))

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
        (make-op 'tell-shop-problem
                 `(in-communication-with-shop)
                 '(shop-knows-problem)
                 nil)
        (make-op 'telephone-shop
                 '(know-phone-number)
                 '(in-communication-with-shop)
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
         '(son-at-home car-needs-battery have-money have-phone-book)))

(import "test")
(defglobal *tests-op* (make-op 'drive-son-to-school
                               '(son-at-home car-works)
                               '(son-at-school)
                               '(son-at-home)))

($test (op-add-list *tests-op*) (son-at-school))
($test (op-del-list *tests-op*) (son-at-home))
($test (achieve 'son-at-home (op-precond *tests-op*)) t)