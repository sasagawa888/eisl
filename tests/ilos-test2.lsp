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
  (print "foo-b method"))
(defmethod method-3 ((x foo-c))
 (print "foo-c method") (call-next-method))
(defmethod method-3 ((x foo-d))
 (print "foo-d method") )


(defglobal a (create (class foo-a)))
(defglobal b (create (class foo-b)))
(defglobal c (create (class foo-c)))
(defglobal d (create (class foo-d)))

;;;
;;; vlvec.lsp : ISLisp 用可変長ベクタとヒープ
;;;
;;;             Copyright (C) 2021 Makoto Hiroi
;;;

;;; テスト用
;(defun print (x) (format (standard-output) "~A~%" x))

;;; クラス定義
(defclass <vlvec> ()
  ((buffer :accessor vlvec-buffer :initform nil :initarg buffer)
   (size   :accessor vlvec-size   :initform 8   :initarg size)
   (fillp  :accessor vlvec-fillp  :initform 0   :initarg fillp)))

(defmethod initialize-object :after ((v <vlvec>) xs)
  (if (null (vlvec-buffer v))
      (setf (vlvec-buffer v) (create-vector (vlvec-size v)))))

;;; メソッドの定義
(defgeneric vlvec-ref (v i))
(defgeneric vlvec-set (v i x))
(defgeneric vlvec-push (v x))
(defgeneric vlvec-pop (v))
(defgeneric vlvec-swap (v i j))
(defgeneric vlvec-length (v))
(defgeneric vlvec-clear  (v))
(defgeneric vlvec-emptyp (v))
(defgeneric vlvec-fold  (v f a))
(defgeneric vlvec-foldr (v f a))
(defgeneric vlvec->list   (v))
(defgeneric list->vlvec (xs))
(defgeneric vlvec->vector (v))
(defgeneric vector->vlvec (vec))
(defgeneric vlvec-for-each (v f))
(defgeneric vlvec-for-each-back (v f))

;;; 参照
(defmethod vlvec-ref ((v <vlvec>) (i <integer>))
  (if (and (<= 0 i) (< i (vlvec-fillp v)))
      (aref (vlvec-buffer v) i)
    (error "vlvec-ref: index out of range")))

;;; 更新
(defmethod vlvec-set ((v <vlvec>) (i <integer>) item)
  (if (and (<= 0 i) (< i (vlvec-fillp v)))
      (setf (aref (vlvec-buffer v) i) item)
    (error "vlvec-set: index out of range")))

;;; バッファの拡張
(defun extend-buffer (v)
  (let ((src (vlvec-buffer v))
	(dst (create-vector (* (vlvec-size v) 2))))
    (for ((i 0 (+ i 1)))
	 ((= i (vlvec-size v)))
	 (setf (aref dst i) (aref src i)))
    (setf (vlvec-buffer v) dst)
    (setf (vlvec-size v) (* (vlvec-size v) 2))))

;;; 追加
(defmethod vlvec-push ((v <vlvec>) item)
  (if (<= (vlvec-size v) (vlvec-fillp v))
      (extend-buffer v))
  (setf (aref (vlvec-buffer v) (vlvec-fillp v)) item)
  (setf (vlvec-fillp v) (+ (vlvec-fillp v) 1))
  item)

;;; 取り出し
(defmethod vlvec-pop ((v <vlvec>))
  (cond
   ((< 0 (vlvec-fillp v))
    (setf (vlvec-fillp v) (- (vlvec-fillp v) 1))
    (aref (vlvec-buffer v) (vlvec-fillp v)))
   (t
    (error "vlvec-pop: empty vlvec"))))

;;; 要素の交換
(defmethod vlvec-swap ((v <vlvec>) (i <integer>) (j <integer>))
  (if (or (< i 0) (>= i (vlvec-fillp v))
	  (< j 0) (>= j (vlvec-fillp v)))
      (error "vlvec-swap: index out of range")
    (let* ((buff (vlvec-buffer v))
	   (item (aref buff i)))
      (setf (aref buff i) (aref buff j))
      (setf (aref buff j) item))))

;;; 要素の個数
(defmethod vlvec-length ((v <vlvec>)) (vlvec-fillp v))

;;; クリア
(defmethod vlvec-clear ((v <vlvec>)) (setf (vlvec-fillp v) 0))

;;; 空か
(defmethod vlvec-emptyp ((v <vlvec>)) (= (vlvec-fillp v) 0))

;;; 畳み込み
(defmethod vlvec-fold ((v <vlvec>) f init)
  (for ((i 0 (+ i 1))
	(a init (funcall f a (aref (vlvec-buffer v) i))))
       ((= i (vlvec-fillp v)) a)))

(defmethod vlvec-foldr ((v <vlvec>) f init)
  (for ((i (- (vlvec-fillp v) 1) (- i 1))
	(a init (funcall f (aref (vlvec-buffer v) i) a)))
       ((< i 0) a)))

;;; 巡回
(defmethod vlvec-for-each ((v <vlvec>) f)
  (for ((i 0 (+ i 1)))
       ((= i (vlvec-fillp v)))
       (funcall f (aref (vlvec-buffer v) i))))

(defmethod vlvec-for-each-back ((v <vlvec>) f)
  (for ((i (- (vlvec-fillp v) 1) (- i 1)))
       ((< i 0))
       (funcall f (aref (vlvec-buffer v) i))))

