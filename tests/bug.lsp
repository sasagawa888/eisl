
(defglobal a '(#\a #\b #\c))

(defglobal a #2a((1 2) (3 4)))

(defun calc-single-comment-margin (x lm)
    (let ((size (flatsize x)))
       (if (< (+ lm size) single-comment-margin)
           (- single-comment-margin (+ lm size))
           (- single-comment-margin1 (+ lm size)) )))

;; write cons with indent
(defun pp-indent (x lm)
    (pp-string "(")
    (for ((s x (cdr s)))
         ((null s)
          (cond ((= (length x) 0) (pp-string ")"))
               (otomo (pp-string ")"))
               (t (setq otomo t) (pp-string " )")) )
          (if (= lm 0)
             (newline 0)) )
         (if (stringp (car s))
             (pp-string (car s))
             (pp1 (car s) (+ lm 1)))
         (cond ((and (not (null (cdr s))) (single-comment-p (car (cdr s))))                ;single comment
                (space (calc (car s) lm))
                (pp-string (car (cdr s)))
                (newline lm)
                (setq s (cdr s)))
               ((not (null (cdr s)))                                                       ;asdfads
                (newline (+ lm 3))))))
