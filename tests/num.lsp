;;;
;;; complex.l : ISLisp 用複素数
;;;
;;;             Copyright (C) 2021 Makoto Hiroi
;;;             add rational number by kenichi sasagawa

;;; 複素数
(defclass <complex> ()
  ((re :accessor realpart :initform 0.0 :initarg re)
   (im :accessor imagpart :initform 0.0 :initarg im)))

;;; コンストラクタ
(defun complex (x y)
  (create (class <complex>) 're (convert x <float>) 'im (convert y <float>)))

;;; rational number
(defclass <rational> ()
  ((nu :accessor numerator :initform 0 :initarg nu)
   (de :accessor denominator :initform 0 :initarg de)))

;;; constructer
(defun rational (x y)
  (create (class <rational>) 'nu (div x (gcd x y)) 'de (div y (gcd x y))))   

(defun complexp (x)
  (instancep x (class <complex>)))

(defun rationalp (x)
  (instancep x (class <rational>)))
  
(defun quaternion (x)
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


(defgeneric g+ (x y)
  (:method ((x <complex>) (y <complex>)) (cadd x y))
  (:method ((x <quaternion>) (y <quaternion>)) (qadd x y))
  (:method ((x <rational>) (y <rational>)) (radd x y))
  (:method (x y) (+ x y)))


;;; 表示
(defun cprint (z)
  (format (standard-output) "#C(~G ~G)~%" (realpart z) (imagpart z)))

(defun rprint (n)
  (format (standard-output) "~A/~A~%" (numerator n) (denominator n)))


;;; 複素共役
(defun conj (z)
  (complex (realpart z) (- (imagpart z))))

;;; 絶対値
(defun cabs (z)
  (cond
   ((= (realpart z) 0.0) (abs (imagpart z)))
   ((= (imagpart z) 0.0) (abs (realpart z)))
   ((> (abs (imagpart z)) (abs (realpart z)))
    (let ((temp (quotient (realpart z) (imagpart z))))
      (* (abs (imagpart z)) (sqrt (+ 1 (* temp temp))))))
   (t
    (let ((temp (quotient (imagpart z) (realpart z))))
      (* (abs (realpart z)) (sqrt (+ 1 (* temp temp))))))))

;;; 偏角
(defun carg (z) (atan2 (imagpart z) (realpart z)))

;;; 四則演算
(defun cadd (x y)
  (complex (+ (realpart x) (realpart y)) (+ (imagpart x) (imagpart y))))

(defun csub (x y)
  (complex (- (realpart x) (realpart y)) (- (imagpart x) (imagpart y))))

(defun cmul (x y)
  ;; (a + bi)(c + di) = ac + adi + bci - bd = (ac - bd) + (ad + bc)i
  (complex (- (* (realpart x) (realpart y)) (* (imagpart x) (imagpart y)))
           (+ (* (realpart x) (imagpart y)) (* (imagpart x) (realpart y)))))

(defun rmul (x y)
    (rational (* (numerator x) (numerator y))
              (* (denominator x) (denominator y))))


(defun cdiv (x y)
  (if (>= (abs (realpart y)) (abs (imagpart y)))
      (let* ((u (quotient (imagpart y) (realpart y)))
             (v (+ (realpart y) (* (imagpart y) u))))
        (complex (quotient (+ (realpart x) (* (imagpart x) u)) v)
                 (quotient (- (imagpart x) (* (realpart x) u)) v)))
    (let* ((u (quotient (realpart y) (imagpart y)))
           (v (+ (* (realpart y) u) (imagpart y))))
      (complex (quotient (+ (* (realpart x) u) (imagpart x)) v)
               (quotient (- (* (imagpart x) u) (realpart x)) v)))))

;;; 指数関数
(defun cexp (z)
  (let ((a (* (exp (realpart z)))))
    (complex (* (cos (imagpart z)) a) (* (sin (imagpart z)) a))))

;;; 対数関数
(defun clog (z) (complex (log (cabs z)) (carg z)))

;;; べき乗
(defun cpow (x y) (cexp (cmul y (clog x))))

;;; 三角関数
(defun csin (z)
  (let ((x (realpart z))
        (y (imagpart z)))
    (complex (* (sin x) (cosh y)) (* (cos x) (sinh y)))))

(defun ccos (z)
  (let ((x (realpart z))
        (y (imagpart z)))
    (complex (* (cos x) (cosh y)) (- (* (sin x) (sinh y))))))

(defun ctan (z)
  (let* ((x (realpart z))
         (y (imagpart z))
         (d (+ (cos (* 2 x)) (cosh (* 2 y)))))
    (complex (quotient (sin (* 2 x)) d) (quotient (sinh (* 2 y)) d))))

;;;双曲線関数
(defun csinh (z)
  (let ((x (realpart z))
        (y (imagpart z)))
    (complex (* (sinh x) (cos y)) (* (cosh x) (sin y)))))

(defun ccosh (z)
  (let ((x (realpart z))
        (y (imagpart z)))
    (complex (* (cosh x) (cos y)) (* (sinh x) (sin y)))))

(defun ctanh (z)
  (let* ((x (realpart z))
          (y (imagpart z))
         (d (+ (cosh (* 2 x)) (cos (* 2 y)))))
    (complex (quotient (sinh (* 2 x)) d) (quotient (sin (* 2 y)) d))))

;;; 平方根
(defun csqrt (z)
  (let* ((x (realpart z))
         (a (cabs z))
         (b (sqrt (quotient (- a x) 2))))
    (complex (sqrt (quotient (+ a x) 2))
             (if (>= (imagpart z) 0) b (- b)))))

;;; 逆三角関数 (atan と atan2 は ISLisp で定義されている)
(defun asin (x) (atan2 x (sqrt (- 1 (* x x)))))
(defun acos (x) (atan2 (sqrt (- 1 (* x x))) x))

;;; 定数
(defconstant iunit  (complex 0 1))
(defconstant iunit- (complex 0 -1))
(defconstant cone   (complex 1 0))
(defconstant ctwo   (complex 2 0))
(defconstant cpi2   (complex (quotient *pi* 2) 0))

;;; 複素数の逆三角関数 (定義式通り)
(defun casin (z)
  (let ((z1 (csqrt (cadd cone z)))
        (z2 (csqrt (csub cone z))))
    (cmul iunit- (clog (cadd (cmul iunit z) (cmul z1 z2))))))

(defun cacos (z) (csub cpi2 (casin z)))

(defun catan (z)
  (let ((z1 (cmul iunit z)))
    (cdiv (cmul iunit
                (csub (clog (csub cone z1)) (clog (cadd cone z1))))
          ctwo)))

;;; 逆双曲線関数 (atanh は ISLisp に定義されている)
(defun asinh (x) (atanh (quotient x (sqrt (+ 1 (* x x))))))

(defun acosh (x)
  (let ((a (sqrt (+ x 1.0)))
        (b (sqrt (- x 1.0))))
    (atanh (quotient (* a b) x))))
