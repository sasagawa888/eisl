;;; tetromino

;;; parts

(defconstant row 5)
(defconstant col 8)

#| board row*col
[0,0,0,0,0,0,0,0]
[0,0,0,0,0,0,0,0]
[0,0,0,0,0,0,0,0]
[0,0,0,0,0,0,0,0]
[0,0,0,0,0,0,0,0]
|#

(defun succp (board)
    (block exit
        (for ((i 0 (+ i 1)))
             ((= i row) t)
             (for ((j 0 (+ j 1)))
                  ((= j col) t)
                  (if (= (aref board i j) 0)
                      (return-from exit nil))))))

(defun find-empty (board i)
    (block exit
        (for ((j 0 (+ j 1)))
             ((= j col) nil)
             (if (= (aref board i j) 0)
                 (return-from exit j)))))


(defun placep (peace board i j)
    (cond ((eq peace 'A0) (place-A0p board i j))
          ((eq peace 'A1) (place-A1p board i j))
          ;;
          (t (error "placep"))))

(defun place-A0p (board i j)
    (and (<= (+ j 4) col)
         (= (aref board i (+ j 1)) 0)
         (= (aref board i (+ j 2)) 0)
         (= (aref board i (+ j 3)) 0)))

(defun place-A1p (board i j)
    (and (<= (+ i 4) row)
         (= (aref board (+ i 1) j) 0)
         (= (aref board (+ i 2) j) 0)
         (= (aref board (+ i 3) j) 0)))
         
(defun place-B0p (board i j)
    (and (<= (+ i 2) row)
         (<= (+ j 2) col)
         (= (aref board (+ i 1) j) 0)
         (= (aref board i (+ j 1)) 0)
         (= (aref board (+ i 1) (+ j 1) 0))))


(defun puton (peace board i j)
    (cond ((eq peace 'A0) (puton-A0 board i j))
          ((eq peace 'A1) (puton-A1 board i j))))



(defun puton-A0 (board i j)
    (set-aref 1 board i j)
    (set-aref 1 board i (+ j 1))
    (set-aref 1 board i (+ j 2))
    (set-aref 1 board i (+ j 3))
    board)
                      
#|         A0         A1
 A piece   [1,1,1,1]  [1]
                      [1]
                      [1]
                      [1]

          B0
 B piece  [1,1]
          [1,1]

          C0      C1     C2          C3     C4        C5
 C piece  [1]     [1,1]  [1,1,1]      [1]   [1]       [1,1,1]
          [1]       [1]      [1]  [1,1,1]   [1,1,1]   [1]
          [1,1]     [1]

          D0      D1        D2      D3
 D piece  [1]       [1,1]     [1]   [1,1]
          [1,1]   [1,1]     [1,1]     [1,1]
            [1]             [1]

          E0      E1      E2         E3
 E piece  [1,1,1] [1]       [1]        [1]
            [1]   [1,1]   [1,1,1]    [1,1]
                  [1]                  [1]
|#


;; main
(defun tetro (board)
    (if (succp board) t)
        (for ((r 0 (+ r 1)))
             ((= r row) nil)
             (cond ((placep 'A0 board) (tetro (puton 'A0 board)))
                   ((placep 'A1 board) (tetro (puton 'A1 board)))
                   ((placep 'B0 board) (tetro (puton 'B0 board)))
                   ((placep 'C0 board) (tetro (puton 'C0 board)))
                   ((placep 'C1 board) (tetro (puton 'C1 board)))
                   ((placep 'C2 board) (tetro (puton 'C2 board)))
                   ((placep 'C3 board) (tetro (puton 'C3 board)))
                   ((placep 'C4 board) (tetro (puton 'C4 board)))
                   ((placep 'C5 board) (tetro (puton 'C5 board)))
                   ((placep 'D0 board) (tetro (puton 'D0 board)))
                   ((placep 'D1 board) (tetro (puton 'D1 board)))
                   ((placep 'D2 board) (tetro (puton 'D2 board)))
                   ((placep 'D3 board) (tetro (puton 'D3 board)))
                   ((placep 'E0 board) (tetro (puton 'E0 board)))
                   ((placep 'E1 board) (tetro (puton 'E1 board)))
                   ((placep 'E2 board) (tetro (puton 'E2 board)))
                   ((placep 'E3 board) (tetro (puton 'E3 board)))
                   (t nil))))
#|
  if sunccp -> t
  row 0~7 find-empty
    try A variation -> recur
    try B variation -> recur
    try C variation -> recur
    try D variation -> recur
    try E variation -> recur

|#
