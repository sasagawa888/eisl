;; written by M.hiroi
;; thanks

; 末尾のセル
(defun last-pair (xs)
  (for ((xs xs (cdr xs)))
       ((null (cdr xs)) xs)))

; 再帰版
(defun rlast-pair (xs)
  (if (null (cdr xs))
      xs
      (rlast-pair (cdr xs))))

;; 末尾の要素
(defun last (xs) (car (last-pair xs)))

; 再帰版
(defun rlast (xs)
  (if (null (cdr xs))
      (car xs)
      (rlast (cdr xs))))

;; 先頭から n 個の要素を取り出す
(defun take (xs n)
  (for ((n n (- n 1))
        (a nil (cons (car xs) a))
        (xs xs (cdr xs)))
       ((or (<= n 0) (null xs)) (nreverse a))))

;; 再帰版
(defun rtake (xs n)
  (if (= n 0)
      nil
      (cons (car xs) (rtake (cdr xs) (- n 1)))))

;; 先頭から n 個の要素を取り除く
(defun drop (xs n)
  (for ((n n (- n 1))
        (xs xs (cdr xs)))
       ((or (<= n 0) (null xs)) xs)))

(defun rdrop (xs n)
  (if (= n 0)
      xs
      (rdrop (cdr xs) (- n 1))))

