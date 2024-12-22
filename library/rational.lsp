;;;
;;; rational.lsp : 有理数 (ISLisp 用)
;;;
;;; Copyright (c) 2024 Makoto Hiroi
;;;
;;; Released under the MIT license
;;; https://opensource.org/license/mit/
;;;

;;; メソッドの宣言
(defgeneric +/ (x y))
(defgeneric -/ (x y))
(defgeneric */ (x y))
(defgeneric // (x y))
(defgeneric inv (x))
(defgeneric =/ (x y))
(defgeneric /=/ (x y))
(defgeneric </ (x y))
(defgeneric <=/ (x y))
(defgeneric >/ (x y))
(defgeneric >=/ (x y))
(defgeneric is-integer (x))
(defgeneric to-integer (x))
(defgeneric to-float (x))
(defgeneric to-string (x))
(defgeneric display/ (x))
(defgeneric repeat-decimal (x))
(defgeneric from-repeat-decimal (x y))

;;; 有理数
(defclass <rational> ()
  ((num :accessor numerator   :initform 0 :initarg num)
   (den :accessor denominator :initform 1 :initarg den)))

;;; コンストラクタ
(defun make-ratio (a b)
  (if (= b 0)
      (error "divizion by zero"))
  (let ((f (if (< b 0) -1 1))
        (z (gcd (abs a) (abs b))))
    (create (class <rational>) 'num (div (* f a) z) 'den (div (* f b) z))))

;;; 型述語
(defun rationalp (x)
  (eq (class-of x) (class <rational>)))

;;; 算術演算子
(defmethod +/ ((x <rational>) (y <rational>))
  (let ((x1 (numerator x)) (x2 (denominator x))
        (y1 (numerator y)) (y2 (denominator y)))
    (make-ratio (+ (* x1 y2) (* x2 y1)) (* x2 y2))))

(defmethod +/ ((x <rational>) (y <integer>))
  (let ((x1 (numerator x)) (x2 (denominator x)))
    (make-ratio (+ x1 (* x2 y)) x2)))

(defmethod +/ ((x <integer>) (y <rational>))
  (let ((y1 (numerator y)) (y2 (denominator y)))
    (make-ratio (+ (* x y2) y1) y2)))

(defmethod +/ ((x <integer>) (y <integer>))
  (make-ratio (+ x y) 1))

(defmethod -/ ((x <rational>) (y <rational>))
  (let ((x1 (numerator x)) (x2 (denominator x))
        (y1 (numerator y)) (y2 (denominator y)))
    (make-ratio (- (* x1 y2) (* x2 y1)) (* x2 y2))))

(defmethod -/ ((x <rational>) (y <integer>))
  (let ((x1 (numerator x)) (x2 (denominator x)))
    (make-ratio (- x1 (* x2 y)) x2)))

(defmethod -/ ((x <integer>) (y <rational>))
  (let ((y1 (numerator y)) (y2 (denominator y)))
    (make-ratio (- (* x y2) y1) y2)))

(defmethod -/ ((x <integer>) (y <integer>))
 (make-ratio (- x y) 1))

(defmethod */ ((x <rational>) (y <rational>))
  (let ((x1 (numerator x)) (x2 (denominator x))
        (y1 (numerator y)) (y2 (denominator y)))
    (make-ratio (* x1 y1) (* x2 y2))))

(defmethod */ ((x <rational>) (y <integer>))
  (let ((x1 (numerator x)) (x2 (denominator x)))
    (make-ratio (* x1 y) x2)))

(defmethod */ ((x <integer>) (y <rational>))
  (let ((y1 (numerator y)) (y2 (denominator y)))
    (make-ratio (* x y1) y2)))

(defmethod */ ((x <integer>) (y <integer>))
  (make-ratio (* x y) 1))

(defmethod // ((x <rational>) (y <rational>))
  (let ((x1 (numerator x)) (x2 (denominator x))
        (y1 (numerator y)) (y2 (denominator y)))
    (make-ratio (* x1 y2) (* x2 y1))))

(defmethod // ((x <rational>) (y <integer>))
  (let ((x1 (numerator x)) (x2 (denominator x)))
    (make-ratio x1 (* x2 y))))

(defmethod // ((x <integer>) (y <rational>))
  (let ((y1 (numerator y)) (y2 (denominator y)))
    (make-ratio (* x y2) y1)))

(defmethod // ((x <integer>) (y <integer>))
  (make-ratio x y))

;;; 逆数
(defmethod inv ((x <integer>)) (make-ratio 1 x))

(defmethod inv ((x <rational>))
  (make-ratio (denominator x) (numerator x)))

;;; 有理数の比較
(defun compare-ratio (x y)
  (let ((x1 (numerator x)) (x2 (denominator x))
        (y1 (numerator y)) (y2 (denominator y)))
    (- (* x1 y2) (* x2 y1))))

;;; 比較演算子の定義
(defmethod =/ ((x <rational>) (y <rational>))
  (= (compare-ratio x y) 0))

(defmethod /=/ ((x <rational>) (y <rational>))
  (not (= (compare-ratio x y) 0)))

(defmethod </ ((x <rational>) (y <rational>))
  (< (compare-ratio x y) 0))

(defmethod >/ ((x <rational>) (y <rational>))
  (> (compare-ratio x y) 0))

(defmethod <=/ ((x <rational>) (y <rational>))
  (<= (compare-ratio x y) 0))

(defmethod >=/ ((x <rational>) (y <rational>))
  (>= (compare-ratio x y) 0))

;;; 整数の判定
(defmethod is-integer ((x <rational>))
  (= (denominator x) 1))

;;; 整数に変換
(defmethod to-integer ((x <rational>))
  (div (numerator x) (denominator x)))

;;; 浮動小数点数に変換
(defmethod to-float ((x <rational>))
  (quotient (numerator x) (denominator x)))

;;; 文字列に変換
(defmethod to-string ((x <rational>))
  (string-append (convert (numerator x) <string>) "/" (convert (denominator x) <string>)))

;;; 表示
(defmethod display/ ((x <rational>))
  (format (standard-output) "~D/~D" (numerator x) (denominator x)))

;;; 検索
(defun find-index (x xs i)
  (cond
   ((null xs) -1)
   ((eql x (car xs)) i)
   (t
    (find-index x (cdr xs) (+ i 1)))))

;;; 循環小数 m/n = ((...) (...))
(defmethod repeat-decimal ((x <rational>))
  (let ((m (numerator x))
        (n (denominator x))
        (xs nil) (ys nil) (zs nil))
    (while (not zs)
      (let ((p (div m n))
            (q (mod m n)))
        (setq ys (cons p ys))
        (cond
         ((= q 0)
          (setq zs (list (reverse ys) '(0))))
         (t
          (let ((i (find-index q xs 0)))
            (cond
             ((>= i 0)
              (setq zs (list (reverse (subseq ys (+ i 1) (length ys)))
                             (reverse (subseq ys 0 (+ i 1))))))
             (t
              (setq xs (cons q xs))
              (setq m (* q 10)))))))))
    zs))

;;; 循環小数を分数に直す
(defun digit-to-number (xs a)
  (if (null xs)
      a
    (digit-to-number (cdr xs) (+ (* a 10) (car xs)))))

(defmethod from-repeat-decimal ((xs <list>) (ys <list>))
  (let ((p0 (digit-to-number xs 0))
        (q0 (expt 10 (- (length xs) 1)))
        (p1 (digit-to-number ys 0))
        (q1 (- (expt 10 (length ys)) 1)))
    (// (+ (* q1 p0) p1) (* q0 q1))))