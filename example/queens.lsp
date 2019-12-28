;queens problemwritten by Hiroshi Gomi


(defun qsort (lambda list)
  (if (null list)
      list
      (qsort2 lambda (car list) (cdr list) nil nil )))


(defun qsort2 (lambda p list left right)
  (if (null list)
      (append (qsort lambda left)(cons p (qsort lambda right)))
      (if (apply lambda (car list)(list p))
          (qsort2 lambda p
                  (cdr list)(cons (car list) left) right)
          (qsort2 lambda p
                  (cdr list) left (cons (car list) right)))))

(defun nqueen (n)
  (nqueen2 n 1 nil))


(defun nqueen2 (n y board)
  (if (> y n)
      nil
      (if (or (member y board)(diagonal 1 y board))
          (nqueen2 n (+ y 1) board)
          (append (if (= (length board) (- n 1))
                      (list (cons y board))
                      (nqueen2 n 1 (cons y board)) )
                  (nqueen2 n (+ y 1) board)))))

(defun diagonal (x queen board)
  (if (null board)
      nil
      (if (= (abs (- (car board) queen)) x)
          t
          (diagonal (+ x 1) queen (cdr board)))))

;;(defun diagonal (x queen board)
;;  (block nil
;;    (for ((i x (+ i 1)))
;;         ((null board) nil)
;;        (if (= (abs (- (car board) queen)) i)
;;             (return-from nil t)
;;             (setq board (cdr board)) ))))