;;; 変換
(defmethod vlvec->list ((v <vlvec>)) (vlvec-foldr v #'cons nil))

(defmethod list->vlvec ((xs <list>))
  (for ((v (create (class <vlvec>)))
	(xs xs (cdr xs)))
       ((null xs) v)
       (vlvec-push v (car xs))))

(defmethod vlvec->vector ((v <vlvec>))
  (subseq (vlvec-buffer v) 0 (vlvec-size v)))

(defmethod vector->vlvec ((vec <general-vector>))
  (let ((len (length vec)))
    (create (class <vlvec>) 'buffer (subseq vec 0 len) 'size len 'fillp len)))

;;;
;;; ヒープ
;;;

;;; 比較関数
(defgeneric compare (x y))

;;; 数値用
(defmethod compare ((x <number>) (y <number>))
  (cond ((= x y) 0)
	((< x y) -1)
	(t 1)))

;;; クラス定義
(defclass <heap> ()
  ((buffer :accessor heap-buffer :initform (create (class <vlvec>)))))

;;; 操作関数

;;; ヒープの構築
(defun upheap (buff n)
  (for ((n n p)
	(p (div (- n 1) 2) (div (- p 1) 2)))
       ((or (< p 0)
	    (<= (compare (vlvec-ref buff p) (vlvec-ref buff n)) 0)))
       (vlvec-swap buff p n)))

; ヒープの再構築
(defun downheap (buff n nums)
  (for ((n n c)
	(c (+ (* n 2) 1) (+ (* c 2) 1)))
       ((>= c nums))
       (if (and (< (+ c 1) nums)
		(> (compare (vlvec-ref buff c) (vlvec-ref buff (+ c 1))) 0))
	   (setq c (+ c 1)))
       (if (> (compare (vlvec-ref buff n) (vlvec-ref buff c)) 0)
	   (vlvec-swap buff n c))))

;;; メソッドの定義
(defgeneric heap-emptyp (h))
(defgeneric heap-length (h))
(defgeneric heap-clear (h))
(defgeneric heap-push (h x))
(defgeneric heap-pop (h))
(defgeneric heap-peek (h))

;;; 空か
(defmethod heap-emptyp ((h <heap>))
  (vlvec-emptyp (heap-buffer h)))

;;; 要素数
(defmethod heap-length ((h <heap>))
  (vlvec-length (heap-buffer h)))

;;; クリア
(defmethod heap-clear ((h <heap>))
  (vlvec-clear (heap-buffer h)))

;;; データの追加
(defmethod heap-push ((h <heap>) x)
  (vlvec-push (heap-buffer h) x)
  (upheap (heap-buffer h) (- (heap-length h) 1)))

;;; 先頭データの参照
(defmethod heap-peek ((h <heap>))
  (if (heap-emptyp h)
      (error "heep-peek : heap is empty")
    (vlvec-ref (heap-buffer h) 0)))

;;; データの取り出し
(defmethod heap-pop ((h <heap>))
  (let* ((x (heap-peek h))
	 (b (heap-buffer h))
	 (z (vlvec-pop b)))
    (cond
     ((not (vlvec-emptyp b))
      (vlvec-set b 0 z)
      (downheap b 0 (vlvec-length b))))
    x))

#|
bikkuri common lisp 
from masahito kurihara's book
|#


(defglobal *new-id* 0)

(defun new-id () (setq *new-id* (+ *new-id* 1)))

(defclass !object ()
    ((id :accessor id! :initform *new-id*)))

(defclass !atom (!object) ())
(defclass !list (!object) ())
(defclass !number (!atom)
    ((number :accessor number! :initarg number)))
(defclass !string (!atom)
    ((string :accessor string! :initarg string)))

(defun eq! (!x !y) (= (id! !x) (id! !y)))

(defgeneric !cl (x))
(defmethod !cl ((num <integer>))
    (create (class !number) 'number num))
(defmethod !cl ((str <string>))
    (create (class !string) 'string str))

(defgeneric cl! (x))
(defmethod cl! ((!num !number))
    (number! !num))
(defmethod cl! ((!str !string))
    (string! !str))

(defun !lisp ()
    (for ()
         (nil t)
         (print-prompt)
         (!print! (!eval!(!read!)))))

(defun print-prompt () (format (standard-output) "%!CL>"))

(defun !read! () (!cl (read)))

(defun !print! (!obj)
    (print (cl! !obj)))

(defgeneric !eval! (x))
(defmethod !eval! ((!obj !object)) !obj)
(defmethod !eval! ((!obj !number)) !Obj)
(defmethod !eval! ((!obj !string)) !obj)

;------- from M Hiroi --------
; ILOS compile test
;;; クラス定義
(defclass foo1 () ())
(defclass foo2 (foo1) ())
(defclass foo3 (foo2) ())

(defglobal x1 (create (class foo1)))
(defglobal x2 (create (class foo2)))
(defglobal x3 (create (class foo3)))

(defgeneric bar (x))
;;; 基本メソッド
(defmethod bar ((x foo1)) (format (standard-output) "foo1 bar~%"))
(defmethod bar ((x foo2)) (format (standard-output) "foo2 bar~%") (call-next-method))
(defmethod bar ((x foo3)) (format (standard-output) "foo3 bar~%") (call-next-method))

;;; :after メソッド
(defmethod bar :after ((x foo1)) (format (standard-output) "foo1 bar after~%"))
(defmethod bar :after ((x foo2)) (format (standard-output) "foo2 bar after~%"))
(defmethod bar :after ((x foo3)) (format (standard-output) "foo3 bar after~%"))

;;; :before メソッド
(defmethod bar :before ((x foo1)) (format (standard-output) "foo1 bar before~%"))
(defmethod bar :before ((x foo2)) (format (standard-output) "foo2 bar before~%"))
(defmethod bar :before ((x foo3)) (format (standard-output) "foo3 bar before~%"))
