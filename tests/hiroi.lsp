;; written by M.hiroi
;; thanks

;; 再帰定義
(defun fact (n)
  (if (= n 0)
      1
    (* n (fact (- n 1)))))

;; 末尾再帰
(defun fact1 (n a)
  (if (= n 0)
      a
    (fact1 (- n 1) (* a n))))

;; 繰り返し
(defun fact2 (m)
  (for ((n m (- n 1))
        (a 1 (* a n)))
       ((<= n 0) a)))


;;おまけ
(defun fact3 (n)
  (let ((a 1))
    (while (> n 0)
      (setq a (* a n))
      (setq n (- n 1)))
    a))