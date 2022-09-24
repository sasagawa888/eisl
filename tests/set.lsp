;;; set
(defclass <set> ()
  ((elt :accessor element :initform 0.0 :initarg elt)))

;;; instance
(defun set (x)
  (create (class <set>) 'elt x))
  
(defglobal a (set '(1 2 3)))

(defglobal b (set (lambda (x) (and (integerp x) (>= x 1) (<= x 3)))))