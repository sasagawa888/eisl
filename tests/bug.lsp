(defun foo ()
(let ((x 0)
       (a '((one . 11) (two . 12) (three . 13) 14)))
   (list (map-into a (lambda () (setq x (+ x 2)))) a)))

; ((2 4 6 8) (2 4 6 8))
; equal)
 

