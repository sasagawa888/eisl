;;; lights out
;;; Copyright (C) 2022 Makoto Hiroi

(defun comb (fn n r a)
  (cond
   ((= r 0) (funcall fn a))
   ((= n 0) nil)
   (t
    (comb fn (1- n) r a)
    (comb fn (1- n) (1- r) (logior (ash 1 (1- n)) a)))))

(defun combination (fn n r) (comb fn n r 0))

(defun 1- (n) (- n 1))


(import "macro")
(import "bit")

;;; ボタンを押したときのパターン
(defglobal pattern
  #(#x0000023 #x0000047 #x000008e #x000011c #x0000218
    #x0000461 #x00008e2 #x00011c4 #x0002388 #x0004310
    #x0008c20 #x0011c40 #x0023880 #x0047100 #x0086200
    #x0118400 #x0238800 #x0471000 #x08e2000 #x10c4000
    #x0308000 #x0710000 #x0e20000 #x1c40000 #x1880000))

;;; ボタンを押す
(defun push-buttons (xs board n)
  (cond
   ((= xs 0) board)
   ((logtest xs 1)
    (push-buttons (ash xs -1) (logxor (aref pattern n) board) (+ n 1)))
   (t
    (push-buttons (ash xs -1) board (+ n 1)))))

;;; 解の表示
(defun print-answer (xs)
  (dotimes (n 25)
    (format (standard-output)
            "~A "
            (if (logbitp n xs) "O" "X"))
    (if (= (mod (+ n 1) 5) 0)
        (format (standard-output) "~%"))))

;;; 解法 (solver #x1ffffff)
(defun solver (board)
  (block
   exit
   (for ((n 1 (+ n 1)))
        ((> n 25))
        (format (standard-output) "----- ~D -----~%" n)
        (combination
         (lambda (xs)
           (cond
            ((= (push-buttons xs board 0) 0)
             (print-answer xs)
             (return-from exit))))
         25 n))))


;;; parallel tests 
;;; added by kenichi sasagawa
;;; (psolver #x1ffffff)
;;; it doesn't work
(defun psolver (board)
  (mp-exec (psolver1 1 13 board)
           (psolver1 14 16 board)
           (psolver1 16 17 board)
           (psolver1 18 19 board)
           (psolver1 20 25 board)))

(defun psolver1 (start end board)
  (block
   exit
   (for ((n start (+ n 1)))
        ((> n end))
        (format (standard-output) "----- ~D -----~%" n)
        (combination
         (lambda (xs)
           (cond
            ((= (push-buttons xs board 0) 0)
             (print-answer xs)
             (return-from exit t))))
         25 n))))