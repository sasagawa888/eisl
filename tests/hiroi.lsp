;testing formatter
; written by M.hiroi

;;;リスト : ナンバープレースの解法

;; 縦横枠のチェック
(defun check (board x y n)
    (block exit
       ; 縦横のチェック
       (for ((i 0 (+ i 1)))
            ((>= i 9))
            (if (or (= (aref board x i) n) (= (aref board i y) n))
                (return-from exit nil) )); 枠のチェック
       (let ((x1 (* (div x 3) 3))
             (y1 (* (div y 3) 3)) )
          (for ((i 0 (+ i 1)))
               ((>= i 3)
                t )
               (for ((j 0 (+ j 1)))
                    ((>= j 3))
                    (if (= (aref board (+ x1 i) (+ y1 j)) n)
                        (return-from exit nil)))))))

;; 盤面の表示
(defun print-board (board)
    (for ((x 0 (+ x 1)))
         ((>= x 9))
         (for ((y 0 (+ y 1)))
              ((>= y 9)
               (format (standard-output) "~%") )
              (format (standard-output) "~D " (aref board x y)))) )

;; 深さ優先探索
(defun solver (board x y)
    (cond ((= y 9) (print-board board))
          ((= x 9) (solver board 0 (+ y 1)))
          ((/= (aref board x y) 0) (solver board (+ x 1) y))
          (t
             (for ((n 1 (+ n 1)))
                ((> n 9))
                (cond ((check board x y n)
                         (setf (aref board x y) n)
                         (solver board (+ x 1) y)
                         (setf (aref board x y) 0) ))) )))

(defun test ()
    (solver q00 0 0) )

;; 問題 (出典: 数独 - Wikipedia の問題例)
(defglobal
   q00
   #2a((5 3 0 0 7 0 0 0 0)
       (6 0 0 1 9 5 0 0 0)
       (0 9 8 0 0 0 0 6 0)
       (8 0 0 0 6 0 0 0 3)
       (4 0 0 8 0 3 0 0 1)
       (7 0 0 0 2 0 0 0 6)
       (0 6 0 0 0 0 2 8 0)
       (0 0 0 4 1 9 0 0 5)
       (0 0 0 0 8 0 0 7 9) ) )