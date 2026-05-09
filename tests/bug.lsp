
;; ILOS stress tests for Easy-ISLisp

(defclass <stress-point> ()
  ((x :accessor point-x :initarg x)
   (y :accessor point-y :initarg y)))

(defclass <stress-color-point> (<stress-point>)
  ((color :accessor point-color :initarg color)))

(defclass <stress-3d-point> (<stress-point>)
  ((z :accessor point-z :initarg z)))

(defgeneric stress-sum (obj))
(defgeneric stress-move (obj dx dy))
(defgeneric stress-describe (obj))
(defgeneric stress-scale (obj n))


(defmethod stress-move ((p <stress-point>) dx dy)
  (setf (point-x p) (+ (point-x p) dx))
  (setf (point-y p) (+ (point-y p) dy))
  p)


(defun stress-ilos8 ()
  (let ((p (create (class <stress-color-point>)
                   'x 10 'y 20 'color 'green)))
    (stress-move p 5 6)
    (list (point-x p) (point-y p) (point-color p))))
;; => (15 26 GREEN)
