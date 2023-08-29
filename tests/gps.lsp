;;; GPS(General problem Solver) PAIP

(defun gps (goal state ops)
    (if (every #'achieve goal state ops) 'solved))

(defun achieve (goal state ops)
    (cond ((null ops) t)
          ((member goal state) t)
          (t (achieve goal state (cdr ops)))))

(defun appropriate-p (goal op)
    (if (member goal (op-add-list op)) t nil))

(defun apply-op (op)
    (cond ((every #'achieve (op-preconds op))
           (print (list 'executing (op-acrion op)))
           (setf (dynamic *state*) (set-difference (dynamic *state*) (op-del-list op)))
           (setf (dynamic *state*) (union (dynamic *state*) (op-add-list op)))
           t)))

(defun some (f ls)
    (cond ((null ls) nil)
          ((funcall f (car ls)) t)
          (t (some f (cdr ls))) ))

(defun every (f :rest ls)
    (cond ((null ls) t)
          ((apply f ls) (every f (cdr ls)))
          (t nil)))

(defun find-all (x ls f)
    (cond ((null ls) nil)
          ((funcall f x (car ls)) (find-all x (cdr ls) f))
          (t (find-all x (cdr ls) f))))

(defun set-difference (x y)
    (append (set-difference1 x y)
            (set-difference1 y x)))

(defun set-difference1 (x y)
    (cond ((null x) nil)
          ((member (car x) y) (set-difference1 (cdr x) y))
          (t (cons (car x) (set-difference1 (cdr x) y)))))

(defun union (x y)
    (cond ((null x) nil)
          ((member (car x) y) (cons (car x) (union (cdr x) y)))
          (t (union (cdr x) y))))

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
    (gps '(son-at-home car-needs-batttery have-money have-phone-book)
         'son-at-school
         *school-ops*))

(import "test")
(defglobal *tests-op* (make-op 'drive-son-to-school
                               '(son-at-home car-works)
                               '(son-at-school)
                               '(son-at-home)))

($test (op-add-list *tests-op*) (son-at-school))
($test (op-del-list *tests-op*) (son-at-home))
($test (appropriate-p 'son-at-school *tests-op*) t)
($test (achieve 'son-at-home (op-precond *tests-op*)) t)