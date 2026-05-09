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


;; ------------------------------------------------------------
;; 1. basic slot access
;; ------------------------------------------------------------

(defmethod stress-sum ((p <stress-point>))
  (+ (point-x p) (point-y p)))

(defun stress-ilos1 ()
  (let ((p (create (class <stress-point>) 'x 10 'y 20)))
    (stress-sum p)))
;; => 30


;; ------------------------------------------------------------
;; 2. inherited slot access
;; ------------------------------------------------------------

(defun stress-ilos2 ()
  (let ((p (create (class <stress-color-point>)
                   'x 10 'y 20 'color 'red)))
    (list (point-x p)
          (point-y p)
          (point-color p))))
;; => (10 20 RED)


;; ------------------------------------------------------------
;; 3. method dispatch by subclass
;; ------------------------------------------------------------

(defmethod stress-describe ((p <stress-point>))
  (list 'point (point-x p) (point-y p)))

(defmethod stress-describe ((p <stress-color-point>))
  (list 'color-point (point-x p) (point-y p) (point-color p)))

(defun stress-ilos3 ()
  (let ((p1 (create (class <stress-point>) 'x 1 'y 2))
        (p2 (create (class <stress-color-point>) 'x 3 'y 4 'color 'blue)))
    (list (stress-describe p1)
          (stress-describe p2))))
;; => ((POINT 1 2) (COLOR-POINT 3 4 BLUE))


;; ------------------------------------------------------------
;; 4. mutation through method
;; ------------------------------------------------------------

(defmethod stress-move ((p <stress-point>) dx dy)
  (setf (point-x p) (+ (point-x p) dx))
  (setf (point-y p) (+ (point-y p) dy))
  p)

(defun stress-ilos4 ()
  (let ((p (create (class <stress-point>) 'x 10 'y 20)))
    (stress-move p 3 4)
    (list (point-x p) (point-y p))))
;; => (13 24)


;; ------------------------------------------------------------
;; 5. mapcar + lambda + object mutation
;; ------------------------------------------------------------

(defun stress-ilos5 ()
  (let ((p (create (class <stress-point>) 'x 0 'y 0)))
    (mapcar
     (lambda (n)
       (stress-move p n (* n 2)))
     '(1 2 3 4))
    (list (point-x p) (point-y p))))
;; => (10 20)


;; ------------------------------------------------------------
;; 6. lexical variable shadowing vs accessor name-like variable
;; ------------------------------------------------------------
;; limitation of compiler
(defun stress-ilos6 ()
  (let ((p (create (class <stress-point>) 'x 5 'y 7)))
    (let ((point-x1 100)
          (point-y1 200))
      (+ point-x1 point-y1 (point-x p) (point-y p)))))
;; => 312


;; ------------------------------------------------------------
;; 7. lambda captures object
;; ------------------------------------------------------------

(defun stress-ilos7 ()
  (let ((p (create (class <stress-point>) 'x 1 'y 1)))
    ((lambda (f)
       (funcall f 10 20)
       (list (point-x p) (point-y p)))
     (lambda (dx dy)
       (stress-move p dx dy)))))
;; => (11 21)


;; ------------------------------------------------------------
;; 8. inherited method works for subclass
;; ------------------------------------------------------------

(defun stress-ilos8 ()
  (let ((p (create (class <stress-color-point>)
                   'x 10 'y 20 'color 'green)))
    (stress-move p 5 6)
    (list (point-x p) (point-y p) (point-color p))))
;; => (15 26 GREEN)


;; ------------------------------------------------------------
;; 9. subclass-specific method with inherited slots
;; ------------------------------------------------------------

(defmethod stress-scale ((p <stress-point>) n)
  (setf (point-x p) (* (point-x p) n))
  (setf (point-y p) (* (point-y p) n))
  p)

(defmethod stress-scale ((p <stress-3d-point>) n)
  (setf (point-x p) (* (point-x p) n))
  (setf (point-y p) (* (point-y p) n))
  (setf (point-z p) (* (point-z p) n))
  p)

(defun stress-ilos9 ()
  (let ((p (create (class <stress-3d-point>) 'x 2 'y 3 'z 4)))
    (stress-scale p 10)
    (list (point-x p) (point-y p) (point-z p))))
;; => (20 30 40)


;; ------------------------------------------------------------
;; 10. recursive method
;; ------------------------------------------------------------

(defgeneric stress-power-x (obj n))

(defmethod stress-power-x ((p <stress-point>) n)
  (if (= n 0)
      1
      (* (point-x p) (stress-power-x p (- n 1)))))

(defun stress-ilos10 ()
  (let ((p (create (class <stress-point>) 'x 2 'y 0)))
    (stress-power-x p 10)))
;; => 1024


;; ------------------------------------------------------------
;; 11. nested lambda + method call + shadowing
;; ------------------------------------------------------------

(defun stress-ilos11 ()
  (let ((p (create (class <stress-point>) 'x 10 'y 20)))
    ((lambda (x)
       ((lambda (x)
          (+ x (stress-sum p)))
        100))
     1000)))
;; => 130


;; ------------------------------------------------------------
;; 12. object list + dynamic dispatch
;; ------------------------------------------------------------

(defun stress-ilos12 ()
  (let ((lst (list
              (create (class <stress-point>) 'x 1 'y 2)
              (create (class <stress-color-point>) 'x 3 'y 4 'color 'red)
              (create (class <stress-3d-point>) 'x 5 'y 6 'z 7))))
    (mapcar
     (lambda (obj)
       (stress-describe obj))
     lst)))
;; expected:
;; ((POINT 1 2)
;;  (COLOR-POINT 3 4 RED)
;;  (POINT 5 6))
;;
;; stress-3d-point has no special stress-describe method,
;; so inherited <stress-point> method should be used.
(defgeneric stress-number-method (x))

(defmethod stress-number-method ((x <integer>))
  (+ x 1))

(defun stress-ilos13 ()
  (stress-number-method 10))
;; => 11

;; ------------------------------------------------------------
;; runner
;; ------------------------------------------------------------

(defun run-all ()
  (list
   (stress-ilos1)
   (stress-ilos2)
   (stress-ilos3)
   (stress-ilos4)
   (stress-ilos5)
   (stress-ilos6)
   (stress-ilos7)
   (stress-ilos8)
   (stress-ilos9)
   (stress-ilos10)
   (stress-ilos11)
   (stress-ilos12)))
   
