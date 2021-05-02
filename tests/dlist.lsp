;;;
;;; dlist.lsp : ISLisp 用双方向リスト
;;;
;;;             Copyright (C) 2021 Makoto Hiroi
;;;

;;; メソッドの宣言
(defgeneric dlist-ref (d n))
(defgeneric dlist-set (d n value))
(defgeneric dlist-insert (d n value))
(defgeneric dlist-delete (d n))
(defgeneric dlist-fold (d func init))
(defgeneric dlist-foldr (d func init))
(defgeneric dlist-length (d))
(defgeneric dlist-clear (d))
(defgeneric dlist-emptyp (d))
(defgeneric list->dlist (ls))
(defgeneric dlist->list (d))
(defgeneric dlist-for-each (d func))
(defgeneric dlist-for-each-back (d func))

;;; セルの定義
(defclass <cell> ()
  ((item :accessor cell-item :initform nil :initarg item)
   (prev :accessor cell-prev :initform nil :initarg prev)
   (next :accessor cell-next :initform nil :initarg next)))

;;; 空リストを作る
(defun make-empty ()
  (let ((cp (create (class <cell>))))
    (setf (cell-prev cp) cp)
    (setf (cell-next cp) cp)
    cp))

;;; 双方向リストの定義
(defclass <dlist> ()
  ((top :accessor dlist-top :initform (make-empty))
   (cnt :accessor dlist-cnt :initform 0)))

;;; 前から n 番目のセルを返す (作業用関数)
(defun cell-nth (d n)
  (for ((cp (dlist-top d) (cell-next cp))
        (i -1 (+ i 1)))
       ((= n i) cp)))

;;; 後ろから n 番目のセルを返す (作業用関数)
(defun cell-nth-back (d n)
  (for ((cp (dlist-top d) (cell-prev cp))
        (i -1 (+ i 1)))
       ((= n i) cp)))

;;; 参照
(defmethod dlist-ref ((d <dlist>) (n <integer>))
  (let ((m (if (< n 0) (abs (+ n 1)) n)))
    (if (< m (dlist-cnt d))
	(cell-item (if (< n 0) (cell-nth-back d m) (cell-nth d m)))
      (error "dlist-ref: out of range"))))

;;; 書き換え
(defmethod dlist-set ((d <dlist>) (n <integer>) value)
  (let ((m (if (< n 0) (abs (+ n 1)) n)))
    (if (< m (dlist-cnt d))
	(setf (cell-item (if (< n 0) (cell-nth-back d m) (cell-nth d m)))
	      value)
      (error "dlist-set: out of range"))))

;;; セルの挿入
;;; p - next -> cp - next -> q
(defun cell-insert (p cp q)
  (setf (cell-next cp) q)
  (setf (cell-prev cp) p)
  (setf (cell-prev q) cp)
  (setf (cell-next p) cp))

