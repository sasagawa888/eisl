;; study ILOS

;; complex-number
(defclass <complex> ()
  ((r :accessor real-part :initform 0.0 :initarg r)
   (i :accessor imag-part :initform 0.0 :initarg i)))

;; ratinal-number
(defclass <rational> ()
  ((n :accessor numerator :initform 0.0 :initarg n)
   (d :accessor denominator :initform 0.0 :initarg d)))

(defun make-rectangler (r i)
  (create (class <complex>) 'r r 'i i))

(defun make-rational (n d)
  (create (class <rational>) `n n `d d))

(defgeneric display (x))

(defmethod display ((x <complex>))
  (if (>= (imag-part x) 0)
      (format (standard-output) "~A+~Ai~%" (real-part x) (imag-part x))
      (format (standard-output) "~A~Ai~%" (real-part x) (imag-part x))))

(defmethod display ((x <rational>))
      (format (standard-output) "~A/~A~%" (numerator x) (denominator x)))

;;; generic-function 
(defgeneric ++ (x y))

(defmethod ++ ((x <complex>) (y <complex>))
  (let ((r (+ (real-part x) (real-part y)))
        (i (+ (imag-part x) (imag-part y))))
    (create (class <complex>) 'r r 'i i)))

(defmethod ++ ((x <rational>) (y <rational>))
  (let* ((d (lcm (denominator x) (denominator y)))
         (n1 (* (numerator x) (div d (denominator x))))
         (n2 (* (numerator y) (div d (denominator y))))
         (n3 (+ n1 n2))
         (d1 (div d (gcd n3 d)))
         (n4 (div n3 (gcd n3 d))))
    (create (class <rational>) 'n n4 'd d1)))
        
      

;;; test
(defun test ()
  (let ((c1 (make-rectangler 3 -4))
        (c2 (make-rectangler 5 -6))
        (r1 (make-rational 3 4))
        (r2 (make-rational 5 8)))
     (display (++ c1 c2))
     (display (++ r1 r2))))
    
