

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

;;xy=　(x0y0−x1y1−x2y2−x3y3)+(x0y1+x1y0+x2y3−x3y2)i　+(x0y2−x1y3+x2y0+x3y1)j+(x0y3+x1y2−x2y1+x3y0)k 

(defun qmult (x y)
  (let* ((x0 (r x)) (x1 (i x)) (x2 (j x)) (x3 (k x))
         (y0 (r y)) (y1 (i y)) (y2 (j y)) (y3 (k y))
         (z0 (+ (* x0 y0) (- (* x1 y1)) (- (* x2 y2)) (- (* x3 y3))))
         (z1 (+ (* x0 y1) (* x1 y0) (* x2 y3) (- (* x3 y2))))
         (z2 (+ (* x0 y2) (- (* x1 y3)) (* x2 y0) (* x3 y1)))
         (z3 (+ (* x0 y3) (* x1 y2) (- (* x2 y1)) (* x3 y0))))
      (quaternion z0 z1 z2 z3)))

(defun qdiv (x y)
   (let ((c (quotient 1 (+ (r x) (i x) (j x) (k x)))))
      (qmult (quaternion c 0 0 0) (qmult x (conjugate x)))))
      

(defun qabs (x)
   (sqrt (+ (r x) (i x) (j x) (k x))))

(defun qprint (x)
  (format (standard-output) "#q(~A,~A,~A,~A)~%" (r x) (i x) (j x) (k x) ))

(defun conjugate (x)
  (let ((x0 (r x)) (x1 (i x)) (x2 (j x)) (x3 (k x)))
      (quaternion x0 (- x1) (- x2) (- x3))))

(defun inverse (x)
    (let ((c (quotient 1 (+ (r x) (i x) (j x) (k x)))))
        (qmult (quaternion c 0 0 0) (conjugate x))))

(defun qeqlp (x y)
  (and (= (r x) (r y)) (= (i x) (i y)) (= (j x) (j y)) (= (k x) (k y))))