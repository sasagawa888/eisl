;;;
;;; complex.l : ISLisp 用複素数
;;;
;;;             Copyright (C) 2021 Makoto Hiroi
;;;

;;; 複素数
(defclass <complex> ()
  ((re :accessor realpart :initform 0.0 :initarg re)
   (im :accessor imagpart :initform 0.0 :initarg im)))

;;; コンストラクタ
(defun complex (x y)
  (create (class <complex>) 're (convert x <float>) 'im (convert y <float>)))

;;; 表示
(defun cprint (z)
  (format (standard-output) "#C(~G ~G)~%" (realpart z) (imagpart z)))

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