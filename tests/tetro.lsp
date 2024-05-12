;;; tetromino

;;; parts

(defglobal a #2a((1 1)(1 1)))

(defun succp (board)
    (block exit
        (for ((i 0 5))
             ((= i 5) t)
             (for ((j 0 8))
                  ((= j 8) t)
                  (if (= (aref board i j) 0)
                      (return-from exit nil))))))

(defun find-empty (board i)
    (block exit
        (for ((j 0 (+ j 1)))
             ((= j 8) nil)
             (if (= (aref board i j) 0)
                 (return-from exit j)))))


(defun placep (peace board i j)
    (cond ((eq peace 'A0) (place-A0p board i j))
          ((eq peace 'A1) (place-A1p board i j))
          ;;
          (t (error "placep"))))


                      
#|         A0         A1
 A peace   [1,1,1,1]  [1]
                      [1]
                      [1]
                      [1]

          B0
 B peace  [1,1]
          [1,1]

          C0      C1     C2          C3
 C peace  [1]     [1,1]  [1,1,1]      [1]
          [1]       [1]      [1]  [1,1,1]
          [1,1]     [1]

          D0      D1
 D peace  [1]       [1,1]
          [1,1]   [1,1]
            [1]

          E0      E1      E2         E3
 E peace  [1,1,1] [1]       [1]        [1]
            [1]   [1,1]   [1,1,1]    [1,1]
                  [1]                  [1]
|#


;; main
(defun tetro (board)
    (if (succp board) t)
        (for ((r 0 (+ r 1)))
             ((= r 5) nil)
             (cond ((placep 'A0 board) (tetro (puton 'A0 board)))
                   ((placep 'A1 board) (tetro (puton 'A1 board)))
                   ((placep 'B0 board) (tetro (puton 'B0 board)))
                   ((placep 'C0 board) (tetro (puton 'C0 board)))
                   ((placep 'C1 board) (tetro (puton 'C1 board)))
                   ((placep 'C2 board) (tetro (puton 'C2 board)))
                   ((placep 'C3 board) (tetro (puton 'C3 board)))
                   ((placep 'D0 board) (tetro (puton 'D0 board)))
                   ((placep 'D1 board) (tetro (puton 'D1 board)))
                   ((placep 'E0 board) (tetro (puton 'E0 board)))
                   ((placep 'E1 board) (tetro (puton 'E1 board)))
                   ((placep 'E2 board) (tetro (puton 'E2 board)))
                   ((placep 'E3 board) (tetro (puton 'E3 board))))))
#|
  if sunccp -> t
  row 0~7 find-empty
    try A variation -> recur
    try B variation -> recur
    try C variation -> recur
    try D variation -> recur
    try E variation -> recur

|#
