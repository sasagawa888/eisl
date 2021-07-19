;; written by M.Hiroi
;; modified by K.Sasagawa
;;リスト : ライツアウトの解法

;; > (solver-fast #x1ffffff)

(import "bit")
(import "macro")

;;;
;;; lo.lisp : ライツアウトの解法
;;;
;;;           Copyright (C) 2020 Makoto Hiroi
;;;

;;; 組み合わせの生成
(defun combination (fn n r :rest a)
  (if (null a)
      (setq a 0)
      (setq a (car a)))
  (cond
   ((zerop r)
    (funcall fn a))
   ((zerop n) nil)
   (t
    (combination fn (1- n) r a)
    (combination fn (1- n) (1- r) (logior (ash 1 (1- n)) a)))))

;;; ボタンを押したときのパターン
(defconstant pattern
  #(#x0000023 #x0000047 #x000008e #x000011c #x0000218
    #x0000461 #x00008e2 #x00011c4 #x0002388 #x0004310
    #x0008c20 #x0011c40 #x0023880 #x0047100 #x0086200
    #x0118400 #x0238800 #x0471000 #x08e2000 #x10c4000
    #x0308000 #x0710000 #x0e20000 #x1c40000 #x1880000))

;;; ボタンを押す
(defun push-buttons (xs board :rest n)
  (if (null n)
      (setq n 0)
      (setq n (car n)))
  (cond
   ((zerop xs) board)
   ((logtest xs 1)
    (push-buttons (ash xs -1) (logxor (aref pattern n) board) (1+ n)))
   (t
    (push-buttons (ash xs -1) board (1+ n)))))

;;; 速度の違いはあまりなかった
(defun push-buttons-fast (xs board)
  (if (zerop xs)
      board
    (let ((x (logand xs (- xs))))
      (push-buttons-fast (logxor xs x)
                         (logxor (aref pattern (logcount (1- x))) board)))))

;;; 解の表示
(defun print-answer (xs)
  (do ((n 0 (1+ n)))
      ((>= n 25))
      (if (logbitp n xs)
          (princ "O ")
        (princ "X "))
      (when (zerop (mod (1+ n) 5))
        (terpri))))

;;; 解法
(defun solver (board)
  (dotimes (n 25)
    (format (standard-output) "----- ~A -----~%" (1+ n))
    (combination
     (lambda (xs)
       (block foo
       (when (zerop (push-buttons xs board))
         (print-answer xs)
         (return-from solver))))
     25 (1+ n))))

;;; 高速版
(defun solver-fast (board)
  (dotimes (i 32)
    (let ((xs i)                               ; 押したボタン (ビット)
          (new-board (push-buttons i board)))  ; 1 行目を押す (32 通り)
      ;; 1 行ずつライトを消していく
      (dotimes (j 20)
        (when (logbitp j new-board)
          (setq new-board (logxor (aref pattern (+ j 5)) new-board))
          (setq      xs        (logior xs (ash 1 (+ j 5))))))
      (when (zerop new-board)
        (print-answer xs)
        (terpri)))))


(defun princ (x)
    (format (standard-output) x))

(defun terpri ()
    (format (standard-output) "~%"))

(defun 1+ (n)
  (+ n 1))

(defun 1- (n)
  (- n 1))

(defun zerop (x)
  (= x 0))