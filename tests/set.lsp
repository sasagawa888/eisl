;;; set
(defclass <set> ()
  ((elt :accessor element :initform 0.0 :initarg elt)))

;;; instance
(defun set (x)
  (create (class <set>) 'elt x))
  
(defglobal a (set '(1 2 3)))

(defglobal b (set (lambda (x) (and (integerp x) (>= x 1) (<= x 3)))))


;;; definition1
(defun set-equal (x y)
    (let ((x1 (element x)) (y1 (element y)))
        (cond ((and (listp x1)(listp y1)) (and (subsetp x1 y1)(subsetp y1 x1)))
              ((and (listp x1)(functionp y1)) (everyp y1 x1))
              ((and (functionp x1)(listp y1)) (everyp x1 y1))
              (t nil)))) 

(defun subsetp (x y)
    (cond ((null x) t)
          ((member (car x) y) (subsetp (cdr x) y))
          (t nil)))

(defun everyp (f x)
    (cond ((null x) t)
          ((funcall f (car x)) (everyp f (cdr x)))
          (t nil)))

;; axiom1
#|
What is formula in Lisp? function?
If formula is same to function in lisp, lisp has  epitaxial axiom.
e.g. 
(defun f (x) (+ x 1)) -> f(1)=f(1)
|#

