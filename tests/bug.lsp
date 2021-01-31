
(defglobal a '(#\a #\b #\c))

(defglobal a #2a((1 2) (3 4)))

(defun calc-single-comment-margin (x lm)
    (let ((size (flatsize x)))
       (if (< (+ lm size) single-comment-margin)
           (- single-comment-margin (+ lm size))
           (- single-comment-margin1 (+ lm size)) )))
