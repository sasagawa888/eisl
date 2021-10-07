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
