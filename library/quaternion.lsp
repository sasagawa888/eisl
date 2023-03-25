

(defun quaternionp (x)
  (instancep x (class <quaternion>)))

;;;  quaternion number
(defclass <quaternion> ()
  ((r :accessor r :initform 0 :initarg r)
   (i :accessor i :initform 0 :initarg i)
   (j :accessor j :initform 0 :initarg j)
   (k :accessor k :initform 0 :initarg k)))

;;; constructer
(defun quaternion (a b c d)
  (create (class <quaternion>) 'r a 'i b 'j c 'k d))    

;;; quaternion operator
(defun qadd (x y)
  (quaternion (+ (r x) (r y)) (+ (i x) (i y)) (+ (j x) (i y)) (+ (k x) (k y))))

(defun qsub (x y)
  (quaternion (- (r x) (r y)) (- (i x) (i y)) (- (j x) (i y)) (- (k x) (k y))))

(defun qabs (x)
   (sqrt (+ (r x) (i x) (j x) (k x))))

(defun qprint (x)
  (format (standard-output) "#[~A,~A,~A,~A]~%" (r x) (i x) (j x) (k x) ))

