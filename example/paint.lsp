;;; A simple "paint"/ASCII-art program.
;;; Ported from https://github.com/HiTECNOLOGYs/cl-charms/blob/master/examples/paint.lisp

(import "virtty")
;; Please compile virtty.lsp in library beforehand.

(defun paint ()
   ;; Paint an asterisk at the cursor, or erase the one already painted.
   (let ((pos (cons 0 0)))
        (getyx pos)
        (tyo (if (char/= #\Space (convert (inch) <character>))
                 #\Space
                 #\*))
        (tycursor (cdr pos) (car pos))))

(defun main ()
   ;; Start the paint program.
   (typrologue)
   (let ((x 0)
         (y 0))
        (for ((c (tyi) (tyi)))
             ((member (convert c <character>) '(#\q #\Q)))
             (tyflush)
             (cond ((= c (tyupkey)) (setq y (- y 1)))
                   ((= c (tyleftkey)) (setq x (- x 1)))
                   ((= c (tydownkey)) (setq y (+ y 1)))
                   ((= c (tyrightkey)) (setq x (+ x 1)))
                   ((char= (convert c <character>) #\Space) (paint)))
             (setq x (mod x (tyxmax)))
             (setq y (mod y (tyymax)))
             (tycursor x y)))
   (tyepilogue))
