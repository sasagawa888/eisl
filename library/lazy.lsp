;;;
;;; lazy.lsp : 遅延評価と遅延ストリーム (Easy-ISLisp 用)
;;;
;;;            Copyright (C) 2023 Makoto Hiroi
;;;

;;;
;;; 遅延評価
;;;
(defmacro delay (expr)
  `(make-promise (lambda () ,expr)))

(defun make-promise (f)
  (let ((flag nil) (result nil))
    (lambda ()
      (if (not flag)
        (let ((x (funcall f)))
          (cond ((not flag)
                 (setq flag t)
                 (setq result x)))))
      result)))

(defun force (promise)
  (funcall promise))

;;;
;;; 遅延ストリーム
;;;

;;; 遅延ストリームの生成
(defmacro lcons (a b)
  `(cons ,a (lambda () ,b)))

;;; アクセス関数
(defun lcar (s) (car s))
(defun lcdr (s)
  (if (functionp (cdr s))
    (setf (cdr s) (funcall (cdr s))))
  (cdr s))

;;; 数列の生成
(defun ltabulate (f n m)
  (if (and m (< m n))
      nil
    (lcons (funcall f n) (ltabulate f (+ n 1) m))))

(defun liota (n m) (ltabulate #'identity n m))

(defun lunfold (p f g seed)
  (if (funcall p seed)
      nil
    (lcons (funcall f seed) (lunfold p f g (funcall g seed)))))

;;; 引数を遅延ストリームに変換
(defun llist (&rest args)
  (if (null args)
      nil
    (lcons (car args) (apply #'llist (cdr args)))))

;;; リストを遅延ストリームに変換
(defun fromlist (xs) (apply #'llist xs))

;;; 遅延ストリームをリストに変換
(defun tolist (s)
  (if (null s)
      nil
    (cons (lcar s) (tolist (lcdr s)))))

;;; n 番目の要素を求める
(defun lnth (n s)
  (if (= n 0)
      (lcar s)
    (lnth (- n 1) (lcdr s))))

;;; 先頭から n 個の要素を取り出す
(defun ltake (s n)
  (if (or (null s) (= n 0))
      nil
    (lcons (lcar s) (ltake (lcdr s) (- n 1)))))

;;; 先頭から n 個の要素を取り除く
(defun ldrop (s n)
  (if (or (null s) (= n 0))
      s
    (ldrop (lcdr s) (- n 1))))

;;; ストリームの結合
(defun lappend (s1 s2)
  (if (null s1)
      s2
    (lcons (lcar s1) (lappend (lcdr s1) s2))))

;;; 遅延評価版 (s2 は遅延評価)
(defun lappend-delay (s1 s2)
  (if (null s1)
      (force s2)
    (lcons (lcar s1) (lappend-delay (lcdr s1) s2))))

;;; 遅延ストリームの要素をまとめる
(defun lzip (&rest s)
  (if (member nil s)
      nil
    (lcons (mapcar #'lcar s) (apply #'lzip (mapcar #'lcdr s)))))

;;; 長さ
(defun llength-sub (s n)
  (if (null s)
      n
    (llength-sub (lcdr s) (+ n 1))))

(defun llength (s) (llength-sub s 0))

;;;
;;; 高階関数
;;;

;;; マッピング
(defun lmap (proc &rest s)
  (if (member nil s)
      nil
    (lcons (apply proc (mapcar #'lcar s))
           (apply #'lmap proc (mapcar #'lcdr s)))))

;;; マッピングの結果を平坦化する
(defun flatlmap (proc s)
  (if (null s)
      nil
    (lappend-delay (funcall proc (lcar s))
                   (delay (flatlmap proc (lcdr s))))))

;;; フィルター
(defun lfilter (pred s)
  (cond
   ((null s) nil)
   ((funcall pred (lcar s))
    (lcons (lcar s)
           (lfilter pred (lcdr s))))
   (t (lfilter pred (lcdr s)))))

;;; 畳み込み
(defun lfold-left (proc a s)
  (if (null s)
      a
    (lfold-left proc (funcall proc a (lcar s)) (lcdr s))))

(defun lfold-right (proc a s)
  (if (null s)
      a
    (funcall proc (lcar s) (lfold-right proc a (lcdr s)))))

(defun lscan-left (proc a s)
  (lcons a (if (null s)
               nil
             (lscan-left proc (funcall proc a (lcar s)) (lcdr s)))))

;;; 巡回
(defun lforeach (proc s)
  (cond
   ((null s)
    (funcall proc (lcar s))
    (lforeach proc (lcdr s)))))

;;; 述語 pred が真を返す要素を取り出す
(defun ltake-while (pred s)
  (if (or (null s)
          (not (funcall pred (lcar s))))
      nil
    (lcons (lcar s)
           (ltake-while pred (lcdr s)))))

;;; 述語 pred が真を返す要素を取り除く
(defun ldrop-while (pred s)
  (if (not (funcall pred (lcar s)))
      s
    (ldrop-while pred (lcdr s))))

;;; pred が真を返す要素があれば T を返す
(defun lsome (pred &rest s)
  (cond
   ((member nil s) nil)
   ((apply pred (mapcar #'lcar s)) t)
   (t (apply #'lsome pred (mapcar #'lcdr s)))))

;;; pred が NIL を返す要素があれば NIL を返す
(defun levery (pred &rest s)
  (cond
   ((member nil s) t)
   ((not (apply pred (mapcar #'lcar s))) nil)
   (t (apply #'levery pred (mapcar #'lcdr s)))))

;;;
;;; 集合演算
;;;

;;; 和集合
(defun lunion (s1 s2)
  (cond
   ((null s1) s2)
   ((null s2) s1)
   ((= (lcar s1) (lcar s2))
    (lcons (lcar s1)
           (lunion (lcdr s1) (lcdr s2))))
   ((< (lcar s1) (lcar s2))
    (lcons (lcar s1)
           (lunion (lcdr s1) s2)))
   (t
    (lcons (lcar s2)
           (lunion s1 (lcdr s2))))))

;;; 積集合
(defun lintersect (s1 s2)
  (cond
   ((or (null s1) (null s2)) nil)
   ((= (lcar s1) (lcar s2))
    (lcons (lcar s1)
           (lintersect (lcdr s1) (lcdr s2))))
   ((< (lcar s1) (lcar s2))
    (lintersect (lcdr s1) s2))
   (t
    (lintersect s1 (lcdr s2)))))

;;; 差集合
(defun ldifferent (s1 s2)
  (cond
   ((null s1) nil)
   ((null s2) s1)
   ((= (lcar s1) (lcar s2))
    (ldifferent (lcdr s1) (lcdr s2)))
   ((< (lcar s1) (lcar s2))
    (lcons (lcar s1)
           (ldifferent (lcdr s1) s2)))
   (t
    (ldifferent s1 (lcdr s2)))))