;;; n 番目に value を挿入
;;; n - 1 番目のセルを求め、その後ろに value を挿入する
(defmethod dlist-insert ((d <dlist>) (n <integer>) value)
  (let ((m (- (if (< n 0) (abs (+ n 1)) n) 1)))
    (if (< m (dlist-cnt d))
	(let* ((p (if (< n 0) (cell-nth-back d m) (cell-nth d m)))
	       (q (if (< n 0) (cell-prev p) (cell-next p)))
	       (cp (create (class <cell>) 'item value)))
	  (if (< n 0)
	      (cell-insert q cp p)
	    (cell-insert p cp q))
	  (setf (dlist-cnt d) (+ (dlist-cnt d) 1))
	  value)
      (error "dlist-insert: out of range"))))

;;;; n 番目のセルの削除
(defmethod dlist-delete ((d <dlist>) (n <integer>))
  (let ((m (if (< n 0) (abs (+ n 1)) n)))
    (if (< m (dlist-cnt d))
	;; p - next -> [cp] - next -> q
	(let* ((cp (if (< n 0) (cell-nth-back d m) (cell-nth d m)))
	       (p (cell-prev cp))
	       (q (cell-next cp)))
	  (setf (cell-next p) q)
	  (setf (cell-prev q) p)
	  (setf (dlist-cnt d) (- (dlist-cnt d) 1))
	  (cell-item cp))
      (error "dlist-delete: out of range"))))

;;; 畳み込み
(defmethod dlist-fold ((d <dlist>) func init)
  (for ((cp (cell-next (dlist-top d)) (cell-next cp))
        (a init (funcall func a (cell-item cp))))
       ((eq cp (dlist-top d)) a)))

(defmethod dlist-foldr ((d <dlist>) func init)
  (for ((cp (cell-prev (dlist-top d)) (cell-prev cp))
        (a init (funcall func (cell-item cp) a)))
       ((eq cp (dlist-top d)) a)))

;;; サイズ
(defmethod dlist-length ((d <dlist>)) (dlist-cnt d))

;;; クリア
(defmethod dlist-clear ((d <dlist>))
  (let ((cp (dlist-top d)))
    (setf (cell-next cp) cp)
    (setf (cell-prev cp) cp)
    (setf (dlist-cnt d) 0)
    nil))

;;; 空リストか？
(defmethod dlist-emptyp ((d <dlist>)) (= (dlist-cnt d) 0))

;;; 変換
(defmethod list->dlist ((xs <list>))
  (for ((d (create (class <dlist>)))
        (xs xs (cdr xs)))
       ((null xs) d)
       (dlist-insert d -1 (car xs))))

(defmethod dlist->list ((d <dlist>))
  (dlist-foldr d (lambda (x y) (cons x y)) nil))

;;; 巡回
(defmethod dlist-for-each ((d <dlist>) func)
  (for ((cp (cell-next (dlist-top d)) (cell-next cp)))
       ((eq (dlist-top d) cp))
       (funcall func (cell-item cp))))

(defmethod dlist-for-each-back ((d <dlist>) func)
  (for ((cp (cell-prev (dlist-top d)) (cell-prev cp)))
       ((eq (dlist-top d) cp))
       (funcall func (cell-item cp))))

;;;
;;; キュー
;;;
(defgeneric enqueue (q x))
(defgeneric dequeue (q))
(defgeneric queue-peek (q))
(defgeneric queue-length (q))
(defgeneric queue-emptyp (q))
(defgeneric queue-clear (q))

;;; クラス定義
(defclass <queue> ()
  ((buffer :accessor queue-buffer :initform (create (class <dlist>)) :initarg buffer)))

;;; キューは空か？
(defmethod queue-emptyp ((q <queue>)) (dlist-emptyp (queue-buffer q)))

;;; キューのサイズ
(defmethod queue-length ((q <queue>)) (dlist-length (queue-buffer q)))

;;; 参照
(defmethod queue-peek ((q <queue>)) (dlist-ref (queue-buffer q) 0))

;;; 挿入
(defmethod enqueue ((q <queue>) item)
  (dlist-insert (queue-buffer q) -1 item))

;;; 取得
(defmethod dequeue ((q <queue>))
  (if (queue-emptyp q)
      (error "dequeue: empty queue")
    (dlist-delete (queue-buffer q) 0)))

;;;
;;; ディーキュー
;;;
(defgeneric deque-push-front (q x))
(defgeneric deque-push-back (q x))
(defgeneric deque-pop-front (q))
(defgeneric deque-pop-back (q))
(defgeneric deque-peek-front (q))
(defgeneric deque-peek-back (q))
(defgeneric deque-length (q))
(defgeneric deque-emptyp (q))
(defgeneric deque-clear (q))

;;; クラス定義
(defclass <deque> ()
  ((buffer :accessor deque-buffer :initform (create (class <dlist>)) :initarg buffer)))

;;; 先頭に追加
(defmethod deque-push-front ((q <deque>) item)
  (dlist-insert (deque-buffer q) 0 item))

;;; 末尾に追加
(defmethod deque-push-back ((q <deque>) item)
  (dlist-insert (deque-buffer q) -1 item))

;;; 先頭要素を取り出す
(defmethod deque-pop-front ((q <deque>))
  (dlist-delete (deque-buffer q) 0))

;;; 末尾要素を取り出す
(defmethod deque-pop-back ((q <deque>))
  (dlist-delete (deque-buffer q) -1))

;;; 先頭要素を参照する
(defmethod deque-peek-front ((q <deque>))
  (dlist-ref (deque-buffer q) 0))

;;; 末尾要素を参照する
(defmethod deque-peek-back ((q <deque>))
  (dlist-ref (deque-buffer q) -1))

;;; 要素数を求める
(defmethod deque-length ((q <deque>)) (dlist-length (deque-buffer q)))

;;; ディーキューは空か？
(defmethod deque-emptyp ((q <deque>)) (dlist-emptyp (deque-buffer q)))

;;; ディーキューを空にする
(defmethod deque-clear ((q <deque>)) (dlist-clear (deque-buffer q)))
