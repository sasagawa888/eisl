;;; GPS(General problem Solver) PAIP

(defglobal *state* nil)
(defglobal *ops* nil)

(defclass <op> ()
  ((action :accessor op-action :initform nil :initarg action)
   (precond :accessor op-precond :initform nil :initarg precond)
   (add-list :accessor op-add-list :initform nil :initarg add-list)
   (del-list :accessor op-del-list :initform nil :initarg del-list)))

(defun make-op (x1 x2 x3 x4)
    (create (class <op>) 'action x1 'precond x2 'add-list x3 'del-list x4)) 

(defun gps (*state* goals *ops*)
    (if (every #'achieve goals) 'solved))

(defun achieve (goal)
    (or (member goal *state*)
        (some #'apply-op
              (find-all goal *ops* #'appropriate-p))))

(defun appropriate-p (goal op)
    (member goal (op-add-list op)))

(defun apply-op (op)
    (cond ((every #'achieve (op-preconds op))
           (print (list 'executing (op-acrion op)))
           (setf *state* (set-difference *state* (op-del-list op)))
           (setf *state* (union *state* (op-add-list op)))
           t)))

(defun some (f ls)
    (cond ((null ls) nil)
          ((funcall f (car ls)) t)
          (t (some f (cdr ls))) ))

(defun every (f ls)
    (cond ((null ls) t)
          ((funcall f (car ls)) (every f (cdr ls)))
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
    (gps '(son-at-home car-needs-batttery have-money have-phone-bool)
         '(son-at-school)
         *school-ops*))