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


(defun putp (peace i j) )


                      
#|
 A peace   [1,1,1,1]  [1]
                      [1]
                      [1]
                      [1]

 B peace  [1,1]
          [1,1]

 C peace  [1]     [1,1]  [1,1,1]      [1]
          [1]       [1]      [1]  [1,1,1]
          [1,1]     [1]

 D peace  [1]       [1,1]
          [1,1]   [1,1]
            [1]

 
 E peace  [1,1,1] [1]       [1]        [1]
            [1]   [1,1]   [1,1,1]    [1,1]
                  [1]                  [1]
|#


;; main
;; (tetro board)
#|
  if sunccp -> t
  row 0~7 find-empty
    try A variation -> recur
    try B variation -> recur
    try C variation -> recur
    try D variation -> recur
    try E variation -> recur

|#
