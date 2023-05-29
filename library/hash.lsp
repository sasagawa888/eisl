;;
;; hash.l : ハッシュ表 (チェイン法)
;;
;;          Copyright (C) 2016 Makoto Hiroi
;;
(import "cxr")

(defglobal default-hash-size 8191)

(defclass <hash> ()
  ((size  :accessor hash-size :initform default-hash-size :initarg size)
   (cnt   :accessor hash-cnt :initform 0)
   (table :accessor hash-table)))

(defmethod initialize-object :after ((h <hash>) xs)
  (setf (hash-table h)
        (create-vector (hash-size h) nil)))


(defgeneric hash-func (k))
(defgeneric gethash (h k))
(defgeneric sethash (h k v))
(defgeneric remhash (h k))
(defgeneric clrhash (h))
(defgeneric hash-count (h))
(defgeneric maphash (f h))

;; integer 整数
(defmethod hash-func ((n <integer>)) (abs n))

;; string 文字列
(defmethod hash-func ((s <string>))
  (for ((i 0 (+ i 1))
        (a 0))
       ((>= i (length s)) a)
       (setq a (+ (* a 8) (convert (elt s i) <integer>)))))

;; find 探索
(defun find-cell (key xs)
  (block exit
    (for ((xs xs (cdr xs)))
         ((null xs))
         (if (equal (caar xs) key)
             (return-from exit (car xs))))))

(defmethod gethash ((h <hash>) key)
  (let ((cp (find-cell key (aref (hash-table h)
                                 (mod (hash-func key) (hash-size h))))))
    (and cp (cdr cp))))

;; insert 挿入
(defmethod sethash ((h <hash>) key val)
  (let* ((ht (hash-table h))
         (hv (mod (hash-func key) (hash-size h)))
         (cp (find-cell key (aref ht hv))))
    (cond (cp
           (setf (cdr cp) val))
          (t
           (setf (aref ht hv)
                 (cons (cons key val) (aref ht hv)))
           (setf (hash-cnt h) (+ (hash-cnt h) 1))))
    val))

;; remove 削除
(defmethod remhash ((h <hash>) key)
  (let* ((ht (hash-table h))
         (hv (mod (hash-func key) (hash-size h)))
         (cp (find-cell key (aref ht hv))))
    (cond (cp
           (setf (aref ht hv)
                 (remove-if (lambda (x) (eq x cp)) (aref ht hv)))
           (setf (hash-cnt h) (- (hash-cnt h) 1))
           t)
          (t nil))))

;; clear クリア
(defmethod clrhash ((h <hash>))
  (setf (hash-cnt h) 0)
  (for ((ht (hash-table h))
        (i 0 (+ i 1)))
       ((>= i (hash-size h)))
       (setf (aref ht i) nil)))

;; count element 要素の個数
(defmethod hash-count ((h <hash>)) (hash-cnt h))

;; map マップ関数
(defmethod maphash (f (h <hash>))
  (for ((i 0 (+ i 1)))
       ((>= i (hash-size h)))
       (for ((xs (aref (hash-table h) i) (cdr xs)))
            ((null xs))
            (funcall f (caar xs) (cdar xs)))))