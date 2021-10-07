;; written by M.Hiroi
;; 2 次元
(defclass <point> ()
  ((x :accessor point-x :initform 0.0 :initarg x)
   (y :accessor point-y :initform 0.0 :initarg y)))

;; 3 次元
(defclass <point3d> ()
  ((x :accessor point-x :initform 0.0 :initarg x)
   (y :accessor point-y :initform 0.0 :initarg y)
   (z :accessor point-z :initform 0.0 :initarg z)))

; メソッド
(defgeneric distance (p1 p2))

(defmethod distance ((p1 <point>) (p2 <point>))
  (let ((dx (- (point-x p1) (point-x p2)))
        (dy (- (point-y p1) (point-y p2))))
    (sqrt (+ (* dx dx) (* dy dy)))))

(defmethod distance ((p1 <point3d>) (p2 <point3d>))
  (let ((dx (- (point-x p1) (point-x p2)))
        (dy (- (point-y p1) (point-y p2)))
        (dz (- (point-z p1) (point-z p2))))
    (sqrt (+ (* dx dx) (* dy dy) (* dz dz)))))

;; テスト
(defun test ()
  (let ((p1 (create (class <point>)))
        (p2 (create (class <point>) 'x 10.0 'y 10.0))
        (p3 (create (class <point3d>)))
        (p4 (create (class <point3d>) 'x 100.0 'y 100.0 'z 100.0)))
    (format (standard-output) "~G~%" (distance p1 p2))
    (format (standard-output) "~G~%" (distance p3 p4))))


;;--------- original test code-----------------

(defgeneric plus (x y))

(defmethod plus ((x <integer>)(y <integer>))
    (+ x y))

(defmethod plus ((x <float>)(y <float>))
    (+ x y))


(defclass <grand> () ((slot3 :accessor slot3 :initarg s3)))
(defclass <parent> (<grand>) ((slot :accessor slot :initarg s)))
(defclass <brother> () ((slot1 :accessor slot1 :initarg s1)))
(defclass <child> (<parent> <brother>) ((slot2 :accessor slot2 :initarg s2)))
(defglobal *x* (create (class <child>) 's 'foo 's2 'bar 's3 'boo 's1 'uoo))



;;-------------- from M.Hiroi page-------------
;;; クラスの定義
(defclass foo-a () ())
(defclass foo-b () ())
(defclass foo-c (foo-a) ())
(defclass foo-d (foo-b foo-c) ())

;;; メソッドの定義
(defgeneric method-2 (x))
(defmethod method-2 ((x foo-a)) (print "foo-a method"))
(defmethod method-2 ((x foo-c)) (print "foo-c method"))

;;; メソッドの定義
(defgeneric method-3 (x))
(defmethod method-3 ((x foo-a))
  (print "foo-a method"))
(defmethod method-3 ((x foo-b))
  (print "foo-b method") (call-next-method))
(defmethod method-3 ((x foo-c))
 (print "foo-c method") (call-next-method))
(defmethod method-3 ((x foo-d))
 (print "foo-d method") (call-next-method))


(defglobal a (create (class foo-a)))
(defglobal b (create (class foo-b)))
(defglobal c (create (class foo-c)))
(defglobal d (create (class foo-d)))
