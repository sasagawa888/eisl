;;;
;;; queue.l : キュー
;;;
;;;           Copyright (C) 2016 Makoto Hiroi
;;;

;; データ構造の定義
(defclass <queue> ()
  ((front :accessor queue-front :initform nil)
   (rear  :accessor queue-rear  :initform nil)))

(defgeneric enqueue (q x))
(defgeneric dequeue (q))
(defgeneric emptyp (q))

;; キューは空か？
(defmethod emptyp ((q <queue>))
  (null (queue-front q)))

;; データの挿入
(defmethod enqueue ((q <queue>) x)
  (let ((cell (list x)))
    (cond ((emptyp q)
           (setf (queue-front q) cell)
           (setf (queue-rear  q) cell))
          (t
           (setf (cdr (queue-rear q)) cell)
           (setf (queue-rear q) cell)))))

;; データの取り出し
(defmethod dequeue ((q <queue>))
  (cond ((null (queue-front q))
         (error "empty Queue"))
        (t
         (let ((x (car (queue-front q))))
           (setf (queue-front q) (cdr (queue-front q)))
           (if (null (queue-front q))
               (setf (queue-rear q) nil))
           x))))
           